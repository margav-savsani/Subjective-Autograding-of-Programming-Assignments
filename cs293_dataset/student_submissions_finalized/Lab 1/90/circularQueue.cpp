#include <iostream>
#include "queue.h"

using namespace std;
/*
We here are implementing Circular Queue, 
Briefing the Strategy:
Here front = start of queue, rear= end of queue. 
Eg: We add the next element to A[0] after A[N-1].
	1) Simply insert(at rear) and delete(at front) elements without affecting the other elements until:
	2) If size becomes equal to N-1 i.e, The array will be filled up upon next insertion, so grow the array and then insert.

*/
template <typename T>
unsigned int DynamicQueue<T>::size(){
	 return (N+tail-head)%N;
	 //Number of elements in Queue.
}

template <typename T>
bool DynamicQueue<T>::isEmpty(){
	return (tail==head);
	//Empty Queue
}

template <typename T>
bool DynamicQueue<T>::isFull(){
	return (head==(tail+1)%N);
	//Full Queue(We assume that a queue is called full if there is just one block left)
	//We do this because there is a conflict in checking size N and size =0, as in both the case head-tail=0.
	//We can rather have another method, which could be good enough but needs an assumption that a particular value isn't been stored in the arrays.
	// For example say -1 will never be input by the user into the arrays. So we can use -1 as a recognizer for an empty array.
	//But since this assumption may fail as the question allows every possible data type, we don't consider this method 
}

template <typename T>
void DynamicQueue<T>::grow(){
	unsigned int Nnew = nextSize();
	// Create a new array with size = nextSize()
	T* Anew = new T[Nnew];
	// Copy the elements present in the old array to the new array
	unsigned int start = head;
	for(unsigned int i=0;i<size();i++){
		Anew[i] = A[(start+i)%N];
	}
	//The front of old array is at the 0th position in the new array.
	//The rear of the old array is at the size()-1 position in the new array.
	//Update head and tail values
	tail = size();
	head = 0;
	// Delete the old array
	delete [] A;
	//Update A,N
	A = Anew;
	N = Nnew;
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
	// Grow the array if array is full.
	if(isFull()) grow();
	// Insert a new element and increment value of tail
	tail = (tail+1)%N;
	A[tail] = x;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
	// Empty Queue has nothing to remove
	if(isEmpty()) return false;
	// Assign value to *x
	*x = A[head];
	//Increment value of head in a circular fashion
	head = (head+1)%N;
	return true;
}

