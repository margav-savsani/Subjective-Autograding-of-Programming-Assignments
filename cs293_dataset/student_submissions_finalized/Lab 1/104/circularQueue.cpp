#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){

    // if head and tail are both equal then queue is empty

    if(head==tail) return true;
    else return false;
}

template <typename T> bool DynamicQueue<T>::isFull(){

    // we are always keeping atleast 1 index free

    if(size()==N-1) return true;
    else return false;
}

template <typename T> void DynamicQueue<T>::grow(){

    // creating a new array with added size
    T* newPtr = new T[nextSize()];

    // copying all the elements of previous array into new array;
    for(int i=0; i<size(); ++i){
        newPtr[i] = A[(i+head)%N];
    }

    // freeing up the space occupied by previous array
    delete[] A;

    // making A point to the new array
    A = newPtr;

    // setting appropriate values of head and tail
    unsigned int temp = size();
    head = 0;
    tail = temp;

    // setting N equal to the new size of the array
    N = nextSize();
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    return (N-tail+head)%N;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){

    // if array isn't full then just add the new element
    if(size() < N-1){
        A[tail] = x;
        tail = (tail+1)%N;
        return;
    }

    // if array is full then grow the array and then insert
    else if(size() == N-1){
        grow();
        A[tail] = x;
        tail = (tail+1)%N;
        return;
    }
}

template <typename T> bool DynamicQueue<T>::QDelete(T* x){
    if(isEmpty()) return false;
    else{
        *x = A[head];
        head = (head+1)%N;
        return true;
    }
}