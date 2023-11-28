#include <iostream>
#include "queue.h"

using namespace std;



template<typename T>
bool DynamicQueue<T>::isEmpty() { 	//if head is equal to tail, as is the case when the queue is initialised,
	if(head == tail) return true;   //we take the queue to be empty
	else return false;
}

template<typename T>
bool DynamicQueue<T>::isFull() { 	//for a linear queue, when the tail reaches N, the queue is full
	if(tail==N) return true;
	else return false;
}

template<typename T>
void DynamicQueue<T>::grow() { 		//we create a new array of type T with a larger size, placing all the
	T* B=new T[nextSize()];		//elements of A in B, starting from index 0 of B, to optimise for space
	N=nextSize();
	for(int theta=0; theta<tail-head; theta++) {
		B[theta]=A[head+theta];
	}
	A=B;
	int temp=tail-head;
	head=0;
	tail=temp;
}

template<typename T>
unsigned int DynamicQueue<T>::size() {		//returns the size by computing tail-head
	return tail-head;
}

template<typename T>
void DynamicQueue<T>::QInsert(T x) {		//if the queue is not full, it works normally, otherwise it grows
	if (!(isFull())) {			//the array first before appending the element to the queue
		A[tail]=x;
		tail+=1;
	}
	else {
		grow();
		A[tail]=x;
		tail+=1;
	}
}

template<typename T>
bool DynamicQueue<T>::QDelete(T *x) {		//if the queue is not empty, it places the head element in the
	if(isEmpty()) return false;		//address of the pointer provided and increments head by 1
	else {
		*x=A[head];
		head+=1;
		return true;
	}
}

