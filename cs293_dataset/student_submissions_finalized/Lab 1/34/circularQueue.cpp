#include "queue.h"

template <typename T>bool DynamicQueue<T> :: isEmpty(){
    return (head == tail);
}
template <typename T>bool DynamicQueue<T> :: isFull(){
    //max size of array is taken to be N-1.
    return (size() == N-1);
}
template <typename T>void DynamicQueue<T> :: grow(){
    //new array created with larger size
    T* B = new T[nextSize()];
    //copying elements to new arrray
    for(int i = 0; i < size(); i++){
        B[i] = A[(i+head)%N];
    }
    //deleting old array to make space.
    delete[] A;
    A = B;
    tail = size();
    head = 0;
    N = nextSize();
}
template <typename T>unsigned int DynamicQueue<T> :: size(){
    //the mod is used for the case when tail < head.
    return (N - head + tail)%N;
}
template <typename T>void DynamicQueue<T> :: QInsert(T x){
    //when size is less than the max size that is N-1 here we simply add the element.
    if(size() < N-1){
        A[tail] = x;
        tail = (tail+1)%N;
    }
    //else we grow the array and then add the element
    else{
        grow();
        A[tail] = x;
        tail = (tail+1);
    }
}
template <typename T>bool DynamicQueue<T> :: QDelete(T* x){
    if(!this->isEmpty()){
        //storing value in x. and then just moving head to next index.
        *x = A[head];
        head = (head+1)%N;
        return true;
    }
    else{
        return false;
    }
}