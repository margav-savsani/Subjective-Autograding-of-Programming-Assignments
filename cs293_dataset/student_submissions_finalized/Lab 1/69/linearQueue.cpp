// Code developed by Erata Maharshi
#include <iostream>
#include "queue.h"
#define CONST_GROWTH 1000
#define INIT_SIZE 1000
using namespace std;

// If head equals tail, queue is empty
template <typename T> bool DynamicQueue <T> :: isEmpty(){
    return (head==tail);
}

// If the value of tail equals N then the queue is empty
template <typename T> bool DynamicQueue <T> :: isFull(){
    return (tail==N);
}

// Initializing a new array and copying the elements into
// correspondingindices of new array and reassigningthe pointer to A
template <typename T> void DynamicQueue <T> :: grow(){
    T* B = new T[nextSize()];
	for(int i=0; i<N; i++){
		B[i]=A[i];
	}
	A=B;
	B=NULL;
	N=nextSize();
}

// Simple difference of head and tail values gives the size of the queue
template <typename T> unsigned int DynamicQueue <T> :: size(){
    return tail-head;
}

// If the queue is full,it will be grown, and then a new element will be added at last position
template <typename T> void DynamicQueue <T> :: QInsert(T x){
    if(isFull()){
        grow();
    }
    A[tail]=x;
    tail++;
}

// If empty will return false, otherwise head value
// increase by one and deleted element is stored in *x
template <typename T> bool DynamicQueue <T> :: QDelete(T *x){
    if(isEmpty()){
        return false;
    }
    *x=A[head];
    head++;
    return true;
}
