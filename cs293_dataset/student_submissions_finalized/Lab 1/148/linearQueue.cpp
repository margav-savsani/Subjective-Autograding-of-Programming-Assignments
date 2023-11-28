#include "queue.h"
template <typename T>
bool DynamicQueue<T>::isEmpty(){
	// Empty when head  = tail
	return DynamicQueue<T>::size() == 0;
}
template <typename T>
bool DynamicQueue<T>::isFull(){
	return DynamicQueue<T>::size() == N;
}
template <typename T>
void DynamicQueue<T>::grow(){
	// Make another check that the queue is full
	if (DynamicQueue<T>::isFull()){
		// Make a new array with the nextSize(). Does a method using less extra memory exist? TODO
		T* B = new T[DynamicQueue<T>::nextSize()];
		for(int i = 0; i< N; i++){
			// Copy A into B, and make it such that head becomes 0
			B[i] = A[(head+i)%N];
		}
		head = 0;
		tail = N;
		N = DynamicQueue<T>::nextSize();
		//Update N and make the original pointer point to this new array B
        T* C = A;
		A = B;
        // Delete the previous array, so that we don't make any dangling pointers
        delete[] C;
		
	}
}
template <typename T>
unsigned int DynamicQueue<T>::size(){
	return tail-head;
}
template <typename T>
void DynamicQueue<T>::QInsert(T x){
	// Make it grow if full
	if(DynamicQueue<T>::isFull()){
		DynamicQueue<T>::grow();
	}
	if(tail == N){
		// If tail == n and the queue is not full, this means that we have some padding at the start. We move the head to 0
		for(int i = head; i<tail; i++){
			A[i-head] = A[i];
		}
		// Update tail and head
		tail = N-head;
		head = 0; 
	}
	// Put x at the tail and increment tail
	A[tail] = x;
	tail++;
}	
template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    
	if(DynamicQueue<T>::isEmpty()){
        return false;
    
    }
	*x = A[head];
	head = head+1;
	if(DynamicQueue<T>::isEmpty()){
		//If the queue is empty, use this opportunity to reset head and tail, because there is no overhead of copying the elements.
		head = tail = 0;
	}
    return true;
}
	



