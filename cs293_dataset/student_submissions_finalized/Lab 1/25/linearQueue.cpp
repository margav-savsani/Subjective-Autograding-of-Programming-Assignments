#include <iostream>
#include "queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty() {
    // The queue is empty if the head and the tail point to the same element
    return (head==tail);
}

template <class T> bool DynamicQueue<T>::isFull() {
    // The queue is full if the head point to index 0 and tail points to index N
    // In any other case, we can rearrange the elements in the queue to make space at the tail
    return (head==0 && tail==N);
}

template <class T> unsigned int DynamicQueue<T>::size(){
    // The size of the contiguous memory location that currently stores the queue elements 
    // is (tail - head)
    return (tail-head);
}

template <class T> void DynamicQueue<T>::grow(){
    T *bigger;
    bigger = new T[nextSize()];
    // We make a new bigger array of typename T and copy the previous array into this one.
    for (int i=0; i<N; i++) {
        bigger[i] = A[i];
    }
    // Now that the old array has been copied into the larger array, we free the memory allocated to the previous array
    // Not doing so would result in memory leak as we wouldn't be able to access that region of memory, 
    // once we assign to pointer A the address to some other location (the new array in this case)
    delete[] A;
    // Now we assign the address of this new array to our queue pointer A
    A = bigger;
    // Update the size to complete the expansion
    N=nextSize();
}

template <class T> void DynamicQueue<T>::QInsert(T x){
    // If the Queue is full, we call the grow function.
    if (isFull()){
        grow();
        // Now the array is ready for insertion
    }
    else if (tail==N){
        /*
        The queue is not full, BUT the tail points to the end (one after the last element) of the array
        We cannot directly store the element in this out-of-bounds location
        We cannot also expand the array since it is not full, doing so would be a waste of memory.
        So we shift the entire contiguous memory location (the queue) storing elements (the region between head and tail)
        to the left of the array, thereby creating space on the right
        */
        for (int i=0; i<size(); i++) {
            A[i] = A[head+i];
        }
        // We update the tail to point to the end of this new shifted queue, and head to index to denote the left-shift
        tail=size(); head=0;
    }
    // Now that all things are taken care of, we append the new element to the queue.
    A[tail]=x; tail++;
}

template <class T> bool DynamicQueue<T>::QDelete(T *x){
    if (isEmpty()){
        // Cannot remove element from an empty queue
        return false;
    }
    // Store the element that is going to be removed into 'T' pointed to by 'x'
    *x=A[head];
    head++;
    return true;
}

