#include <iostream>
#include "queue.h"

// I have discussed with Pritesh and Kartik regarding the specification minutiae whose solution was suggested as storing an invalid index in tail once the queue is full. I use -1 as the invalid index.:

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
		A_new[i] = A[(head+i)%N];
	}
	head = 0; // new head is 0
	tail = N; // new tail is N
	A = A_new; // reassign A to A_new
	N = N_new; // reassign N to N_new
}

// return the current number of elements in the queue
template <typename T> unsigned int DynamicQueue<T>::size() {
	if(tail == -1){ // tail being -1 indicates that the queue is full
		return N;
	} else if(tail >= head){ // if tail is after head, then their difference is the size of the queue
		return tail - head;
	} else{ // if tail is before head, the the queue wraps around
		return (N - head) + tail;
	}
}

// insert given element at tail of the queue; grow array size as necessary
template <typename T> void DynamicQueue<T>::QInsert(T x) {
	if(isFull()){ // if the queue is full, grow the queue
		grow();
	}

	// insert element at tail and increment tail (wrapping around if necessary)
	A[tail] = x;
	tail++;
	if(tail == N) tail = 0;
	if(tail == head){ // if the queue is full, represent that by setting tail to -1
		tail = -1;
	}
}

// delete element at the head of the queue and place it in *x; return false if queue is empty, true otherwise
template <typename T> bool DynamicQueue<T>::QDelete(T *x) {
	if(isEmpty()){ // if queue is empty, return false
		return false;
	}
	
	// place element at head in *x, increment head (wrapping around if necessary) and return true
	*x = A[head];
	if(tail == -1){ // if the queue was full, the tail can now be a valid index
		tail = head;
	}
	head++;
	if(head == N) head = 0;
	return true;
}
