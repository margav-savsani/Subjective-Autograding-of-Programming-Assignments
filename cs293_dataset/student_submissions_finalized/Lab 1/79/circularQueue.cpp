#include <iostream>
#include "queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty(){
    if(head == tail) return true; // if head and tail have same index, queue is empty
    else return false;
}

template <typename T> bool DynamicQueue<T> :: isFull(){
    if(tail - head == N) return true; // like a linear queue
    else if ((tail < head)&&( head - tail == 1)) return true; // special case for circular queue when tail is behind head
    else return false;
}

template <typename T> void DynamicQueue<T> :: grow(){
    int previous_N = N; // storing the original value of N in previous_N variable
    N = nextSize(); 
    T *B = new T[N];
    for(int i = 0; i < previous_N; i++) B[i] = A[i]; // copying elements to the new array

    delete[] A;
    A = B;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
    return tail - head;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x){
    if(size() == N - 1) grow(); // grow when one space is left so that we don't have the case where head == tail
    if(!isFull()){
        A[tail%N] = x;
        tail = tail%N;
    }
    else{
        grow();
        A[tail] = x;
    }
    tail++;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
    if(isEmpty()) return false;
    else{
        int x_size = *(&x + 1) - x; // size of array x
        T *y = new T[N];
        for(int i = 0; i < x_size; i++){
            y[i] = x[i];
        }
        y[x_size] = A[head];
        x = y;
        return true;
    }
}