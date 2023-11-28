#include<iostream>
#include"queue.h"


template <typename T> bool DynamicQueue<T>:: isEmpty(){
	return (tail==head);
}
template <typename T> bool DynamicQueue<T>:: isFull(){
	return (tail-head==N);
}
template <typename T> void DynamicQueue<T>:: grow(){
	T *B = new T[nextSize()];
	for(int i=0; i<N; i++){B[i]=A[i];}
	A=B;
	N=nextSize();
}
template <typename T> unsigned int DynamicQueue<T>:: size(){
	//eg: [5,6,7,1,2,3,4,_,_,_,_] head=3, tail=7, length=7-3=4, the 5,6,7 were elements that had
	//been previously 'deleted', but are still showing in the array  but we have already changed
	//the head to 3
	return (tail-head);
}
template <typename T> void DynamicQueue<T>:: QInsert(T x){
	if(tail!=N){A[tail]=x; tail++;}
	if(tail==N && head!=0){//eg: [1,2,3,4,5] but head=2, tail=5 means 1,2 were 'deleted' and
	                         //will now be overridden
		for(int i=0; i<tail-head-1; i++){
			A[i]=A[head+i];//we shift all elements backwards to create space behind tail, 
			               //and we override the deleted elements
		}
		tail=tail-head;
		head=0;
	}
	if(tail==N && head==0){//array is full, we will have to grow it
		grow();
		A[tail]=x;
		tail++;
	}
}
template <typename T> bool DynamicQueue<T>:: QDelete(T *x){
	head++;//head is increased so we will now ignore the element before head index and consider 
	       //it deleted
	*x=A[head-1];
	if(tail==0) return false;
	else return true;
}

