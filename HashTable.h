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
        next = nullptr;
    }
};

template <class K, class V>
class CustomHashTable{
    HashNode<K,V> **buckets;
    int count;
    int capacity;

    int getBucketIdx(const K& key){
        return hashKey(key)%capacity;
    }

    public:
    CustomHashTable(){
        count = 0;
        capacity = 16;
        buckets = new HashNode<K,V>* [capacity];
        for(int i= 0; i<capacity; i++){
            buckets[i] = nullptr;
        }
    }

    //to prevent from copying hashtable as require much space and time
    CustomHashTable(const CustomHashTable&) = delete;         
    CustomHashTable& operator=(const CustomHashTable&) = delete;

    V* find(const K& key){
        int index = getBucketIdx(key);
        HashNode<K,V>* temp = buckets[index];
        while(temp!=NULL){
            if(temp->key == key){
                return &(temp->val);
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void insert(const K& key, const V& val){
        int index = getBucketIdx(key);
        HashNode<K,v> newNode = new HashNode<K,V>(key,val);
        if(buckets[index] == NULL){   //linked list at that Idx is empty
            buckets[index] = newNode;
            return;
        }
        HashNode<K,V>* temp = buckets[index];
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }

    ~CustomHashTable(){
        for(int i = 0; i<capacity; i++){
            HashNode<K,V>* curr = buckets[i];
            while(curr != NULL){
                HashNode<K,V>* temp = curr;
                curr = curr->next;
                delete temp;
                temp = nullptr;
            }
        }
        delete [] buckets;
    }
};
