#include "queue.h"

template <typename T> void DynamicQueue<T> :: grow() {
	T *B;
	B = new T[nextSize()];
		
	for( int i=0; i < N; i++){
		B[i] = A[i];
	}
	//here we create a class B and copy all first N elements, delete the pointer A and pointing A to B.
	delete(A);
	A = B; N = nextSize();
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
	return (tail - head);
	//here tail and head are array indices
}

template <typename T> bool DynamicQueue<T> :: isEmpty() {
	if((tail-head) == 0)
		return true;
	else 
		return false;
}

template <typename T> bool DynamicQueue<T> :: isFull() {
	if(tail-head == N)
		return true;
	//this is the only possible outcome when it is full.
	else
		return false;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x){
	if (tail != N){
		A[tail] = x;
		tail += 1;
	}
	else if ((head != 0)){
		int temp = tail - head;
		for(int i = 0; i < temp ; i++){
			A[i] = A[head + i];
		}
		head = 0; tail = temp;
		A[tail] = x;
		tail += 1;
	}
	else{
		grow();
		A[tail] = x;
		tail += 1;
	}	
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
	if(tail - head == 0)
		return false;
	else{
		head += 1;
		return true;
	}
}
		
