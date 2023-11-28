#include <iostream>
#include "queue.h"
using namespace std;

template <typename T>
bool DynamicQueue<T>::isEmpty(){ // return true if queue is empty
    return (head == tail);
}

template <typename T>
bool DynamicQueue<T>::isFull(){ // return true if queue is full
        return (tail == head - 1 || (head == 0 && tail == N-1)); // true is tail is just before head   
}                                           // or head is at 0 and tail is at N-1

template <typename T>
void DynamicQueue<T>::grow(){  // this will creat a new array with bigger size 
    int NEW_SIZE = nextSize();  
    T* B = new T[NEW_SIZE];    
    int current_size = size(); // current size of the array 
    for (size_t i = head; i < head + current_size ; i++) // coping element to new array 
    {
        B[i-head] = A[i%N];                              // from 0th index of new array
    }
    head = 0;
    tail = current_size; // updating head and tail
    delete[] A; // delete previous array
    A = B;      // assign new array to A
    N = NEW_SIZE;// updating current size
}

template <typename T>
unsigned int DynamicQueue<T>::size(){ // return number of element in the queue
    if (tail < head)    // if tail is less then head 
    {
        return N - (head - tail); 
    }
    return (tail - head); // normal case
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){ // insert new element at last
    if (isFull()){ // if array is full then grow will increase array size
        grow();
    }
    A[tail] = x; // new element will added to the last
    tail = ++tail % N; // updating tail
    return;   
}

template<typename T>
bool DynamicQueue<T>::QDelete(T *x){    // deleting the first element
    if (size() != 0)    // if size not equal to 
    {
        *x = A[head];   // A[head] will stored to x 
        head = ++ head % N; // and head will increase 
        return true;    
    }
    return false; // return true if size is not zero otherwise return false
}
