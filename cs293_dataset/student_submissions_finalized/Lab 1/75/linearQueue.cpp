#include <iostream>
#include "queue.h"
using namespace std;

// Accessor methods

// To check whether queue is empty
template <class T>
bool DynamicQueue<T>:: isEmpty()
{
    return (tail == head); // The queue is empty if tail = head of the array
}

// To check whether queue is full
template <class T>
bool DynamicQueue<T>:: isFull(){
    return (tail == N); // The queue is empty if tail refers to the element after the last elements of the array
}

// To return the current number of elements in the queue
template <class T>
unsigned int DynamicQueue<T>:: size(){
    return (tail - head); // Number of elements = tail - head 
}

// Modifier methods

// To grow the array representing the queue
template <class T>
void DynamicQueue<T>:: grow(){
    T *NewArray; int N_old;

    NewArray = new T[nextSize()]; // NewArray is the new, longer Queue in which the elements of the old array will be copied
    N_old = N; // N_old stores the size of the old array for the purpose of copying the old array into the new one

    // If NewArray has been correctly allocated, update the size of Queue (N)
    if (NewArray != nullptr) N = nextSize();
    else N = 0;
    
    // To copy the elements of the old array into the new one
    for(int i = 0; i<size();i++){ // becuase an N lengthed array can store only n elements at max
        NewArray[i] = A[head + i];
    }


    tail = size(); // Reallocate the tail pointer to point at the correct index after growing the array
    head = 0; // Reallocate the head pointer to the 0th position after growing the array 
    
    delete A; // delete the dynamically allocated array A to free up memory.
    A = NewArray; // To make pointer A to point to the new array dynamically created
}

// To delete element in the queue head if it is non empty
template <class T>
bool DynamicQueue<T>:: QDelete(T *x){
    if(isEmpty()){
        x = nullptr; // to allocate x to a null pointer if the queue is empty
        return false; // to return false if the queue is empty
    }
    else{
        *x = A[head]; // the element at the head copied into *T

        head++; // To increment the position of the head
        return true; // return true because the queue was not empty
    }
}

// To insert new element into the queue
template <class T>
void DynamicQueue<T>:: QInsert(T x){

    if(isFull()){
        grow(); // to allocate a larger array if the initial array is full
    }
    A[tail] = x; // to place the new object in the queue
    tail = (tail + 1);
}


