#include "Indexer.h"
#include<iostream>
#include<fstream>
#include<filesystem>
#include<cctype>
namespace fs = std::filesystem;


CustomVector<std::string> tokenize(const std::string& line){
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

bool buildIndex(const std::string& rootFolder, const CustomSet<std::string>& stopWords){

    if (!fs::exists(rootFolder) || !fs::is_directory(rootFolder)){
        std::cout<<"Error: Folder not found: "<<rootFolder<<std::endl;
        return;
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


    return true;
}
