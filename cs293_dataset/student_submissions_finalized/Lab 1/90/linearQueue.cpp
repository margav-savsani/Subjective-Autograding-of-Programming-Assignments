#include <iostream>
#include "queue.h"

using namespace std;


template <typename T> unsigned int DynamicQueue<T>::size(){
	return (tail-head);
	// Number of elements in Queue.
}

template <typename T> bool DynamicQueue<T>::isEmpty(){
	return (size() == 0);
	// Empty Queue
}

template <typename T> bool DynamicQueue<T>::isFull(){
	return (size() == N);
	// Full Queue
}

template <typename T> void DynamicQueue<T>::grow(){

	unsigned int Nnew = nextSize();
	// Create a new array with size = nextSize()
	T* Anew = new T[Nnew];
	// Copy the elements present in the old array to the new array
	for(unsigned int i=0; i<N; i++){
		Anew[i] = A[i];
	}
	// Delete the old array
	delete [] A;
	// Update A,N
	A = Anew;
	N = Nnew;

}

template <typename T> void DynamicQueue<T>::QInsert(T x){

	// Grow the array if it is full
	if(isFull()){
		grow();
	}
	// If queue is not full, but last block is filled up
	else if(tail==N){
		//Shift the stack to the start.
		unsigned int start = head;
		for(unsigned int i=0; i<size(); i++){
			A[i] = A[start];
			start++;	
		}
		//Update tail and head values.
		tail = size();
		head = 0;		
	}
	//Insert new element and increment value of tail
	A[tail++] = x;

}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	
	//If Queue is not empty
	if(!isEmpty()){
		// Assign the value of deleted element to the value that x points to.
		*x = A[head];
		//Increment head value.
		head++;
		//Sucessfully deleted an element, hence return true.
		return true;
	}
	//Empty Queue has no elements to delete, hence return false.
	return false;

}

