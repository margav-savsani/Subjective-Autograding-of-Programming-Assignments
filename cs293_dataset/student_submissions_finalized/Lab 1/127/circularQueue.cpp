#include <iostream>
#include "queue.h"

using namespace std;


//if head is equal to tail, as is the case when the queue is initialised,
//we take the queue to be empty

template<typename T>
bool DynamicQueue<T>::isEmpty() { 	
	if(head == tail) return true;	
	else return false;
}


//for a circular queue, when the tail reaches head from behind, in a sense,
//the queue is full

template<typename T>
bool DynamicQueue<T>::isFull() {	
	if((head-tail+N)%N==1) return true;
	else return false;
}


//we create a new array of type T with a larger size, placing all the
//elements of A in B, starting from index 0 of B, to optimise for space

template<typename T>
void DynamicQueue<T>::grow() {
	T* B=new T[nextSize()];
	N=nextSize();
	for(int theta=0; theta<size(); theta++) {
		B[theta]=A[(head+theta)%N];
	}
	int temp=size();
	A=B;
	head=0;
	tail=temp;
}


//returns the size by computing tail-head modulo N

template<typename T>
unsigned int DynamicQueue<T>::size() {
	return (tail-head+N)%N;
}


//if the queue is not full, it works normally, otherwise it grows
//the array first before appending the element to the queue

template<typename T>
void DynamicQueue<T>::QInsert(T x) {
	if (!(isFull())) {
		A[tail]=x;
		tail=(tail+1)%N;
	}
	else {
		grow();
		A[tail]=x;
		tail=(tail+1)%N;
	}
}


//if the queue is not empty, it places the head element in the
//address of the pointer provided and increments head by 1

template<typename T>
bool DynamicQueue<T>::QDelete(T *x) {
	if(isEmpty()) return false;
	else {
		*x=A[head];
		head=(head+1)%N;
		return true;
	}
}

