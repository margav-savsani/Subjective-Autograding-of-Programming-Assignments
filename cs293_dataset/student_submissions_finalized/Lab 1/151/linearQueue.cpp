#include <iostream>
#include "queue.h"

using namespace std;

// returns whether the queue is empty or not
template <typename T> bool DynamicQueue<T>::isEmpty()
{
	return !size();
}

// returns whether the queue is full or not
template <typename T> bool DynamicQueue<T>::isFull()
{
	return (N == size());
}

// if the queue is full ONLY, it will increase the size of the queue by a constant
template <typename T> void DynamicQueue<T>::grow()
{
	if(isFull()){							// checks whether array is full
		T* B = new T[nextSize()];

		for(int i = 0; i < N; i++){
			B[i] = A[i];					// copies each element of queue A into the bigger queue B
		}

		A = B;								// makes A point to B, therefore, increasing the size of A
		N = nextSize();						// update N
	}
}

// returns the size of the queue
template <typename T> unsigned int DynamicQueue<T>::size()
{
	return (tail - head);
}

// inserts an element at the tail of the queue
// if queue is full, then the grow() function is called
// if the tail of the queue is at the last element of the array, even though the queue is not filled,
// then the elements are shifted to the start of the array
template <typename T> void DynamicQueue<T>::QInsert(T x)
{
	if(isFull()){
		grow();								// grow() function is called if queue is full
	}

	if(tail == N){							// procedure to shift the elements to the start of the queue
		int size = tail - head;				// if the tail reaches the last element of array
		for(int i = 0; i < size; i++){
			A[i] = A[head];
			head++;
		}
		head = 0;
		tail = size;
	}

	A[tail] = x;							// new element x is added at the tail
	tail++;									// tail is updated
}


// deletes the element at the head of the tail
// returns false if the queue is empty
// else returns true, and points x to the deleted element (the old head)
template <typename T> bool DynamicQueue<T>::QDelete(T *x)
{
	if(isEmpty()){
		return false;						// returns false if queue is empty
	}

	x = A + head;							// x is pointed to the head
	head++;									// head is updated
	return true;						
}

