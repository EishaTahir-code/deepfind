#include "ranker.h"
#include<iostream>
#include<cstdlib>
#include "maxheap.h"
#include "sorter.h"
using namespace std;

//To put occurences in increasing line order
static bool lineBefore(const Occurrence& a, const Occurrence& b){
    return a.lineNumber<b.lineNumber;
}

//using maxheap best result is taken from top
CustomVector<SearchResult> rankResults(const CustomVector<SearchResult>& options, int k){
    CustomMaxHeap<SearchResult> heap;
    for(int i=0; i<options.size(); i++){
        SearchResult r=options[i];
        r.score=r.wordCount;
        customSort(r.occurrences, lineBefore);
        //join repeat of same lines
        CustomVector<Occurrence> merged;
        for(int j=0; j<r.occurrences.size(); j++){
            if(!merged.empty() && merged.back().lineNumber==r.occurrences[j].lineNumber){
                merged.back().timesOnLine+=r.occurrences[j].timesOnLine;
            }
            else{
                merged.push_back(r.occurrences[j]);
            }
        }
        r.occurrences=merged;
        heap.insert(r);
    }
    CustomVector<SearchResult> results;
    while(!heap.isEmpty() && (k<=0 || results.size()<k)){
        results.push_back(heap.extractMax());
    }
    return results;
}

//prints result to screen
void printResults(const CustomVector<SearchResult>& results, const CustomVector<FileInfo>& files, const string& query){
    if(results.empty()){
        cout<<"No file contains "<<query<<endl;
        return;
    }
    for(int i=0; i<results.size(); i++){
        const SearchResult& r=results[i];
        const FileInfo& file=files[r.fileId];
        cout<<i+1<<". "<<file.path;
        cout<<"Found "<<r.wordCount<<" times"<<endl;
        for(int j=0; j<r.occurrences.size() && j<3; j++){
            int line=r.occurrences[j].lineNumber;
            cout<<" Line: "<<line+1<<": "<<file.lines[line]<<endl;
        }
    }
}

//opens file in default program
void openFile(const FileInfo& file){
    string command="\""+file.path+"\"";
    system(command.c_str());
}