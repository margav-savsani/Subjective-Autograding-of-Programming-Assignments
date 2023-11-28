#include "queue.h"

template <typename T> bool DynamicQueue<T> :: isEmpty() {
    return head == tail;
}

template <typename T> bool DynamicQueue<T> :: isFull() {
    return tail-head == N;
}

template <typename T> void DynamicQueue<T> :: grow() {
    if(!isFull()){
        return ;                // check if really full
    }

    int oldN = N;
    N = nextSize();
    T *B = new T[N];            // creating a new pointer in heap with more capacity

    for(int i=0; i<oldN; i++){
        B[i] = A[i];
    }

    delete A;                   // then replace the pointer
    A = B;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
    return tail-head;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
    if(isFull()){
        grow();
    }
    if (tail==N && head!=0){
        for(int i=0; i<N-head; i++){
            A[i] = A[i+head];
        }
        tail -= head; head = 0;
    }
                                // in-case tail reaches the end, shift everything to the start
    A[tail] = x;
    tail++;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x) {
    if(isEmpty()){
        return false;
    }
    *x = A[head];               // assign the value at head to the location pointed to by pointer x

    head++;
    return true;
}