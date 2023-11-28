#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){

    // if head and tail are both equal then queue is empty

    if(head==tail) return true;
    else return false;    
}

template <typename T> bool DynamicQueue<T>::isFull(){

    // if tail points to the end of array then queue is full

    if(size()==N) return true;
    else return false;    
}

template <typename T> void DynamicQueue<T>::grow(){

    // creating a new array with added size
    T* newPtr = new T[nextSize()];

    // copying all the elements of previous array into new array;
    for(int i=head; i<tail; ++i){
        newPtr[i-head] = A[i];
    }

    // freeing up the space occupied by previous array
    delete[] A;

    // making A point to the new array
    A = newPtr;

    // setting N equal to the new size of the array
    N = nextSize();

    // setting appropriate values of head and tail
    unsigned int temp = tail-head;
    head = 0;
    tail = temp;
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    return tail-head;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    if(tail != N){
        // if we haven't reached end of array then just insert the new element
        A[tail] = x;
        tail++;
        return;
    }

    if(tail == N){
        // when we have reached the end of array
        if(size()<N){

            //
            for(int i=head; i<tail; ++i){
                A[i-head] = A[i];

                unsigned int temp = tail-head;
                head = 0;
                tail = temp;
            }
        }
        else{
            // if number of empty spaces in current array are less than what we will be increasing
            // then grow the array and then insert in the new array
            grow();
            A[tail] = x;
            tail++;
        }
    }
}

template <typename T> bool DynamicQueue<T>::QDelete(T* x){
    if(isEmpty()) return false;
    else{
        *x = A[head];
        head++;
        return true;
    }
}

