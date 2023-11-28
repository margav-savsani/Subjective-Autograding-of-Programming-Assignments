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

// This relation satisfies the given requirements to find wheather
// a circular queue is full or not
template <typename T> bool DynamicQueue <T> :: isFull(){
	return ((head-1)%N==tail%N);
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

// If tail is more than head simple difference
// If tail is less than head we have to add array size
template <typename T> unsigned int DynamicQueue <T> :: size(){
	if(tail>head)
		return tail-head;
	else
		return N+tail-head;
}

// If the queue is full,it will be grown, and then a new element will be added at last position
template <typename T> void  DynamicQueue <T> :: QInsert(T x){
	if(isFull()){
		grow();
	}
	A[tail]=x;
	tail++;
}

// If empty will return false, otherwise head value
// increase by one and deleted element is stored in *x
template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
	if(head==tail){
		return false;
	}
	*x=A[head];
	head++;
	return true;
}
