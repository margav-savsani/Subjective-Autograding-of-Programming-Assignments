// Linear Queue
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
void DynamicQueue<T>::grow(){ // grow the queue to its next size; takes O(N) time
    T * B = A;
    A = new T[nextSize()];
    for (int i = 0; i < N; i++){
        A[i] = B[i];
    }
    
    delete[] B;
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
        A[tail] = x;
        tail += 1;
        return;
    }
    /* If the queue is not full and the the tail didn't reach the end of array we just store normally.
    Takes O(1) */
    else if (tail != N){
        A[tail] = x;
        tail += 1;
        return;
    }
    
    /* If the queue is not full and the tail reached the end of array, we must move the elements to 
    the start of the array to create space, ie, move the head to 0. This takes O(N)*/
    for (int i = head; i < tail; i++){
        A[i-head] = A[i];
    }
    tail -= head;
    A[tail] = x;
    tail += 1;
    head = 0;
    return;
}
template <class T>
bool DynamicQueue<T>::QDelete(T *x){ // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
    if (isEmpty()){
        return 0;
    }
    *x = A[head];
    head += 1;
    return 1; 
}

/* This is for alternate makefile
For using the altenate Makefile (see README), we'll have to declare all the classes used in test.cpp here:

template class "classname"<"object type"> 

*/

// template class DynamicQueue<int>;
