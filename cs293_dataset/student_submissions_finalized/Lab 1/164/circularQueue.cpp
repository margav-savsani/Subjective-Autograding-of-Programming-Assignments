#include <iostream>
#include "queue.h"
// head and tail are continously incresed whether the index of last element of the queue is more or less than the index of the head
//the head and tail elements are accessed by using modulo N 
template<typename T>bool DynamicQueue<T> :: isEmpty(){
	if (head==tail)
		return true;
	else return false;
}
template<typename T>bool DynamicQueue<T> :: isFull(){
	if (N==tail-head)
		return true;
	else return false;
}
template<typename T>void DynamicQueue<T>::grow(){
	T*arr= new T[nextSize()];
	for (int i=0;i<N;i++)
		{
		arr[i]=A[(i+head)%N];
		}
    head=0;
    tail=N;
    N=nextSize();
	T*t=A;
	A=arr;
	delete t;
}
template<typename T>unsigned int DynamicQueue<T>::size(){
	return tail-head;
}
template<typename T>void DynamicQueue<T>::QInsert(T x){
	if(isFull())
	{grow();}
	A[tail%N]=x;
	tail=tail+1;
}
template<typename T>bool DynamicQueue<T>::QDelete(T *x){
	T* t=&(A[head%N]);
	t=NULL;
	head=head+1;
	return true;
}
