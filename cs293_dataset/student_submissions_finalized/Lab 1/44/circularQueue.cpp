#include <iostream>
#include "queue.h"
using namespace std;

// x----------------x-----------------Defining the DynamicQueue class's methods to implement a growable circular queue----------------x-----------------x

// boolean variable to determine whether last operation was insert or delete
bool last_call_QInsert = false; // helps to ascertain ths size(empty/full) of the queue when head = tail

template <typename T> unsigned int DynamicQueue<T> :: size(){
    if(head > tail){ // arises when the queue wraps around the array
        return N-head+tail; 
    }
    else if(head < tail){ // usual linearQueue case
        return tail-head;
    }

    // case when head = tail; last_call being true indicates that it was the insert function that led to this queue configuration and hence the queue is full (and not empty)
    else if(head == tail && last_call_QInsert == true){
        return N;
    }   
    else if (head == tail && last_call_QInsert == false){
        return 0;
    }
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
    T *B = new T[N];
    
// arises when the queue is full; the circular queue is unwrapped and stored as a linearQueue in a bigger(grown) circularQueue
    for(int i = 0; i<N; i++){
        B[i] = A[(i+head)%N];
    }
    tail = N;
    head = 0;
    N = nextSize();
    // the queue is grown and elements are brought back into the queue from the temporarily allocated memory
    T* A = new T[nextSize()];
    for (int i=0; i<N; i++){
        A[i] = B[i];
    }
  // delete[] B;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){ // deletes the element from a non-empty queue in accordance with the FIFO principle
    last_call_QInsert = false; // lets other functions know that the method QDelete() was called
    if(!isEmpty()){
        *x = A[head];
        A[head]=0;
        head = (head+1) % N; // updates the index of the "head" element with appropriate wrap-around in case the previous "head" was the last element of the queue
    }
    else if(isEmpty()) return false;
    else return true;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x){ // inserts the element "x" into the queue in-sync with the FIFO principle
    last_call_QInsert = true; // lets other functions know that the method QInsert() was called
    if(isFull()) grow();
    if(head !=0){ // case arises when the head is not the first element of the queue and the queue is not yet full
        A[tail]=x;
        tail = (tail+1) % N; // updates the index of "tail" with appropriate wrap-around in case the previous "tail" was the last element of the queue
    }
    else { // case arises when the queue is not full yet and the head is at the first index of the queue
        A[tail]=x;
        tail = (tail+1); 
        }
}
