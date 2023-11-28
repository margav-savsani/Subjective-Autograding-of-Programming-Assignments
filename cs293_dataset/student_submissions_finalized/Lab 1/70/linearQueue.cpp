#include<iostream>
#include "queue.h"
using namespace std;

//this is an implementation of linear queue where each consecutive element
//is stored in array locations with consecutive indices and the first element is
//always at the array location with the smallest index

//my array implementation puts tail one index after the last entered element
//whereas head represents the first element, except when the queue is empty

template<typename T> bool DynamicQueue<T>:: isEmpty(){
    //returns true if the array is empty
    return(head==tail);
}
template<typename T> bool DynamicQueue<T>:: isFull(){
    //returns true if the array is full
    return(size()==N);
}
template<typename T> void DynamicQueue<T>:: grow(){
    //increases the size of the array linearly if the array is full
    //otherwise it just rearranges the array with the first element starting from index zero

    if(isFull()){
        N = nextSize(); //increase in size of the array if the array is full
    }
    //rearrangement with or without increase in size
    T *newA; newA = new T[N];   //temporary array with increased size if the array is full
    unsigned int newAelem = 0;
    unsigned int sz = size();
    for(unsigned int i = head; i < tail; i++){
        newA[newAelem] = A[i];  //copying of elements from primary array to the temporary array
        newAelem++;
    }
    head = 0; tail = sz;    //reassigning the head and tail after rearrangement
    A = newA;   //pointing the primary array towards the temporary array to get the desired array
}
template<typename T> unsigned int DynamicQueue<T>:: size(){
    //returns the number of elements in the array
    return(tail-head);
}
template<typename T> void DynamicQueue<T>:: QInsert(T x){
    if(tail==N) grow(); //if tail reaches the index after the end position of the array we call grow which performs rearrangement with/without increase in size
    A[tail] = x;    //insertion of new element at the tail position
    tail++; //new tail position
}
template<typename T> bool DynamicQueue<T>:: QDelete(T *x){
    //deletes the element at the head position by reassigning the head position to the second element in the array
    
    if(isEmpty()) return false; //returns false if the array is empty and there is nothing to delete
    else{
        *x = A[head];
        head++;
        return true;    //returns true if the operation is preformed successfully
    }
}