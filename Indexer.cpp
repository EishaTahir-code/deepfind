#include "Indexer.h"
#include<iostream>
#include<fstream>
#include<cctype>

CustomVector<std::string> tokenize(const std::string& line){
    CustomVector<std::string> words;
    std::string word = "";

    for (int i = 0; i < (int)line.size(); i++){
        char c = line[i];
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