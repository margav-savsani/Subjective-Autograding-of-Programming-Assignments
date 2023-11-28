#include <iostream>
using namespace std;
#include "queue.h"

template<typename T>
bool DynamicQueue<T>::isEmpty(){
    return (head==tail);            // queue empty when head and tail point to same index (can also be full)
}

template<typename T>
bool DynamicQueue<T>::isFull(){
    return tail==-1;                // queue full indicated by tail=-1
}

template<typename T>
void DynamicQueue<T>::grow(){
    unsigned int n = nextSize();        // stores size of enlarged array
    T *a = new T[n];                    // dummy array too store elements initially
    for(unsigned int i=0; i<N; i++)
        a[i] = A[(i+head)%N];           // copying of elements from original array to dummy : starting from the start of array
    delete[] A;
    head = 0;                           // new array stores elements from start
    tail = N;                           // next element to be added is at the end of the initial length
    A = a;                              // the dummy array now becomes our primary array
    N = n;                              // the array capacity has increased
}

template<typename T>
unsigned int DynamicQueue<T>::size(){
    if (tail==-1)
        return N;                       // array full
    return (tail+N - head)%N;           // takes into account both cases of tail<head & head<tail due to presence of +N with %N
}

template<typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()){
        grow();                     // increase array size before inserting new element
        A[tail] = x;                // inserting new element at the tail index
        tail+=1;                    // incrementing tail for upcoming element
    }
    else{
        A[tail] = x;                // inserting element
        tail = (tail+1)%N;          // altering tail to point at next available space in a circular fashion
        if (tail == head)
            tail = -1;              // indicates that the array is full


                                    // since there is no index available where new element can be inserted when aray full,
                                    // setting tail = -1 to indicate full array, else there is no way to differentiate
                                    // empty array from full array as in both cases head = tail
        // cout << head <<" " << tail <<endl;
        // for(unsigned int i=0; i<N; i++)
        //     cout<<A[i]<<" ";
        // cout<<endl;
    }
}

template<typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty())
        return false;                       // cannot delete element from an empty array
    *x = A[head];                           // x stores the value of deleted element
    if(isFull())
        tail = head;                        // if array is full: tail =-1, which has to be reset to value of head
                                            //      as empty space available now at head index and array no more full 
    head = (head+1)%N;                      // altering head to point to next deletable element in a circular fashion
    // for(unsigned int i=0; i<N; i++)
    //     cout<<A[i]<<" ";
    // cout<<endl;
    return true;
}