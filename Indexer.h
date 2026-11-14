#pragma once
#include<string>
#include "Types.h"
#include "HashTable.h"
#include "Set.h" 

class Indexer{
   CustomHashTable<std::string, CustomVector<FilePosting>> index;  
   CustomVector<FileInfo> files;                                   
  
   public:
   CustomVector<std::string> tokenize(const std::string& line);
   bool buildIndex(const std::string& rootFolder, const CustomSet<std::string>& stopWords); 
   CustomHashTable<std::string, CustomVector<FilePosting>>& get_index();
   CustomVector<FileInfo>& get_files();
};