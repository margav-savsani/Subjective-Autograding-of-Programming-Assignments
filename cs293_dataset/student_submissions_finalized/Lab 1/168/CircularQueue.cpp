#include <iostream>
#include "queue.h"
using namespace std;

//Circular Queue implementation

template <typename T> bool DynamicQueue<T>::isEmpty(){
	//gives true if the queue is empty
	//which happens when head and tail are equal
	return (head==tail);
}

template <typename T> bool DynamicQueue<T>::isFull(){
	//gives true if the queue is full
	//which happens when the number of elements in the array
	//is N-1 (as 1 spot is left empty so head won't be equal
	//to tail with a non-empty queue)
	return (N-1==size());
}

template <typename T> unsigned int DynamicQueue<T>::size(){
	//gives the number of elements in the queue.
	if (head<=tail){
		return (tail-head);	//without any wrap-around
	}
	else{
		return (tail+N-head);	//if a wrap-arround has happened
	}
}


template <typename T> void DynamicQueue<T>::grow(){
	//extends the size of the queue by CONST_GROWTH.
	T* B=new T[nextSize()];
	for (int i=0;i<N;i++){	//copies the elements of A into a new array B
		B[i]=A[(head+i)%N];	//this makes sure that if head!=0, the elements get shifted so head becomes 0
	}
	delete[] A;
	A=B;		//sets A=B again	
	N=nextSize();	//updates the value of N
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
	//adds an element to the queue
	if(isFull()){
		tail=N-1;	//updates tail to the value it will take
		grow();		//grows the array to accomodate the new element.
		head=0;		//updates head
	}	
	else if(tail==N){
		tail=0;		//sets tail to 0 to perform the wrap-around.
	}	

	//Actually adding the new element to the tail of the queue.
	A[tail]=x;
	tail++;		//shifting tail by one
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	if (isEmpty()){
		return false;	//can't dequeue from an empty queue
	}
	else{
		head++;		//shifts queue because one element was removed.
		*x=A[head-1];
		head=head%N;	//if head takes value N, it will shift to 0 (in case we delete the element at index N-1
		return true;
	}
}

