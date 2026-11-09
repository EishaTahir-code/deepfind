#include<iostream>
#include<stdexcept>
using namespace std;

template <class T>
class CustomVector{
    T* data;
    int count;
    int capacity;

    public:
    CustomVector(){
        data = nullptr;
        count = 0;
        capacity = 0;
    }
    int size(){
        return count;
    }
    bool isEmpty(){
        return count == 0;
    }
    void push_back(T val){
        if(count==capacity){
            grow();
        }
        data[count++] = val;
    }
    void pop_back(){
        if(count == 0){
            throw out_of_range("pop_back on an empty CustomVector");
        }
        count--;
        data[count] = T();
    }
    void clear(){
        for(int i = 0; i<count; i++){
            data[i] = T();
        }
        count = 0;
    }
    ~CustomVector(){
        delete [] data;
    }
};