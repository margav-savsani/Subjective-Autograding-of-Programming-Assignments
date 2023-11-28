#include <iostream>
#include "queue.h"
using namespace std;

template <typename T>
bool DynamicQueue<T>::isEmpty(){ // return true if queue is empty by checking 
    return (head == tail);       // is head and tail are equal or not
}

template <typename T>
bool DynamicQueue<T>::isFull(){ // retun true if queue is full by checking
    return (N == (tail-head));  // is tail - head is equal to N or not
}

template <typename T>
void DynamicQueue<T>::grow(){ // this will creat a new array with bigger size 
    int NEW_SIZE = nextSize();  
    T* B = new T[NEW_SIZE];
    for (size_t i = head; i < tail; i++) // copy all elements between head and tail to new array
    {
        B[i-head] = A[i];
    }
    tail = size(); // update head and tail
    head = 0;
    delete[] A; // delete previous array and asign new array to A
    A = B;
    N = NEW_SIZE;  // updating current size of array
}

template <typename T>
unsigned int DynamicQueue<T>::size(){ // return no of elements in the array
    return (tail - head);
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){ // insert element to the tail
    if (tail >= N){                 // if tail is at last then array will grow 
        grow();              
    }
    A[tail] = x;    // assign new element to tail and increment of tail by 1
    tail ++;
    return;   
}

template<typename T>
bool DynamicQueue<T>::QDelete(T *x){ // delete element at head
    if (size() != 0)
    {
        *x = A[head];   // assign the value of the head to this pointer
        head ++;        // increment of head by 1
        return true;    // if size not equal to zero
    }
    return false;
}
