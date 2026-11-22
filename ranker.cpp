#include "ranker.h"
#include<iostream>
#include<cstdlib>
#include "maxheap.h"
#include "sorter.h"
using namespace std;

//sorts occurrences by line number
static bool lineBefore(const Occurrence& a, const Occurrence& b){
    return a.lineNumber<b.lineNumber;
}

//best result is taken from top of max heap
CustomVector<SearchResult> rankResults(const CustomVector<SearchResult>& options, int k){
    CustomMaxHeap<SearchResult> heap;
    for(int i=0; i<options.size(); i++){
        SearchResult r=options[i];
        r.score=r.wordCount;
        customSort(r.occurrences, lineBefore);
        //same line repeated is joined
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

//removes spaces at start and cuts long lines
static string shorten(string text, int len){
    if(text.size()>=3 && text.compare(0, 3, "\xEF\xBB\xBF")==0){
        text.erase(0, 3);
    }
    int s=0;
    while(s<(int)text.size() && (text[s]==' ' || text[s]=='\t')){
        s++;
    }
    text=text.substr(s);
    if((int)text.size()>len){
        text=text.substr(0, len-3)+"...";
    }
    return text;
}

//prints result to screen
void printResults(const CustomVector<SearchResult>& results, const CustomVector<FileInfo>& files, const string& query){
    if(results.empty()){
        cout<<"\nNo results for \""<<query<<"\""<<endl;
        return;
    }
    if(results.size()==1){
        cout<<"\n1 file found for \""<<query<<"\""<<endl;
    }
    else{
        cout<<"\n"<<results.size()<<" files found for \""<<query<<"\""<<endl;
    }
    for(int i=0; i<results.size(); i++){
        const SearchResult& r=results[i];
        const FileInfo& file=files[r.fileId];
        cout<<"\n ["<<i+1<<"] "<<file.path<<"   ("<<r.wordCount;
        if(r.wordCount==1){
            cout<<" match)"<<endl;
        }
        else{
            cout<<" matches)"<<endl;
        }
        for(int j=0; j<r.occurrences.size() && j<3; j++){
            int line=r.occurrences[j].lineNumber;
            cout<<"     Line "<<line<<": "<<shorten(file.lines[line-1], 80)<<endl;
        }
        if(r.occurrences.size()>3){
            cout<<"     ...and "<<r.occurrences.size()-3<<" more lines"<<endl;
        }
    }
}

//opens file in default program
void openFile(const FileInfo& file){
    string command="start \"\" \""+file.path+"\"";
    system(command.c_str());
}