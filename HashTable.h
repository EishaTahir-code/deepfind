#pragma once
#include<string>
#include "vector.h"

template <class K, class V>
class HashNode{
    public:
    K key;
    V val;
    HashNode* next;

    HashNode(K k, V v){
        key = k;
        val = v;
        next = NULL;
          
    }
};

