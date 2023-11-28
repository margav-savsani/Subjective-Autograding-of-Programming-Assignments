#include "queue.h"
//when head and tail are in same position in linear array it means that the array is empty
template <typename T> bool DynamicQueue<T>::isEmpty(){
	return (head==tail);
}
//as tail means the position next to filled element size is directly given by tail-head
template <typename T> unsigned int DynamicQueue<T>::size(){
	return (tail-head);
}
//if filled size of array (given by size()) is same as size of array then the queue is full
template <typename T> bool DynamicQueue<T>::isFull(){
	return (size()==N);
}
//to increase the queue size creating a temporary array of the new size and copying all the elements into temporary array and then changing the address of old array to the new one with increased size
template <typename T> void DynamicQueue<T>::grow(){
		T *array = new T[nextSize()];
		for(int i=0;i<N;i++){
			array[i]=A[i];
		}
		A=NULL;
		A=array;
		N=nextSize();//as N is also to be changed to the new value
		return;
}
template <typename T> void DynamicQueue<T>::QInsert(T x){
//if the array is full we use grow function to increase size as well as arranging the elements in correct order
	if(isFull()) grow();
//if the array is not full and tail is at the last possible position we shift the elements of the array so that we can add more elements to the end of the array
	else if(tail==N){
		for(int i=head;i<tail;i++){
			A[i-head]=A[i];
		}
		tail=tail-head;
		head=0;
	}
//we add the new element to the end of the array	
	A[tail]=x;
	tail++;
	return;
}
//for deleting the head of array;instead of deleting the element we can just shift the position of head
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	if(!isEmpty()){	
		*x=A[head];
		head++;
	}
	return (!isEmpty());	
}
//########################################################## ANCHA PRANAVI ##########################################################
