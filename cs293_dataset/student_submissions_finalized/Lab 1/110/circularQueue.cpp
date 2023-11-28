#include<iostream>
#include"queue.h"

template<typename T> bool DynamicQueue<T> :: isEmpty(){
    return (tail-head==0);
} 

template<typename T> bool DynamicQueue<T> :: isFull(){
    return (tail-head==N);  
}

template<typename T> void DynamicQueue<T> :: grow(){
		T *B;
        B = new T[nextSize()];
		for (int i=0;i<N;i++) B[i]=A[i];    //increased the size of array
        delete(A);
        A=B;
        N = nextSize();
        B = NULL;
}

template<typename T> unsigned int DynamicQueue<T> :: size(){
	return tail-head;
}

template<typename T> void DynamicQueue<T> :: QInsert(T x){
    tail++;
    if(isFull()) grow();
    A[(tail-1)%N]=x;
}

template<typename T> bool DynamicQueue<T> :: QDelete(T *x){
    if(isEmpty()) return false;
    *x = A[head%N];
    T *t=&(A[head%N]);
    t=NULL;
	head++;
    return true;
}
