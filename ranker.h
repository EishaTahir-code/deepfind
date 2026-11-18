#pragma once
#include<string>
#include "Types.h"
using namespace std;

CustomVector<SearchResult> rankResults(const CustomVector<SearchResult>& options, int k=TOP_K);
void printResults(const CustomVector<SearchResult>& results, const CustomVector<FileInfo>& files, const string& query);
void openFile(const FileInfo& file);