// implementation of a Circular Queue
// code developed by Krishna Narasimhan Agaram, CSE.

#include "queue.h"
// #include <iostream>

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return size() == 0; // self-explanatory
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    return (head - tail  + N) % N == 1; // the idea here is that the queue is full when the tail is just in front of the head when the queue is arranged like a clock with the hands of the clock being the head and the tail of the queue - in particular, only N-1 elements can be stored in the N-sized queue, and the queue is full if head - tail is 1 (or 1-N in the case tail > head, where tail must be N-1 and head 0 for a full queue) or (head - tail + N) % N == 1. The + N is to make the argument of the mod positive. 
}

template <typename T>
void DynamicQueue<T>::grow(){
    int oldsize = N-1;
    N = nextSize(); // increase array size.
    T *new_arr = new T[N]; // create a new array of this larger size
    
    // copy over the oldsize elements from the existing queue.
    int j = 0;
    for (int i = head; j < oldsize; i = (i + 1)%N)
        new_arr[j++] = A[i];
    
    delete[] A; // free original memory
    
    // assign A, head, tail values to the new array.
    A = new_arr;
    head = 0; // start index = 0
    tail = j; // the tail of the new array is j(or oldsize)
    
    // std::cout << "After grow, Tail: " << tail << std::endl;
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return (tail - head + N) % N; // The size is tail - head, yes, but to account for the fact that head and tail may have been reduced by N on wraparound the size is tail - head modulo N, and to keep the argument to mod positive, we add the + N as usual.
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if (isFull()) grow(); // we must ensure the array can accomodate the new element.
    
    // add the new element and update the tail index
    A[tail] = x;
    tail = (tail + 1) % N; // allow for wraparound.
    
    // std::cout << "Head: " << head << " Tail: " << tail << std::endl;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){

    // nothing to delete here, the specification requires us to return false in this case.
    if (isEmpty()) return false;

    // copy in the element to delete to the address in x
    *x = A[head];
    head = (head + 1) % N; // update the head variable.
    
    // std::cout << "Head: " << head << " Tail: " << tail << std::endl;
    return true; // succesful deletion
}