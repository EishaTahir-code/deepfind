/*to build inverted index(hashTable) for each new word that tracks the
   occurrence in a particular file (fileID), frequency of the word, 
   and vector list of struct occurrence (lineNumber, timesOnLine) */

#pragma once
#include<string>
#include "Types.h"
#include "HashTable.h"
#include "Set.h" 

CustomVector<std::string> tokenize(const std::string& line);
bool buildIndex(const std::string& rootFolder, const CustomSet<std::string>& stopWords); 
CustomHashTable<std::string, CustomVector<FilePosting>>& get_index();
CustomVector<FileInfo>& get_files();
