#include "queue.h"

template <typename T> void DynamicQueue<T> :: grow() {
	T *B;
	B = new T[nextSize()];

	for(int i=0; i < N; i++){
		B[i] = A[(head + i) % N];
	}
	delete(A);
	A = B; head = 0; tail = N;
	N = nextSize();
	//here we are creating a new class B and coping every element of A to B, deleting the pointer A and equating A to B.
	//reseting the size N to nextsize(), heat to 0 and tail to N. 
}

template <typename T> bool DynamicQueue<T> :: isEmpty() {
	if(tail - head == 0)
		return true;
	//here head and tail are not array indices.
	//tail - head will give the size of the queue. (tail is always greater than head)
	//if tail-head = 0 it will return true else false 
	else
		return false;
}

template <typename T> bool DynamicQueue<T> :: isFull() {
	if(tail - head == N)
		return true;
	else
		return false;
	//if size() == N, will return true else returns false.
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
	return (tail - head);
	//since size() = tail - head it will return the same.
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x) {
	if(size() == 0)
		return false;
		//since we can't delete from empty set.
	else{
		head += 1;
		return true;
		// by changing the starting queue to second element we are deleting the first element.
	}
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
	if(size() < N){
		A[tail % N] = x;
		tail += 1;
	}
	else{
		grow();
		A[tail % N] = x;
		tail += 1;
	}
}
