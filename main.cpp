#include <iostream>
#include <conio.h>
#include "QueryEngine.h"
#include "ranker.h"
#include "Indexer.h"
using namespace std;

string rwsuggest(const CustomTrie& trie) {
    string written;
    while (true) {
        string word = written;
        for (int i = 0; i < (int)written.size(); i++) {
            if (written[i] == ' ') word = written.substr(i + 1);
        }
        for (int i = 0; i < (int)word.size(); i++) {
            word[i] = tolower((unsigned char)word[i]);
        }

        cout << "\n> " << written << "    [ ";
        CustomVector<Suggestion> s = trie.getSuggestions(word, 5);
        for (int i = 0; i < s.size(); i++)  {
            cout << s[i].word << " "; }
        cout << "]";

    int key = _getch();
        if (key == 13) {
            cout << "\n";
            return written;
        }
        if (key == 8 && !written.empty()) written.pop_back();
     else if (key >= 32 && key < 127) written += (char)key;
    }
}

int main(int argc, char* argv[]) {
    string folder;
    if (argc > 1) folder = argv[1];
    else {
        cout << "Folder to index: ";
        getline(cin, folder);
    }
    if (folder.size() >= 2 && folder[0] == '"') {
        folder = folder.substr(1, folder.size() - 2);
    }

    CustomSet<string> stopWords = makeStopWords();
    Indexer indexer;
    if (!indexer.buildIndex(folder, stopWords))  {
        return 1; }

    CustomTrie trie;
    buildTrie(trie, indexer);
    cout << "Indexed " << indexer.get_files().size() << " files, "
  << indexer.get_index().size() << " unique words\n";

    CustomVector<SearchResult> lastResults;

    while (true) {
        cout << "\n1 Search   2 Search with suggestions   3 Open a result   0 Quit\n> ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore(1000, '\n');

        if (choice == 0) {break; }

        if (choice == 1 || choice == 2) {
            string query;
            if (choice == 1) {
                cout << "Search: ";
                getline(cin, query);
            } 
            else {
                query = rwsuggest(trie);
            }
            lastResults = rankResults(findCandidates(query, stopWords, indexer));
     printResults(lastResults, indexer.get_files(), query);
        }
        else if (choice == 3) {
            if (lastResults.empty()) {
                cout << "Search for something first.\n";
                continue;
            }
            int n;
        cout << "Result number (1-" << lastResults.size() << "): ";
        cin >> n;
        cin.ignore(1000, '\n');
        if (n < 1 || n > lastResults.size()) {
                cout << "That is not one of the results.\n";
            } else {
                openFile(indexer.get_files()[lastResults[n - 1].fileId]);
            }
        }
    else {
            cout << "Please type 0, 1, 2 or 3.\n";
        }
    }
    cout << "Thanks and goodbye!\n";
    return 0;
}