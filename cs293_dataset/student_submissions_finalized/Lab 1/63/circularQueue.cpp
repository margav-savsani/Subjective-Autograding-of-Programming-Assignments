// Circular Queue
# include "queue.h"

template <class T>
bool DynamicQueue<T>::isEmpty(){ // is the queue empty?
    if (size() == 0){
        return 1;
    }
    return 0;
} 
template <class T>
bool DynamicQueue<T>::isFull(){ // is the queue full?
    if (size() == N){
        return 1;
    }
    return 0;
}
template <class T>
void DynamicQueue<T>::grow(){ // grow the queue to its next size 
    T * B = A;
    A = new T[nextSize()];
    for (int i = 0; i < N; i++){
        A[i] = B[(i+head)%N];
    }
    delete[] B;
    head = 0;
    tail = N;
    N += CONST_GROWTH;
}
template <class T>
unsigned int DynamicQueue<T>::size(){ // return the current number of elements in the queue
    return tail-head;
}
template <class T>
void DynamicQueue<T>::QInsert(T x){ ; // insert given element at tail of the queue; grow array size as necessary
    /* If the queue is full we grow the queue with grow() function and store the element. Takes O(N)*/
    if (isFull()){  
        grow();
        A[tail%N] = x;
        tail += 1;
        return;
    }
    /* If the queue is not full and the the tail didn't reach the end of array we just store normally.
    Takes O(1) */
    A[tail%N] = x;
    tail += 1;
    if (head > N && tail > N){
        head -= N;
        tail -= N;
    }
    return;
}
template <class T>
bool DynamicQueue<T>::QDelete(T *x){ // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
    if (isEmpty()){
        return 0;
    }
    *x = A[head%N];
    head += 1;
    return 1; 
}


/* This is for alternate makefile
For using the altenate Makefile (see README), we'll have to declare all the classes used in test.cpp here:

template class "classname"<"object type"> 

*/

// template class DynamicQueue<int>;