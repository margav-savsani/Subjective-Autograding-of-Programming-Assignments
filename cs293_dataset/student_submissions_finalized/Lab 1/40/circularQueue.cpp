#include "queue.h"
#include<iostream>
using namespace std;

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return (N - head + tail)%N;               //way of calculating size of a circular queue
}

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return (size() == 0);                     //if size is 0 then array is empty
}
template <typename T>
bool DynamicQueue<T>::isFull(){
    return (size() == N-1);                     //for a circular array if the size is N-1 it is considered FULL. 
                                                //because head == tails is the condition for empty list so if we add one more element
                                                //to make the size N it will result in ambiguity as to whether the list is empty or full                
}
template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()) grow();                        //incrementing the array if the list is full
    tail = (tail + 1)%N;                        //we use mod because it is a circular array ie after N-1, 0 comes not N
    A[tail] = x;
}
template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(head == tail) return false;              //head == tail is the condition of empty array and it's not possible to delete from empty array
    *x = A[head];
    head = (head+1)%N;                          //we again use mod because it's a circular array
    return true;
}
template <typename T>
void DynamicQueue<T>::grow(){
     T* B;                                      //we make a new array with increased size
    B = new T[nextSize()];
    for (int i = 0; i < N; i++)
    {
        B[i] = A[i];
    }
    A = B;  
    N = nextSize();                               
}
