#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){
    return (tail==head);
}
template <typename T> bool DynamicQueue<T>::isFull(){
    return (size()==N);
}
template <typename T> void DynamicQueue<T>::grow(){
    T *new_A;
    new_A = new T[nextSize()]; //created new pointer and now setting it size to nextSize.
    int i=head, j=0;
    while(i<N){
        new_A[j] = A[i];
        j++; i = (i+1)%N;
        if(j==size()) break; //in this while loop, I stored every value of A in new_A in a linear pattern
        // like I used the condition i = (i+1)%N, for first copying the last value to the starting of the new queue,
        // then copying the initial values of the old queue in front of the value of the new queue
    }
    delete(A); //here I delete the old queue
    A = new_A; //here I copied the new queue to the old queue
    N = nextSize();
}
template <typename T> unsigned int DynamicQueue<T>::size(){
    if(head<tail) return (tail-head); //returns the size of queue when the tail is ahead of head
    else return(N-head+tail+1); //returns the size of queue when the head is ahead of tail
}
template <typename T> void DynamicQueue<T>::QInsert(T x){
    if(isFull()) grow(); //when the queue becomes full, the size gets increased
    A[tail]=x; //adding the new value to the queue
    tail = (tail+1)%N; //for the tail becomes in behind of head
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(size()==0) return false; //returns false when queue is false 
    *x = A[head]; //storing the head value of queue in pointer x
    head = (head+1)%N; // for the tail becomes in behind of head
    return true;
}
