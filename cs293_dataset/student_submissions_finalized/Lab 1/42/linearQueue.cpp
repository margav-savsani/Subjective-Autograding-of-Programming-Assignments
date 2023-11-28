#ifndef LINQ_H //Just in case the file was copied twice
#define LINQ_H
#include<iostream>

using namespace std;

template <typename T>
bool DynamicQueue<T>::isEmpty(){ // If the head and tail point to the same element, it means the queue is empty, 
    return (head == tail);
}

template <typename T>
bool DynamicQueue<T>::isFull(){ 
    // If the head points to 0 and the tail points to N (Even though tail is out of bounds, I would call the grow function if I'm adding something at this point, so the queue resizes and the tail is now valid and the correct place of insertion for the bigger array)

    // Also this would not be true if just the tail was at N, since I could shift all the elements so that the head becomes 0 and the tail would no longer be N

    return ((head == 0) && (tail == N));
}

template <typename T>
void DynamicQueue<T>::grow(){

    // The nextSize() function increases the value of N, but only when the array is full , i.e., no space left in the array (even after adjustment and shifting).

    // A new array B is defined, with the size being the new length of the queue. The old array is then deleted, but that just deletes the space and not the pointer, which we point again to the new queue.

    if (isFull()) {
        N = nextSize();
        T *B = new T[N];
        for (int i=0;i<tail;i++){
            B[i] = A[i];
        }
        delete[] A;
        A = B;
    }
}

template <typename T>
unsigned int DynamicQueue<T>::size(){

    // The size is as calculated below, will work for all tail and head, even if head is 0 or tail is N

    return (tail - head);
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){

    // Two cases here, but before entering the cases, I grow the size of the queue (It will only grow if the array is really full)
    
    //First is when the tail is at N but the head is not at 0, in which case, I shift all the elements backwards to make room for the new element, after which I then reset the values of head and tail. 
    
    //The second is the normal case, where I just insert the element and increment the tail.

    grow();
    if (tail == N){
        for (int i=head;i<tail;i++){
            A[i - head] = A[i];
        }
        A[tail - head] = x;
        tail = tail - head + 1;
        head = 0; 
    }
    else{
        A[tail] = x;
        tail++;
    }
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    // Here, I check for 2 cases, when the queue is empty and when the queue has some element in it. When the list is non-empty, I store the element to be deleted in the variable provided and increment the head pointer, while returning true. Else, I return false
    if (isEmpty()) return false;
    *x = A[head];
    head++;
    return true;
}

#endif