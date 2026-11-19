//autocompletes
#pragma once
#include <string>
#include "vector.h"
#include "sorter.h"

const int SLOTS = 37;
inline int slotOf(char c) {
    if(c >= 'a' && c <= 'z') {
        return c-'a';
    }
    if(c>= '0' && c <= '9') {
        return 26+(c - '0');
    }
    if(c == '_') {
        return 36;
    }
    return -1;
}
inline char charOf(int slot) {
    if(slot < 26) {
        return 'a'+slot;
    }
    if (slot < 36) {
        return '0'+(slot-26);
    }
    return '_';
}
struct TrieNode {
    TrieNode* children[SLOTS] = {};
    bool isWord = false;
    int frequency = 0;

    ~TrieNode() {
        for(int i =0 ; i < SLOTS ; i++) {
            delete children[i];
        }
    }
};
struct Suggestion{
    std::string word;
    int frequency = 0;
    
};

inline bool moreFrequent(const Suggestion& a, const Suggestion& b) {
    if(a.frequency != b.frequency) {
        return a.frequency > b.frequency;
    }
    return a.word < b.word;
}
class CustomTrie{
TrieNode* root = new TrieNode();


const TrieNode* walk(const std::string& text) const {
    const TrieNode* node = root;
    for(int i = 0 ; i < (int)text.size();i++) {
        int slot = slotOf(text[i]);
        if(slot < 0 || node->children[slot] == nullptr) {
            return nullptr;
        }
        node = node->children[slot];
    }
    return node;
}
void collect(const TrieNode* node, std:: string& word,CustomVector<Suggestion>& out) const {
    if(node->isWord) {
      Suggestion s;
      s.word = word;
      s.frequency = node->frequency;
      out.push_back(s);

    }
    for(int i = 0 ; i < SLOTS;i++){
        if(node->children[i] != nullptr) {
            word.push_back(charOf(i));
            collect(node->children[i],word,out);
            word.pop_back();
        }
    }
}
public:
~CustomTrie() {
    delete root;
}
CustomTrie() = default;
CustomTrie(const CustomTrie&) = delete;
CustomTrie& operator=(const CustomTrie&) = delete;

void insert(const std::string& word,int frequency) {
    if(word.empty()) return;

    for(int i = 0 ; i < (int)word.size() ; i++) {
        if(slotOf(word[i]) < 0) {
            return;        }
    }
    TrieNode* node = root;
    for(int i = 0 ; i < (int)word.size() ; i++) {
        int slot = slotOf(word[i]);
    if(node->children[slot] == nullptr) 
    node->children[slot] = new TrieNode();
    node = node->children[slot];
}
node->isWord = true; 
node->isWord = true;
node->frequency += frequency;
}
bool search(const std::string& word) const  {
    const TrieNode* node = walk(word);
    return node != nullptr && node->isWord;
}
CustomVector<Suggestion> getSuggestions(const std::string& prefix, int limit = 5) const {
CustomVector<Suggestion> all;
        const TrieNode* start = walk(prefix);
        if (start == nullptr) {
            return all;
        }

        std::string word = prefix;
        collect(start, word, all);
        customSort(all, moreFrequent);

        CustomVector<Suggestion> best;
        for (int i = 0; i < all.size() && i < limit; i++) {
            best.push_back(all[i]);
        }
        return best;
    }};