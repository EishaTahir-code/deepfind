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
    void push_back(){

    }
    void pop_back(){

    }
};