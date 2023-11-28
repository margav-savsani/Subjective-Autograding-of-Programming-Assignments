#include <iostream>
#include "queue.h"
using namespace std;


template <typename T> bool DynamicQueue<T>::isEmpty(){
    if(head > tail)
        return true; // if head is greater than tail then the queue is empty
    else if (head == tail == 0){
        return true; // no elements in the queue
    }else 
        return false;
}

template <typename T> bool DynamicQueue<T>::isFull(){
    if (tail == N-1){
        if (head == 0){
            return true; // the array is filled from 0th index to the N-1 index
        } else {
            for (int i = head; i < N, i++;)
            {
                A[i - head] = A[i];
            }
            tail = N - head - 1;
            head = 0;
            return false; // the array is empty at the beginning of the queue
        }
    } else return false; 
}

template <typename T> void DynamicQueue<T>::grow(){
    if (isFull()){
        N = nextSize();
    }
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    if (isEmpty()){
        return 0;
    }else
        return tail - head + 1;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    if (isFull()){
        grow(); tail++;
        A[tail] = x;
        N++; 
    } else {
        if (tail == 0){
            A[tail] = x;
            N++;
        }else {
            tail++;
            A[tail] = x;
            N++; 
        }
        
    }
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if (isEmpty()){
        return false;
    } else {
        *x = A[head]; //places the first element of the queue in *T
        head++;
        return true;
    }
}