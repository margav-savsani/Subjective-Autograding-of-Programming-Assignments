#include <iostream>
using namespace std;
#include "queue.h"

template <typename T> bool DynamicQueue<T> :: isEmpty(){
	if( head==tail )return true;
		else return false;
}

template <typename T> bool DynamicQueue<T> :: isFull(){
	if( tail-head==N ) return true;
		else return false;
}

template <typename T> unsigned int DynamicQueue<T> :: size(){
	return tail-head; // As tail is the index where the next element will be inserted
}

template <typename T> void DynamicQueue<T> :: grow(){
	T* B;
	B= new T[nextSize()]; // A new array is created with the required size
	for (int i=0; i<N; i++){
		B[i]=A[i]; // copies elements from A to B
	}
	delete [] A; //Now deletes the elements in A
	A=B; // By this A becomes the required array
	N=nextSize(); // Current size of the array is updated
}

template <typename T> void DynamicQueue<T> :: QInsert(T x){
	if( isFull()==true ) {
		grow(); // As the array is full we need to grow the array
	}
	else if( tail==N ){ // As the array is not full we shift the elements to the start of the array
		for(unsigned int i=0; i<size(); i++){
			A[i]=A[head+i];
		}
		tail=size(); // updates the tail after shifting
		head=0; // updates the head after shifting
	} 
	A[tail]=x; // At this point we can insert the given value into the tail 
	tail++; // updates the tail after inserting the elements
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
	if( isEmpty()==true ) return false;
	else	
	*x=A[head];
	head++;
	return true;
}
