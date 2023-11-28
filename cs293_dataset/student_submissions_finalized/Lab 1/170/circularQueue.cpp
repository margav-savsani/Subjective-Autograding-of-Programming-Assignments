#include<iostream>
using namespace std;
#include "queue.h"

template <typename T> bool DynamicQueue<T> :: isEmpty(){
	if( head==tail )return true;
		else return false;
}

template <typename T> bool DynamicQueue<T> :: isFull(){
	if( size()==N-1 ) return true;
		else return false;
}

template <typename T> unsigned int DynamicQueue<T> :: size(){
	return (N+tail-head) % N; // To get positive and less than N we add and divide N
}

template <typename T> void DynamicQueue<T> :: grow(){
	T* B;
	B= new T[nextSize()]; // A new array is created with the required size
	
	// we have to consider two elements 
	if(head<tail){ 
		for (int i=head; i<tail; i++){
			B[i]=A[i]; // copies elements from A to B
		}
	}
	
	if(head>tail){ 
		for (int i=head; i<N; i++){
			B[i]=A[i]; // copies elements from A to B
		}
		
		for (int i=0; i<tail; i++){
			B[i]=A[i]; // copies elements from A to B
		}
		head=head+CONST_GROWTH;
	}
	delete [] A; //Now deletes the elements in A
	A=B; // By this A becomes the required array
	N=nextSize(); // Current size of the array is updated
}

template <typename T> void DynamicQueue<T> :: QInsert(T x){
	if( isFull()==true ) {
		grow(); // As the array is full we need to grow the array
	}
	A[tail]=x; // At this point we can insert the given value into the tail
	tail=(tail+1) % N; // updates the tail and we divide with N as the index after N-1 is 0
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
	if( isEmpty()==true ) return false;
	else	*x=A[head];
	head=(head+1) % N; // updates the tail and we divide with N as the index after N-1 is 0
	return true;
}
