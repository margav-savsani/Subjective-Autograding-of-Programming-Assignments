#include "queue.h"
template <typename T>bool DynamicQueue<T> :: isEmpty(){
    if(head == tail) return true;
    else return false;
}
template <typename T>bool DynamicQueue<T> :: isFull(){
    if(tail - head == N)return true;
    else return false;
}
template <typename T>void DynamicQueue<T> :: grow(){
    //new array created with size N + CONST_GROWTH
    T* B = new T[nextSize()];
    //copying old array to new array
    for(int i = 0; i < size(); i++){
        B[i] = A[i+head];
    }
    //deleting old array to free up space
    delete[] A;
    A = B;
    N = nextSize();
}
template <typename T>unsigned int DynamicQueue<T> :: size(){
    return tail - head;
}
template <typename T>void DynamicQueue<T> :: QInsert(T x){
    //when queue is not full
    if(this->size() < N){
        //when tail has reached end
        if(tail == N){
            for(int i = 0; i < this->size(); i++){
                A[i] == A[i+head];
            }
            tail = tail - head;
            head = 0;
            A[tail] = x;
            tail++;
        }
        //tail has not reached end
        else{
            A[tail] = x;
            tail++;
        }
    }
    //when array gets full.
    else{
        grow();
        A[tail] = x;
        tail++;
    }
}
template <typename T>bool DynamicQueue<T> :: QDelete(T* x){
    if(!this->isEmpty()){
        //storing value in x. and then just moving head to next index.
        *x = A[head];
        head++;
        return true;
    }
    else{
        return false;
    }
}