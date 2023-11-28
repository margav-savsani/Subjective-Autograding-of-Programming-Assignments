#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){
	return (tail-head == 0);
}
template <typename T> bool DynamicQueue<T>::isFull(){
	return (tail-head == N);
}
template <typename T> void DynamicQueue<T>::grow(){
	T *new_A; // creating a new pointer
	new_A = new T[N]; //setting the size of the new pointer
	for(int i=head;i<tail; i++)
	{
		new_A[i-head]=A[i];
	}
	
	A = new_A; // now copying the whole new queue in our previous queue A
	head=0; 
	tail=N;
	N = nextSize(); //increasing the size
}
template <typename T> unsigned int DynamicQueue<T>::size(){
	return(tail-head); //returning the size of the queue
}
template <typename T> void DynamicQueue<T>::QInsert(T x){
	if(tail==N) grow();
	A[tail]=x; //inserting new element in the last
	tail++; //increasing the tail by 1
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	if(isEmpty()) return false; 
	*x = A[head]; //storing the head elements
	head++; //decreasing the tail by 1 when the head element gets deleted
	return true;
}
