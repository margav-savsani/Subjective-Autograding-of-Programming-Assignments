#include<iostream>
#include"queue.h"

template<typename T>bool DynamicQueue<T> :: isEmpty(){
    if(head==tail) return true;
    else return false;

}
template<typename T>bool DynamicQueue<T>:: isFull(){
    if(tail-head==N) return true;//tail and head keeps on increasing ,when we want to access last elements qwe use modulo function.
    else return false;
}
template<typename T>void DynamicQueue<T> :: grow(){
    T*B;
    B=new T[nextSize()];//new circular queue of nextsize
    for(int i=0;i<N;i++){
        B[i]=A[i];//copying elements
    }
    head=0;
    tail=N;
    N=nextSize();
    T*K;
    K=A;
    A=B;
    delete K;//deleting space of A
    
    
}
template<typename T>unsigned DynamicQueue<T> ::size(){
    return tail-head;
}
template<typename T>void DynamicQueue<T> ::QInsert(T x){
    if(isFull()){
        grow();
        A[tail]=x;
        tail++;
    }
    else{
        A[(tail%N)]==x; //modulus function of tail gives the last element
        tail++;
    }
}
template<typename T>bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return false;
    else{
        *x=A[head%N]; // storing the last element
        head++;
        return true;
    }
    
    
}
