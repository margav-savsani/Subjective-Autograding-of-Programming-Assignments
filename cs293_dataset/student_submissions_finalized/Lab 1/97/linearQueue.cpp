/* 
CS 293
Lab Assignment 1
Om Godage
*/

#include <iostream>
#include "queue.h"

using namespace std;

//tells if the queue is empty
template <typename T>
bool DynamicQueue<T>::isEmpty(){
	return (head == tail);
}

// tells if the queue is full
template <typename T>
bool DynamicQueue<T>::isFull(){
	return size() == N;
}

// grows the queue, by allocating a larger memory for the array, and copying over all the previous elements
template <typename T>
void DynamicQueue<T>::grow(){
	T *B;
	B = new T[nextSize()];
	for(int i = 0; i < size(); i++){
		B[i] = A[head + i];
	}
	N = nextSize();
	delete[] A;
	A = B;
}

// gives the number of elements stored in the queue
template <typename T>
unsigned int DynamicQueue<T>::size(){
	return tail - head;
}

// checks if the queue is full, if it is, then grows the queue, else adds an element, also if queue is not full, but 
// the tail reaches the end of the linear queue, then shifts the head to 0
template <typename T>
void DynamicQueue<T>::QInsert(T x){
	A[tail] = x;
	tail++;
	if(isFull()){
		grow();
		int temp = size();
		head = 0;
		tail = temp;
	}
	else if(tail == N){
		for(int i = 0; i < size(); i++){
			A[i] = A[head + i];
			A[head+i] = 0;
		}
		tail = size();
		head = 0;
	}
}

// checks if the queue is empty, and if not, deletes the first element
template<typename T>
bool DynamicQueue<T>::QDelete(T *x){
	if(isEmpty())
		return false;
	else{
		*x = A[head];
		A[head] = 0;
		head++;
		return true;
	}
}
