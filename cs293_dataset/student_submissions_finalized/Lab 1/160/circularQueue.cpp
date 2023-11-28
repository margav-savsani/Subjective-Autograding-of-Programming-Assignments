#include "queue.h"
//here there is an ambiguity of the case when head=tail as it is true for both the empty and fully filled case
//so we consider that the array is full when filled size is N-1 only instead of N so that head is not equal to tail in that case
template <typename T> bool DynamicQueue<T>::isEmpty(){
	return (head==tail);
}
template <typename T> unsigned int DynamicQueue<T>::size(){
	return((tail-head+N)%N);//this expression is used as the tail can be less than head position also
}
template <typename T> bool DynamicQueue<T>::isFull(){
	return (size()==N-1);
}
//to increase the queue size create a temporary array and copy old elements in correct order and change the address of old array
template <typename T> void DynamicQueue<T>::grow(){
		T *array = new T[nextSize()];
		for(int i=0;i<N-1;i++){
			array[i]=A[((head+i)%N)];
		}
		A=NULL;
		A=array;
		head=0;tail=N-1;	
		N=nextSize();
		return;
}
template <typename T> void DynamicQueue<T>::QInsert(T x){
//if array is full then increase it's size
	if(isFull()) grow();
//here we use %N at a lot of places as we are trying to use circular array	
	A[tail%N]=x;
	tail=(tail+1)%N;
	return;
}
//for deleting the head of array;instead of deleting the element we can just shift the position of head
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	if(!isEmpty()){
		*x=A[head];
		head=(head+1)%N;
	}	
	return (!isEmpty());
}
//########################################################## ANCHA PRANAVI ##########################################################
