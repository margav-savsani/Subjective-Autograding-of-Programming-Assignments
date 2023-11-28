#include <iostream>
#include "queue.h"
using namespace std;

// x----------------x-----------------Defining the DynamicQueue class's methods to implement a growable linear queue----------------x-----------------x

template <typename T> unsigned int DynamicQueue<T> :: size(){
    return tail-head; // tail-head returns the number of elements present in the queue
}

template <typename T> bool DynamicQueue<T> :: isEmpty(){ // boolean method to check if the queue is empty
    if(size() == 0) return true;
    else return false;
}

template <typename T> bool DynamicQueue<T> :: isFull(){ // boolean method to check if the queue has reached it's max capacity
    if(size()==N) return true;
    else return false;
}

// method to extend the capacity of queue when current queue is completely filled
template <typename T> void DynamicQueue<T> :: grow(){

    // dynamically allocating an array of current queue size to temporarily store the elements while the size of the queue is increased
    T *B = new T[N];
    for (int i = 0; i<N; i++){
        B[i] = A[i];
    }
   
    // re-allocating a larger memory space of the queue
    T* A = new T[nextSize()]; //mextSize() private method returns the required increased capacity of the queue
    for (int i=0; i<N; i++){
        A[i] = B[i]; // storing the elements in the extended queue back again
    }
 //   delete[] B; //deallocating the dynamic memory used for temporarily storing the elements
    N = nextSize(); // updating the queue capacity in variable 'N'
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){ // deletes the element from a non-empty queue in accordance with the FIFO principle
    if(!isEmpty()){
        *x = A[head];
        A[head]=0; // sets the "head" element to zero
        head++; // the next element to the right becomes the new "head"
        return true;
    }
    else return false;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x){ // inserts the element "x" into the queue in-sync with the FIFO principle
    
    if(isFull()) grow(); // extends the capacity of the queue in case it is full
    
    // shifts back the elements to bring head to zeroth index in order to fill in more elements at higher indices
    else if (tail >= N) {
        for(int i = head; i < tail; i++){
            A[i-head] = A[i];
        }
        tail = size();
        head = 0 ;
    }
    
    // finally adding the element to the queue and updating the index of the tail
    A[tail]=x;
    tail++;
}


