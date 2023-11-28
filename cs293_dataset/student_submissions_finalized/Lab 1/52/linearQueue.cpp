#include "queue.h"

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return (head==tail);    // Queue is empty if head equals tail
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    return (head==0 && tail==N);    // Queue is full if head is 0 and tail is N
}

template <typename T>
void DynamicQueue<T>::grow(){
    unsigned int sz = (tail-head);   // Store current size
    T* B = A;                        // Store a pointer to current array
    N = nextSize();                  // Get next size
    A = new T[N];                    // point A to a new bigger array

    for(unsigned int i=0; i<sz; i++){  // fill the elements in A using B
        A[i] = B[i];
    }
    delete[] B;                      // delete old array
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return (tail-head);              
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(tail==N){                    // Handle if tail has reached the end
        if(isFull()){               // If array is full then grow
            grow();                 
        }   
        else{                       // else shift all elements back
            unsigned int sz = (tail-head);      // store current size (number of elements)
            for(unsigned int i=0; i<sz; i++){   
                A[i] = A[head+i];               // copy all elements backwards
            }
            head = 0;               
            tail = sz;
        }
    }

    A[tail] = x;
    tail++;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty())
        return false;
    else{
        *x = A[head];
        head++;
        return true;
    }
}