#include <iostream>
#include "queue.h"
using namespace std;


template <typename T> bool DynamicQueue<T>::isEmpty(){
    if(head > tail)
        return true; // if head is greater than tail then the queue is empty
    else if (head == tail == 0){
        return true; // no elements in the queue
    }else 
        return false;
}

template <typename T> bool DynamicQueue<T>::isFull(){
    if (tail > head){
        if (head == 0 && tail== N-1)
            return true; // if head is 0 and tail is N-1 then the queue is full
        else return false; // if tail is greater than head and tail and head these are not at the end and at the beginning of the queue respectively
    } else if (tail < head){
        if (head - tail == 1)
            return true; // the next element to tail is head 
        else return false; // space is present in between head and tail
    } else
        return false; // when head = tail
}

template <typename T> void DynamicQueue<T>::grow(){
    if (isFull()){
        N = nextSize();
    }
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    if (tail > head){
        return tail - head + 1; //queue stored in a single line
    } else if (tail < head){
        return 7 + tail - head; // queue stored at the beginning and at the end, the middle is empty;
    } else if (tail == head == 0){
        return 0; 
    }
        return 1; // when head and tail are equal, but not 0 
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    if (isFull()){
        grow(); tail++;
        A[tail] = x;
        N++; 
    } else {
        tail++;
        A[tail] = x;
        N++; 
    }
    if (head == 0){
        head++;
    }
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if (isEmpty()){
        return false;
    } else {
        head++;
        return true;
    }
}