#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include "queue.h"
using namespace std;



template <typename T> bool DynamicQueue<T>::isEmpty(){
    return (head == tail);// returns true if head = tail which signifies an empty queue
}

template <typename T> bool DynamicQueue<T>::isFull(){
    return (size() == N) ;// if the difference between head and tail is the size, then it means
    // the queue is full as the head must be 0 and tail must be N(size). 
}


template <typename T> void DynamicQueue<T>:: grow(){
    T *temp;
    temp = new T[nextSize()];// created a new array of bigger size   
    for(int i =0; i<size(); i++){// for loop to copy data
        temp[i] = A[i];
    }

    delete[] A;
    A = temp;
    N = nextSize();// increase N
    return;
}

template <typename T> unsigned int DynamicQueue<T>:: size(){
    return (tail - head) ;// size is basically the difference between tail and head
}

template <typename T> void DynamicQueue<T>:: QInsert(T x){
    if(isFull()){// if the queue is full, we need to grow it
        grow();       
    }
    else if(tail == N){// if the tail is N, that is the last position is fixed, I reorder the elements so
        for(int i = 0; i < size(); i++){//the queue begins with A[0] giving us space in the end
            A[i] = A[head+i];
        }
        tail = size();
        head = 0;
    }
    A[tail]= x;// finally after all the to be errors are sorted, we store the next element and increment
    tail++;// tail by 1
    return;
}

template <typename T> bool DynamicQueue<T>:: QDelete(T* x){
    if(isEmpty()) return false;// if the queue is empty then this function should return false
    *x = A[head];//stores the deleted element in *x
    head++;// increments the head as now the next element to be deleted is after this one
    return true;// returns true if the deletion was done
}
