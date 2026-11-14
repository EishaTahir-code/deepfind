#include "Indexer.h"
#include<iostream>
#include<fstream>
#include<cctype>

CustomVector<std::string> tokenize(const std::string& line){
    CustomVector<std::string> words;
    std::string word = "";

    for(int i = 0; i < (int)line.size(); i++){
        unsigned char c = (unsigned char) line[i];
        if(isalnum(c) || c == '_'){
            word += tolower(c);
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
    std::string filePath = rootFolder;
    std::ifstream fin(filePath);

    if(!fin.is_open()){
        std::cout<<"Error: Cannot open file!\n";
        return false;
    }

    FileInfo info;
    info.path = filePath;

    std::string line;

    while(getline(fin, line)) {
        info.lines.push_back(line);
    }

    files.push_back(info);

    fin.close();

    return true;
}
