#include <iostream>
#include "queue.h"

// is the queue empty?
template <typename T> bool DynamicQueue<T>::isEmpty() {
	return head == tail; // if the head and tail are at the same position, then the queue is empty
}

// is the queue full?
template <typename T> bool DynamicQueue<T>::isFull() {
	return size() == N; // if the size of the queue is N, then the queue is full
}

// grow the queue to its next size
template <typename T> void DynamicQueue<T>::grow() {
	unsigned int N_new = nextSize(); // N_new is the next queue size
	T *A_new = new T[N_new]; // A_new is the new array
	for(int i = 0; i < N; i++){ // allocate elements from A to A_new
		A_new[i] = A[i];
	}
	head = 0; // new head is 0
	tail = N; // new tail is N
	A = A_new; // reassign A to A_new
	N = N_new; // reassign N to N_new
}

// return the current number of elements in the queue
template <typename T> unsigned int DynamicQueue<T>::size() {
	return tail - head; // the difference of the tail and head is the size of the queue
}

// insert given element at tail of the queue; grow array size as necessary
template <typename T> void DynamicQueue<T>::QInsert(T x) {
	if(isFull()){ // if the queue is full, grow the queue
		grow();
	} else if(tail == N){ // if the tail is at position N, realloacte the elements of the queue
		unsigned int len = size();
		for(int i = 0; i < len; i++){
			A[i] = A[head+i];
		}
		head = 0;
		tail = len;
	}

	// insert element at tail and increment tail
	A[tail] = x;
	tail++;
}

// delete element at head of the queue and place it in *x; returns false if queue is empty, true otherwise
template <typename T> bool DynamicQueue<T>::QDelete(T *x) {
	if(isEmpty()){ // if queue is empty, return false
		return false;
	}
	
	// place element at head in *x, increment head and return true
	*x = A[head];
	head++;
	return true;
}
