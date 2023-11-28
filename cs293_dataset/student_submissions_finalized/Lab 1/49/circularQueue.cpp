#include "queue.h"

// to check whether array is empty or not
template <typename T> bool DynamicQueue<T> :: isEmpty(){
    if(tail==head) return true;
    else return false;
}
// to check whether array is full or not
template <typename T> bool DynamicQueue<T> :: isFull(){
    if((tail-head)==N) return true;
    else return false;
}
// to increase the size of array
template <typename T> void DynamicQueue<T> :: grow(){
    T *B;
    B = A;// copies address stored in A       
    A = new T[nextSize()];// now creates new array of size nextSize() to store data
    for(int i=0;i<N;i++){// copies data which was already present
        A[i]=B[i];
    }
    N = nextSize();
}
// to know number of elements in queue
template <typename T> unsigned int DynamicQueue<T> :: size(){
    // here tail and head are counted generally as in a linearQueue 
    // that is after inserting N elements tail is N and if further 
    // insertion is done without growing size then tail is N+1
    // index of tail in array is tail%N 
    // index of head in array is head%N
    return tail-head; 
}
// to insert element 
template <typename T> void DynamicQueue<T> :: QInsert(T x){
    if(isFull()) grow();       
    A[tail%N] = x;
    tail++;
}
// to delete element
template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
    if(isEmpty()) return false;
    *x = A[head%N];     
    head++;
    return true;     
}