#include<iostream>
#include"queue.h"


template <typename T> bool DynamicQueue<T>:: isEmpty(){
	return (tail==head && tail==0);
}
template <typename T> bool DynamicQueue<T>:: isFull(){
	return ((tail-head)%N==0 && tail!=0);
}
template <typename T> void DynamicQueue<T>:: grow(){
	if(tail==N && head==0){
		T *B = new T[nextSize()];
		for(int i=0; i<N; i++){B[i]=A[i];}
		A=B;
		N=nextSize();
	}
	if(tail==head && tail!=0){//for example [4,5,6,1,2,3] where head and tail both are 3
		T *B = new T[nextSize()];
		for(int i=0; i<tail; i++){B[i]=A[i];}
		for(int i=0; i<N-tail; i++){B[nextSize()-i-1]=A[N-i-1];}
		A=B;//eventually it will be like [4,5,6,_,_,.....extra spaces added.....,_,_,1,2,3], head=nextSize()-3, tail=3
		    //hence we won't have to rearrange the elements in ascending order from head to tail, we can just add space in between.
		head=nextSize()-(N-head);
		N=nextSize();
	}
}
template <typename T> unsigned int DynamicQueue<T>:: size(){
	if(tail==head && head==0){//empty 
		return 0;
	}
	if(tail>head){ 
		return (tail-head);
	}
	else if(tail<head){
		return(N-head+tail);
	}
	
}
template <typename T> void DynamicQueue<T>:: QInsert(T x){
	if(!(isFull())){A[tail]=x; tail++;}
	if(isFull()){//array is full, we will have to grow it
		grow();
		A[tail]=x;
		tail++;
	}
}
template <typename T> bool DynamicQueue<T>:: QDelete(T *x){
	head=(head+1)%N;//head is increased so we will now ignore the element before head index and consider 
	       //it deleted
	*x=A[head-1];
	if(isEmpty()) return false;
	else return true;
}

