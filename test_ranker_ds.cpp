#include <iostream>
#include<string>
#include<stdexcept>
#include "maxheap.h"
#include "sorter.h"
#include "ranker.h"

int fail=0;
void check(bool pass, string test){
    if(pass){
        cout<<"Pass "<<test<<endl;
    }
    else{
        cout<<"Fail "<<test<<endl;
        fail++;
    }
}

//Sort numbers
bool small(const int& a, const int& b){
    return a<b;
}

//Sort higher score first
bool higherScore(const SearchResult& a, const SearchResult& b){
    return a.score>b.score;
}

//Fake search test result
SearchResult result(int id, int count, int terms){
    SearchResult s;
    s.fileId=id;
    s.wordCount=count;
    s.termsMatched=terms;
    return s;
}

//Fake occurrence
Occurrence makeOccurrence(int no){
    Occurrence o;
    o.lineNumber=no;
    o.timesOnLine=1;
    return o;
}

//Heap test
void testHeap(){
    CustomMaxHeap<int> heap;

    //inserting numbers into max heap
    int numbers[]={1, 20, 3, 42, 56};
    for(int i=0; i<5; i++){
        heap.insert(numbers[i]);
    }
    check(heap.size()==5, "All 5 present");

    //biggest number first
    bool inOrder=true;
    int prev=heap.extractMax();
    while(!heap.isEmpty()){
        int current=heap.extractMax();
        if(current>prev){
            inOrder=false;
        }
        prev=current;
    }
    check(inOrder, "Biggest to smallest");
    check(heap.isEmpty(), "empty heap");

    //empty heap should throw error
    bool threw=false;
    try{
        heap.extractMax();
    }catch(const out_of_range&){
        threw=true;
    }
    check(threw, "extractMax on empty results in error");
}

//sort test
void testSort(){
    CustomVector<int> v;
    //to input some num and sort them
    int n[]={5, 1, 6, 8, 2, 3};
    for(int i=0; i<6; i++){
        v.push_back(n[i]);
    }
    customSort(v, small);

    bool sort=true;
    for(int i=1; i<v.size(); i++){
        if(v[i-1]>v[i]){
            sort=false;
        }
    }
    check(sort && v.size()==6, "small to big");

    //empty and 1 list shouldn't crash
    CustomVector<int> empty;
    customSort(empty, small);
    CustomVector<int> one;
    one.push_back(33);
    customSort(one, small);
    check(empty.size()==0 && one.size()==1 && one[0]==33, "handles empty and 1 list");

    //equal scores keep orig order
    CustomVector<SearchResult> results;
    for(int i=0; i<6; i++){
        SearchResult r=result(i, 1, 1);
        if(i%2==0){
            r.score=10;
        }
        else{
            r.score=20;
        }
        results.push_back(r);
    }
    customSort(results, higherScore);
    check(results[0].fileId==1 && results[1].fileId==3 && results[2].fileId==5 && results[3].fileId==0 && results[4].fileId==2 && results[5].fileId==4, "sorted");
}

//rank test
void testRank(){
    //fake files
    CustomVector<SearchResult> options;
    options.push_back(result(0, 5, 1));
    options.push_back(result(1, 3, 1));
    options.push_back(result(2, 5, 1));

    CustomVector<SearchResult> top=rankResults(options);
    check(top.size()==3 && top[0].fileId==0 && top[1].fileId==2 && top[2].fileId==1, "similar to smaller file id");
    check(top[0].score==5, "score is set number of hits");

    check(rankResults(options, 2).size()==2, "k=2 returns 2");
    check(rankResults(options, 0).size()==3, "k=0 returns all");

    //for same number of hits, more matching words come first
    CustomVector<SearchResult> tie;
    tie.push_back(result(0, 4, 1));
    tie.push_back(result(1, 4, 2));
    (check(rankResults(tie)[0].fileId==1, "equal hits and more matched words wins"));

    CustomVector<SearchResult> none;
    check(rankResults(none).size()==0, "no input so no results");

    SearchResult r=result(0, 3, 1);
    r.occurrences.push_back(makeOccurrence(5));
    r.occurrences.push_back(makeOccurrence(1));
    r.occurrences.push_back(makeOccurrence(3));
    CustomVector<SearchResult> single;
    single.push_back(r);
    CustomVector<Occurrence> lines=rankResults(single)[0].occurrences;
    check(lines[0].lineNumber==1 && lines[1].lineNumber==3 && lines[2].lineNumber==5, "rank puts into order");
}

int main(){
    testHeap();
    testSort();
    testRank();

    cout<<endl;
    if(fail==0){
        cout<<"All Tests passed"<<endl;
        return 0;
    }
    cout<<fail<<" Tests failed"<<endl;
    return 1;
}