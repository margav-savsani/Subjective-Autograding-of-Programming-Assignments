#include "queue.h"

template <typename T> bool DynamicQueue<T> :: isEmpty() {
    return head == tail;
}

template <typename T> bool DynamicQueue<T> :: isFull() {
    return (tail-head == N);
}

template <typename T> void DynamicQueue<T> :: grow() {
    if(!isFull()){
        return ;
    }

    int oldN = N;
    N = nextSize();
    T *B = new T[N];

    for(int i=0; i<oldN; i++){
        B[i] = A[(i+head)%oldN];    // rearranging elements of A into B
    }
    delete A;
    A = B;

    tail -= head;
    head=0; 
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
    return tail-head;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
    if(isFull()){
        grow();
    }

    A[tail%(N)] = x;    // basically, we won't restrict the value of tail, and instead take modulo when used as index
    tail++;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x) {
    if(isEmpty()){
        return false;
    }
    *x = A[head%N];     // assign the value at head to the location pointed to by pointer x
    head++;
    
    return true;
}