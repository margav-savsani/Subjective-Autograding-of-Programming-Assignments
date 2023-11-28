#include "queue.h"

template <typename T> bool DynamicQueue<T> :: isEmpty(){
    //check if the head and tail are same
    if (head == tail){
        return true;
    } else {
        return false;
    }
}


template <typename T> bool DynamicQueue<T> :: isFull(){
    // if the size is one less than the size of array, return true
    if (size() == N - 1){
        return true;
    } else {
        return false;
    }
}

template <typename T> void DynamicQueue<T> :: grow(){
    // find the new size and create the new array
    int newSize = nextSize();
    T* B = new T[newSize];

    // if queue doesnt wrap around, simply copy the elements in the new array
    if (this->tail > this->head){
        
        for (int i = 0; i < newSize; i++){
                B[i] = 0;
        }


        for (int i = 0 ; i < N; i++){
            B[i] = A[i];

        }

    
    

    // if the queue wraps around, create extra space between tail and head by amount CONST_GROWTH  
    } else {
        for(int i = 0; i < tail; i++){
            B[i] = A[i];
        }
        
        for(int i = head; i < N; i++){
            B[i + CONST_GROWTH] = A[i];
        }

        head = head + CONST_GROWTH;
        
    }

    delete[] A;
    A = B;
    N = newSize;
    
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
    // check the number of elements occupied in the array by using modulo irrespective
    // of the fact that array is wrapped or not
    return (tail - head + N) % N;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
    if (this->isFull()){
        this -> grow();
        
    }

    A[tail] = x;
    tail = (tail + 1) % N; // advance to the next position, if end is reached then wrap around
}

template <typename T> bool DynamicQueue<T> :: QDelete (T *x) {
    if (this -> isEmpty()){
        return false;

    } else {
        // if queue is nonempty, move the head to the succeeding position, if head is at the end then wrap around
        // store the delted value in the space corresponding to x
        x = A + head;

        head = (head + 1) % N;
        return true;
    }
}