#include "queue.h"

template <typename T> bool DynamicQueue<T> :: isEmpty(){
    //check if head and tail have the same value
    if (head == tail){
        return true;
    } else {
        return false;
    }
}


template <typename T> bool DynamicQueue<T> :: isFull(){
    // check if difference between tail and head is the same as array size
    if (size() == N){
        return true;
    } else {
        return false;
    }
}

template <typename T> void DynamicQueue<T> :: grow(){
    // create a new array of size N + CONST_GROWTH
    // copy elements to a new array and delete the old array
    int newSize = nextSize();
    T* B = new T[newSize];
    for (int i = 0; i < newSize; i++){
        B[i] = 0;
    }


    for (int i = 0 ; i < N; i++){
        B[i] = A[i];

    }

    
    delete[] A;

    A = B;
    N = newSize;
    
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
    // return the difference between head and tail
    return tail - head;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {

    // if the queue is full, grow the queue
    if (this->isFull()){
        this -> grow();
        
    }

    //insert the new element at the tails position
    //advance the tail by 1
    A[tail] = x;
    tail++;

    if(tail == N) {
        for(int i = head; i < tail; i++){
            A[i - head] = A[i];
        }
        tail = tail - head;
        head = 0;
    }
}

template <typename T> bool DynamicQueue<T> :: QDelete (T *x) {
    
    if (this -> isEmpty()){
        return false;

    } else {
        // if queue is nonempty, move the head to the succeeding position
        // store the delted value in the space corresponding to x
        *x = A[head];
        head++;
        return true;
    }
}