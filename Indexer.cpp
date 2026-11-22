#include "Indexer.h"
#include<iostream>
#include<fstream>
#include<filesystem>
#include<cctype>
namespace fs = std::filesystem;


CustomVector<std::string> Indexer::tokenize(const std::string& line) const{
    CustomVector<std::string> words;
    std::string word = "";

    for(int i = 0; i < (int)line.size(); i++){
        unsigned char c = (unsigned char) line[i];
        if(isalnum(c) || c == '_'){
            word += (char)tolower(c);
        }
        else{
            if(word != ""){
                words.push_back(word);
                word = "";
            }
        }
    }
    if(word != ""){
        words.push_back(word);
    }
    return words;
}

bool Indexer::buildIndex(const std::string& rootFolder, const CustomSet<std::string>& stopWords){

    if (!fs::exists(rootFolder) || !fs::is_directory(rootFolder)){
        std::cout<<"Error: Folder not found: "<<rootFolder<<std::endl;
        return false;
    }
    for(const auto& entry : fs::recursive_directory_iterator(rootFolder, fs::directory_options::skip_permission_denied)){
        if (!entry.is_regular_file()){
            continue; // Skip folders, only look at files
        }

        //gets lowercased extension (.txt, .cpp, .h)
        std::string ext = entry.path().extension().string();
        for(int i = 0; i < (int)ext.size(); i++){
            ext[i] = (char)tolower((unsigned char)ext[i]);
        }
        if(ext != ".txt" && ext != ".cpp" && ext != ".h"){
            continue;
        }

        //opens the file
        std::string filePath = entry.path().string();
        std::ifstream fin(filePath);
        if(!fin.is_open()){
            std::cout<<"Warning: Could not open file: "<<filePath<<std::endl;
            continue;
        }

        //fill FileInfo struct from Types.h
        FileInfo info;
        info.path = filePath;
        info.totalWords = 0;
        std::string line;
        while(std::getline(fin, line)){
            // Strip Windows '\r' at the end of the line if present
            if(!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            info.lines.push_back(line);
        }
        fin.close();

        files.push_back(info);
    }

    //for every fileInfo in 'files' and every line in each file is tokenized
    for (int F = 0; F < files.size(); F++){
        for (int L = 0; L < files[F].lines.size(); L++){
            
            CustomVector<std::string> words = tokenize(files[F].lines[L]);

            for (int w = 0; w < words.size(); w++){
                std::string word = words[w];
                if (stopWords.contains(word)){
                    continue;
                }
                files[F].totalWords++;
                //insert in 'index' hashtable (key = word, value = array of filepostings bcz a word might appear in different files)
                CustomVector<FilePosting>* postings = index.find(word);
                if(postings == nullptr){
                    index.insert(word, CustomVector<FilePosting>()); //empty vector pass
                    postings = index.find(word);
                }
                //creates new fileposting when either for a word in a file no fileposting created
                //or when the same word found in a new file(different file id)
                if(postings->size() == 0 || (*postings)[postings->size() - 1].fileId != F){
                    FilePosting fp;
                    fp.fileId = F;
                    fp.wordCount = 0;
                    postings->push_back(fp);
                }

                //refers to the new FilePosting(value) added to our hashtable with key(word)
                FilePosting& currentPosting = (*postings)[postings->size() - 1];
                currentPosting.wordCount++;

                //if last Occurrence isn't line L, add {L, 1}, otherwise increment timesOnLine
                CustomVector<Occurrence>& occ = currentPosting.occurrences;
                if(occ.size() == 0 || occ[occ.size() - 1].lineNumber != L+1){
                    Occurrence oc;
                    oc.lineNumber = L+1;
                    oc.timesOnLine = 1;
                    occ.push_back(oc);
                } 
                else{
                    occ[occ.size() - 1].timesOnLine++;
                }
            }
        }
    }
    return true;
}

CustomHashTable<std::string, CustomVector<FilePosting>>& Indexer::get_index(){
    return index;
}

CustomVector<FileInfo>& Indexer::get_files(){
    return files;
}

const CustomHashTable<std::string, CustomVector<FilePosting>>& Indexer::get_index() const {
    return index;
}

const CustomVector<FileInfo>& Indexer::get_files() const {
    return files;
}
