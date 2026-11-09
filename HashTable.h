#pragma once
#include<string>
#include "vector.h"

   /*inline - required when defining functions in header files
   to avoid linker errors (if the function is used by many files and it 
   is defined without inline then each file creates its own machine code 
   for these functions)*/

//djb2 - Hashing Function by Daniel J. Bernstein
inline unsigned long hashKey(const std::string& key){
    unsigned long hash = 5381;
    for(int i = 0; i<(int)key.size(); i++){ 
        unsigned long c = (unsigned char)key[i];
        hash = (hash*33) + c;
    }
    return hash;
}

//hash key for fileIDs (int)
//hash function - number itself bcz fileIDs are 0,1,2,3,...
inline unsigned long hashKey(int key){
    return (unsigned long)(unsigned int)key;
}

template <class K, class V>
class HashNode{
    public:
    K key;
    V val;
    HashNode* next;

    HashNode(const K& k, const V& v){
        key = k;
        val = v;
        next = NULL;
    }
};

