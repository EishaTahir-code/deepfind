#include <iostream>             
#include <fstream>             
#include <filesystem>         
#include <string>            
#include "Vector.h"            
#include "HashTable.h"        
#include "Indexer.h"             

static int failures = 0;        

static void check(bool condition, const std::string& name){  
    if(condition){                                         
        std::cout<<"PASS  "<<name<<"\n";              
    } 
    else{                                                
        std::cout<<"FAIL  "<<name<<"\n";                
        failures++;
    }
}                                                         

int main(){
    CustomVector <int> numbers;
    for(int i = 0; i < 100000; i++){
        numbers.push_back(i);
    }
    check(numbers.size() == 100000, "push_back 100,000 items");
    check(numbers[0] == 0 && numbers[99999] == 99999, "operator[] reads the right items");

    CustomVector <int> copy = numbers;
    copy[0] = -1;
    check(numbers[0] == 0, "copy constructor makes an independent copy");

    CustomVector <int> assigned;
    assigned.push_back(7);
    assigned = numbers;
    assigned[1] = -1;
    check(numbers[1] == 1 && assigned.size() == 100000, "copy assignment makes an independent copy");  // original unchanged, copy complete

    CustomVector<CustomVector<std::string>> nested;
    CustomVector<std::string> inner;
    inner.push_back("hello");
    nested.push_back(inner);
    CustomVector<CustomVector<std::string>> nestedCopy = nested;
    nestedCopy[0][0] = "changed";
    check(nested[0][0] == "hello", "nested vectors copy deeply");

    numbers.pop_back();
    check(numbers.size() == 99999 && numbers.back() == 99998, "pop_back and back");

    bool threw = false;
    try{
        CustomVector<int> emptyOne;
        emptyOne.pop_back();
    } 
    catch(const std::out_of_range&){
        threw = true;
    }
    check(threw, "pop_back on an empty vector throws");

    numbers.clear();
    check(numbers.empty() && numbers.size() == 0, "clear empties the vector");

    CustomHashTable<std::string, int> table;
    for(int i = 0; i < 10000; i++){
        table.insert("word" + std::to_string(i), i);
    }
    check(table.size() == 10000, "insert 10,000 words");
    bool allFound = true;
    for(int i = 0; i < 10000; i++){
        int* value = table.find("word" + std::to_string(i));
        if (value == nullptr || *value != i) allFound = false;
    } 
    check(allFound, "find returns every stored value after rehashing");
    table.insert("word5", 500);
    check(*table.find("word5") == 500 && table.size() == 10000, "insert overwrites an existing key");
    check(!table.contains("missing") && table.find("missing") == nullptr, "a missing key is reported missing");
    check(table.keys().size() == 10000, "keys returns every key");

    Indexer idx;
    CustomVector<std::string> t = idx.tokenize("int my_var = Stack(3); // done.");
    check(t.size() == 5 && t[0] == "int" && t[1] == "my_var" && t[2] == "stack" && t[3] == "3" && t[4] == "done",
          "tokenize lowercases, keeps '_' and splits on symbols");
    check(idx.tokenize("  ;;{}()  ").size() == 0, "a line of only symbols has no words");

    namespace fs = std::filesystem;
    fs::path dir = fs::temp_directory_path() / "deepfind_test_indexer";
    fs::remove_all(dir);
    fs::create_directories(dir / "sub");
    std::ofstream fileA(dir / "a.txt");
    fileA<<"The stack is full.\nstack stack queue\n";
    fileA.close();
    std::ofstream fileB(dir / "sub" / "b.cpp");
    fileB<<"Stack s; // a stack\n";
    fileB.close();
    std::ofstream fileC(dir / "c.md");
    fileC<<"stack\n";
    fileC.close();

    bool ok = idx.buildIndex(dir.string(), makeStopWords());
    check(ok && idx.get_files().size() == 2, "buildIndex finds only .txt/.cpp/.h files, including subfolders");
    CustomVector<FilePosting>* postings = idx.get_index().find("stack");
    check(postings != nullptr && postings->size() == 2, "\"stack\" is found in 2 files");
    bool aIsRight = false;
    for(int i = 0; postings != nullptr && i < postings->size(); i++){ 
        const FilePosting& p = (*postings)[i];
        const std::string& path = idx.get_files()[p.fileId].path;
        if(path.size() >= 5 && path.substr(path.size() - 5) == "a.txt"){
            aIsRight = p.wordCount == 3 && p.occurrences.size() == 2
                    && p.occurrences[0].lineNumber == 1 && p.occurrences[0].timesOnLine == 1 
                    && p.occurrences[1].lineNumber == 2 && p.occurrences[1].timesOnLine == 2;
        }
    }
    check(aIsRight, "counts and line numbers for a.txt are right");
    check(idx.get_index().find("the") == nullptr, "stop words are not indexed"); 
    fs::remove_all(dir);

    std::cout<<"\n"<<(failures == 0 ? "All tests passed." : "Some tests FAILED.")<<"\n";
    return failures == 0 ? 0 : 1;
}
