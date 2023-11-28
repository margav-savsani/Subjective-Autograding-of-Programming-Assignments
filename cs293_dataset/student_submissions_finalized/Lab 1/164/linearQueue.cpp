#include <iostream>
#include "queue.h"

template<typename T>bool DynamicQueue<T> :: isEmpty(){
	if (head==tail)
		return true;
	else return false;
}
template<typename T>bool DynamicQueue<T> :: isFull(){ //if the head is at the initial position and the tail is at the ending postion of the array then
	if (head==0 && tail==N)                         //the queue is said to be full
		return true;
	else return false;
}
template<typename T>void DynamicQueue<T>::grow(){
	N=nextSize();               //when the array is grown we will implement a new array and copy the old elements in to the new array of increased size
	T*arr= new T[nextSize()];
	for (int i=0;i<N;i++)
		{
		arr[i]=A[i];
		}
	T*t=A;
	A=arr;
	delete t;
}
template<typename T>unsigned int DynamicQueue<T>::size(){
	return tail-head;
}
template<typename T>void DynamicQueue<T>::QInsert(T x){ //when the tail is less than N then it means we have still space to fill and we will add our new elements
	if(tail==N && head!=0){       //when the tail is N and the head is not equal to zero then we still have more space at the start to fill
		for(int i=0;i<tail-head;i++)  // so we will move the elements to the start and we will add our new elements at the end
		{A[i]=A[head+i];}
		tail=tail-head;
		head=0;
	}
	if(isFull())//if the head is zero and the tail is N we will grow the array and increase the size of the array and we will add our elements
	{grow();}
	A[tail]=x;
	tail=tail+1;
}
template<typename T>bool DynamicQueue<T>::QDelete(T *x){
	T* t=&(A[head]);
	t=NULL;
	head=head+1;
	return true;
}
