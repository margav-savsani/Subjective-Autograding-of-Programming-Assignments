#include "queue.h"
//assuming that empty arrays are both empty and full at the same time

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    if(size() == 0){  //true if no elements in the queue
        return true;
    }
    else{
        return false;
    }
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    if(size() == N-1 || size() == 0){   //full if N-1 elements are present in the queue
                                  //in a filled circular queue, head=tail, so filing the queue only till N-1
        return true;
    }
    return false;
}

template <typename T>
void DynamicQueue<T>::grow(){
    T* B = new T[nextSize()];     //allocate new heap memory
    int ind = head;
    int sz = size();
    for(int i = 0; i < sz; i++){  //copy all the elements to the new array
        B[i] = A[ind];
        ind = (ind+1) % N;
    }
    delete[] A;  //delete the old array
    A = B;      //assign the new array pointer to A
    head = 0;
    tail = sz;
    N = nextSize();  //increase the value of N accordingly 
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return ((N+tail-head) % N);    //% sign takes into account the case when tail < head.
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()){    //if queue is already full, then grow
        grow();
    }
    A[tail] = x;   //store the element at the tail index in the array
    tail = (tail+1) % N;  //move tail to the next index
        
}

template <typename T>
bool DynamicQueue<T>::QDelete(T* x){
    if(isEmpty()){    //return false if empty
        return false;
    }
    *x = A[head];   //store the front element in *x
    head = (head+1) % N;    //increment head, equivalent to removing the top element

    return true;
}