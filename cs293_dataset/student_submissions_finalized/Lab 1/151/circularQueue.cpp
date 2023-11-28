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
			B[i] = A[(head + i)%N];			// copies each element of queue A into the bigger queue B
		}

		A = B;								// makes A point to B, therefore, increasing the size of A
		head = 0;							// updates head and tail
		tail = N;
		N = nextSize();						// update N

	}
}



// returns the size of the queue, with the help of modulo function
template <typename T> unsigned int DynamicQueue<T>::size()
{
	return (tail - head) % N;
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

	A[tail] = x;							// new element x is added at the tail
	tail = ++tail % N;						// tail is updated

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
	head = ++head % N;						// head is updated
	return true;						
}

