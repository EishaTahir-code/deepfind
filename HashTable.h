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

    int getBucketIdx(const K& key) const{
        return hashKey(key)%capacity;
    }

    HashNode<K,V>* findNode(const K& key) const{
        int index  = getBucketIdx(key);
        HashNode<K,V>* temp = buckets[index];
        while(temp != NULL){
            if(temp->key == key){
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
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
        HashNode<K,V>* temp = findNode(key);
        return (temp)? &(temp->val) : nullptr;
    }

    const V* find(const K& key) const{
        HashNode<K,V>* temp = findNode(key);
        return (temp)? &(temp->val) : nullptr;       
    }

    void insert(const K& key, const V& val){
        //if key exists so will overwrite its value
        HashNode<K,V>* exists = findNode(key);
        if(exists){
            exists->val = val;
            return;
        }
        int index = getBucketIdx(key);
        HashNode<K,V>* newNode = new HashNode<K,V>(key,val);

        newNode->next = buckets[index];
        buckets[index] = newNode;
        count++;
    }

    bool contains(const K& key) const{
        return (findNode(key))? true : false;
    }
    int size() const{
        return count;
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
