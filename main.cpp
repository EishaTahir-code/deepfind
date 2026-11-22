#include <iostream>
#include <string>
#include <conio.h>
#include "QueryEngine.h"
#include "ranker.h"
#include "Indexer.h"
using namespace std;

//word being typed right now
string lastWord(const string& typed){
    int space=(int)typed.find_last_of(' ');
    string word=typed.substr(space+1);
    for(int i=0; i<(int)word.size(); i++){
        word[i]=(char)tolower((unsigned char)word[i]);
    }
    return word;
}

//reads search and shows suggestions on same line
bool readSearch(const CustomTrie& trie, string& typed){
    typed="";
    int oldLen=0;
    while(true){
        CustomVector<Suggestion> s;
        string word=lastWord(typed);
        if(!word.empty()){
            s=trie.getSuggestions(word, 5);
        }
        string hint="";
        for(int i=0; i<s.size(); i++){
            if(i>0){
                hint+="  ";
            }
            hint+=s[i].word;
        }

        string prompt="Search: "+typed;
        string full=prompt;
        if(!hint.empty()){
            full+="      ("+hint+")";
        }
        cout<<"\r"<<full;
        if((int)full.size()<oldLen){
            cout<<string(oldLen-full.size(), ' ');
        }
        oldLen=(int)full.size();
        cout<<"\r"<<prompt<<flush;

        int key=_getch();
        if(key==0 || key==224){
            _getch();
            continue;
        }
        if(key==27){
            cout<<"\r"<<string(oldLen, ' ')<<"\r";
            return false;
        }
        if(key==13){
            cout<<"\r"<<string(oldLen, ' ')<<"\r"<<prompt<<endl;
            return true;
        }
        if(key==8){
            if(!typed.empty()){
                typed.pop_back();
            }
        }
        else if(key==9){
            if(s.size()>0){
                typed=typed.substr(0, typed.size()-word.size())+s[0].word;
            }
        }
        else if(key>=32 && key<127){
            typed+=(char)key;
        }
    }
}

int main(int argc, char* argv[]){
    string folder;
    if(argc>1){
        folder=argv[1];
    }
    else{
        cout<<"Folder to search: ";
        getline(cin, folder);
    }
    if(folder.size()>=2 && folder[0]=='"'){
        folder=folder.substr(1, folder.size()-2);
    }

    cout<<"Indexing "<<folder<<" ..."<<endl;
    CustomSet<string> stopWords=makeStopWords();
    Indexer indexer;
    if(!indexer.buildIndex(folder, stopWords)){
        return 1;
    }
    CustomTrie trie;
    buildTrie(trie, indexer);

    cout<<"\n=========================================="<<endl;
    cout<<"  DeepFind - "<<indexer.get_files().size()<<" files, "<<indexer.get_index().size()<<" words indexed"<<endl;
    cout<<"  Enter = search   Tab = complete word   Esc = quit"<<endl;
    cout<<"==========================================\n"<<endl;

    while(true){
        string query;
        if(!readSearch(trie, query)){
            break;
        }
        if(query.find_first_not_of(' ')==string::npos){
            continue;
        }

        CustomVector<SearchResult> results=rankResults(findCandidates(query, stopWords, indexer));
        printResults(results, indexer.get_files(), query);

        if(!results.empty()){
            cout<<"\nOpen a file (1-"<<results.size()<<") or press Enter to search again: ";
            string choice;
            getline(cin, choice);
            bool isNum=!choice.empty() && choice.find_first_not_of("0123456789")==string::npos;
            if(isNum){
                int n=stoi(choice);
                if(n>=1 && n<=results.size()){
                    openFile(indexer.get_files()[results[n-1].fileId]);
                    cout<<"Opening "<<indexer.get_files()[results[n-1].fileId].path<<endl;
                }
                else{
                    cout<<"That is not one of the results."<<endl;
                }
            }
        }
        cout<<"\n------------------------------------------\n"<<endl;
    }
    cout<<"Goodbye!"<<endl;
    return 0;
}