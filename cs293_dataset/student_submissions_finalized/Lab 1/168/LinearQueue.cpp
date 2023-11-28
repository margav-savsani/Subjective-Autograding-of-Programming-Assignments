#include <iostream>
#include "queue.h"
using namespace std;

//Linear Queue implementation

template <typename T> bool DynamicQueue<T>::isEmpty(){
	//gives true if the queue is empty
	//which happens if head and tail are equal
	return (head==tail);
}

template <typename T> bool DynamicQueue<T>::isFull(){
	//gives true if the queue is full
	//which happens if the size of the queue is equal to the number of elements in it.
	return (N==size());
}

template <typename T> unsigned int DynamicQueue<T>::size(){
	//gives the number of elements in the queue.
	return (tail-head);
}

template <typename T> void DynamicQueue<T>::grow(){
	//extends the size of the queue by CONST_GROWTH.
	T* B=new T[nextSize()];
	for (int i=0;i<N;i++){		//copies elements of A into B
		B[i]=A[i];
	}
	delete[] A;
	A=B;		//sets A=B
	N=nextSize();	//updates the value of N after growing
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
	//adds an element to the queue
	if (tail==N){		//if the end of the queue has been reached
		if(isFull()){
			//queue is full, must be extended
			grow();
		}
		else{
			//queue isn't full, so we need to shift elements back to the front of the queue.
			for (int i=0;i<tail-head;i++){
				A[i]=A[head+i];
			}
			//resetting the values of head and tail
			tail=tail-head;
			head=0;	
		}
	}
	A[tail]=x;	//actually adding the new element to the tail of the queue.
	tail++;		//updating the value of tail
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	if (isEmpty()){
		return false;	//can't delete from an empty queue.
	}
	else{
		head++;		//increases head because we deleted an element
		*x=A[head-1];
		return true;
	}
}
