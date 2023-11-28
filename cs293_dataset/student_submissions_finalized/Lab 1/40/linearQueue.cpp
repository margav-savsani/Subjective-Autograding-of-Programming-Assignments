#include "queue.h"
#include<iostream>
using namespace std;

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return (tail - head);                     //this is the size of an array in linear queue
}

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return (size() == 0);                     //checking for size and comparing with 0 (empty case)
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    return (size() == N);                     //size will be N (size of array) if it is full
}
template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()) grow();              //if the array has N elements ie it's actually full we just increase the size
    else if (tail == N){                    //if the array is not really full but we can't add an element due to tail reaching 
        for (int i = 0; i < size(); i++)    //the end of array we just shift all the elements to the left such that head becomes 0
        {
            A[i] = A[i + head];               //shifting elements 'head' units to the left
        }
        tail = tail - head;                   //assigning the new positions for head and tail
        head = 0;
    }
    A[tail] = x;                              //element added in position
    tail = tail + 1;                          //tail increments by one because element is added         
}
template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(head == tail) return false;            //case of empty list due to which we can't delete element
    *x = A[head];                            
    head = head + 1;                          //incrementing head 
    return true;
}
template <typename T>
void DynamicQueue<T>::grow(){
    T* B;
    B = new T[nextSize()];
    for (int i = 0; i < N; i++)
    {
        B[i] = A[i];
    }
    A = B;  
    N = nextSize();                          
}