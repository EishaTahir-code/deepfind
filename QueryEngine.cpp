#include "QueryEngine.h"
using namespace std;
void buildTrie(CustomTrie& trie,Indexer& indexer){
    CustomVector<string> words = indexer.get_index().keys();
    for(int i = 0 ; i < words.size() ; i++) {
        CustomVector<FilePosting>* row = indexer.get_index().find(words[i]);
        int total = 0;
        for(int j = 0 ; j < row->size() ; j++) {
            total += (*row)[j].wordCount;
        }
        trie.insert(words[i],total);
    } }
    CustomVector<SearchResult> findCandidates(const string& query, const CustomSet<string>& stopWords,
                                          Indexer& indexer) {
        CustomVector<string> tokens = indexer.tokenize(query);
        CustomSet<string> seen;
        CustomVector<string> terms;
        for(int i = 0 ; i < tokens.size() ; i ++ ) {
            if(stopWords.contains(tokens[i]) || seen.contains(tokens[i])) {
                continue;
            }
            seen.insert(tokens[i]);
            terms.push_back(tokens[i]);
        }
        CustomVector<SearchResult> results;
        if(terms.empty()) return results;
        CustomVector <FilePosting>* first = indexer.get_index().find(terms[0]);
        if(first == nullptr) return results;
        
    for(int  p = 0 ; p < first->size(); p++) {
         SearchResult r;
    r.fileId = (*first)[p].fileId;
    r.wordCount = (*first)[p].wordCount;
    r.termsMatched = 1;
    r.occurrences = (*first)[p].occurrences;
    bool inAll = true;

    for (int t = 1; t < terms.size(); t++) {
        CustomVector<FilePosting>* other = indexer.get_index().find(terms[t]);
        bool found = false;

        if (other != nullptr) {
            for (int q = 0; q < other->size(); q++) {
                if ((*other)[q].fileId == r.fileId) {
                    r.wordCount += (*other)[q].wordCount;
                    r.termsMatched++;
                    for (int o = 0; o < (*other)[q].occurrences.size(); o++) {
                        r.occurrences.push_back((*other)[q].occurrences[o]);
                    }
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            inAll = false;
            break;
        }
    }

    if (inAll) {
        results.push_back(r);
    }
}
return results;
}
                                                                                    
