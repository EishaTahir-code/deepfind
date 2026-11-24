#pragma once
#include "HashTable.h"
template <typename T>
struct Node {
    T item;
    Node* next = nullptr;

};

template <typename T>
class CustomSet {

    Node<T>** buckets;  
    int count;           
    int capacity;       
    int bucketOf(const T& item) const {
        return int(hashKey(item) % (unsigned long)capacity);
    }

public:

CustomSet() {

        count = 0;
        capacity = 20;
        buckets = new Node<T>*[capacity];
        for(int i = 0 ; i < capacity ; i++) {
            buckets[i] = 0;
        }
     }

void insert(const T& item) {

    if (contains(item)) {
        return;
    } 

    int i = bucketOf(item);
    Node<T>* n = new Node<T>;
    n->item = item;
    n->next = buckets[i];
    buckets[i] = n;
    count++; 

}
// checks if the word is  found
bool contains(const T& item) const { 

    Node<T>* curr = buckets[bucketOf(item)];
    while(curr) {

        if(curr->item == item) {
        return true;
            }
        curr = curr->next;

        }
        return false;
}

//finds the word and if found fix the links and remove the node
void remove(const T& item) {
 int i = bucketOf(item);
 Node<T>* prev = nullptr;
 Node<T>* curr = buckets[i];
 while(curr) {
    if(curr->item == item) {
        if(prev) {
            prev->next = curr->next;
        }
        else {
            buckets[i] = curr->next;
        }
        delete curr;
        count--;
        return;
    }
   prev = curr;
   curr = curr->next;
}

}
//destructor
~CustomSet() {
    for (int i = 0; i < capacity; i++) {
        Node<T>* curr = buckets[i];
        while (curr) {
            Node<T>* next = curr->next;
            delete curr;
            curr = next;
        }
    }
    delete[] buckets;
}
// GETS SIZE
int size() const {
        return count;
    }

//copy constructor 
CustomSet(const CustomSet& other) : CustomSet() {
  
    CustomVector<T> all = other.items();
    for (int i = 0; i < all.size(); i++) insert(all[i]);
}
  CustomSet& operator=(const CustomSet&) = delete;

CustomVector<T> items() const {
CustomVector<T> all;
    for(int i = 0 ; i < capacity ; i ++) {
         for(Node<T>* curr = buckets[i]; curr ; curr = curr->next) {
           all.push_back(curr->item);
        
            }
        }
         return all;
     }
};

inline CustomSet<std::string> makeStopWords() {
    const char* words[] = {
        "the", "is", "a", "an", "and", "of", "to", "in", "on", "at",
        "by", "with", "it", "its", "that", "be", "are", "was", "were", "been",
        "as", "from", "but", "so", "than", "then", "there", "these", "those", "which",
        "who", "what", "will", "can", "has", "have", "had", "he", "she", "they", "we", "you"
    };
    int n = sizeof(words) / sizeof(words[0]);

    CustomSet<std::string> s;
    for (int i = 0; i < n; i++) s.insert(words[i]);
    return s;
}