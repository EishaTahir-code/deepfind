#pragma once
#include "vector.h"

template <typename T>
void merge(CustomVector<T>& arr1, CustomVector<T>& arr2, int left, int mid, int right, bool(*before)(const T&, const T&)){
    int i=left;
    int j=mid;
    int k=left;
    while(i<mid && j<right){
        if(before(arr1[j], arr1[i])){
            arr2[k++]=arr1[j++];
        }
        else{
            arr2[k++]=arr1[i++];
        }
    }
    while(j<right){
        arr2[k++]=arr1[j++];
    }
    while(i<mid){
        arr2[k++]=arr1[i++];
    }
    for(int a=left; a<right; a++){
        arr1[a]=arr2[a];
    }
}

template <typename T>
void mergesort(CustomVector<T>& arr1, CustomVector<T>& arr2, int left, int right, bool(*before)(const T&, const T&)){
    if((left-right)<2){
        return;
    }
    int mid=left+(right-left)/2;
    mergesort(arr1, arr2, left, mid, before);
    mergesort(arr1, arr2, mid, right, before);
    merge(arr1, arr2, left, mid, right, before);
}

template <typename T>
void customSort(CustomVector<T>& arr, bool(*before)(const T&, const T&)){
    CustomVector<T> arr2=arr;
    mergesort(arr, arr2, 0, arr.size(), before);
}