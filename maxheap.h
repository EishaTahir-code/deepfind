#pragma once
#include<stdexcept>
#include "vector.h"

template<typename T>
class CustomMaxHeap{
    private:
    CustomVector<T> tree;
    int parent(int i) const{
        return (i-1)/2;
    }
    int leftChild(int i) const{
        return 2*i+1;
    }
    int rightChild(int i) const{
        return 2*i+2;
    }

    void swap(int v1, int v2){
        T temp=tree[v1];
        tree[v1]=tree[v2];
        tree[v2]=temp;
    }

    void heapifyUp(int i){
        while(i>0 && tree[i]>tree[parent(i)]){
            swap(i, parent(i));
            i=parent(i);
        }
    }

    void heapifyDown(int i){
        while(true){
            int max=i;
            int l=leftChild(i);
            int r=rightChild(i);
            if(l<tree.size() && tree[l]>tree[max]){
                max=l;
            }
            if(r<tree.size() && tree[r]>tree[max]){
                max=r;
            }
            if(max==i){
                return;
            }
            swap(i, max);
            i=max;
        }
    }

    public:
    bool isEmpty() const{
        return tree.empty();
    }

    int size() const{
        return tree.size();
    }

    void insert(const T& t){
        tree.push_back(t);
        heapifyUp(tree.size()-1);
    }

    T extractMax(){
        if(tree.empty()){
            throw std::out_of_range("extractMax cannot be done on an empty heap");
        }
        T max=tree[0];
        tree[0]=tree.back();
        tree.pop_back();
        if(!tree.empty()){
            heapifyDown(0);
        }
        return max;
    }
};