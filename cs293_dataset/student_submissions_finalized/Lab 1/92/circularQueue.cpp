#include<iostream>
#include<cmath>
#include "queue.h"
using namespace std;

template <typename T> unsigned int DynamicQueue<T>::size(){
    return ((N-head+tail)%N);
    }
template <typename T> bool  DynamicQueue<T>::isEmpty(){
    return size()==0;
}
template <typename T> bool DynamicQueue<T>::isFull(){
    return size()==N-1;
}
template <typename T> void DynamicQueue<T>::grow(){
    T *S;
    S=new T[nextSize()];
    int j=head;
    for(int i=0;i<N-1;i++){
        S[i]=A[j];
        j=(j+1)%N;
    }
    A=S;
    head=0;tail=N-2;
    N=nextSize();
    }
template <typename T> void DynamicQueue<T>::QInsert(T x){
    if(isFull()) {
        grow();
        A[tail]=x;
        tail=(tail+1)%N;
    }
    else {
        A[tail]=x;
        tail=(tail+1)%N;
    }
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()){return 0;}
    else {
        *x=A[head];
        head=(head+1)%N;
        return 1;
    }
}