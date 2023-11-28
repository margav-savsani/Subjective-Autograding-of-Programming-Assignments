#include "queue.h"

template <typename T> bool DynamicQueue<T> :: isEmpty(){
	if((head==0 && tail==0)||(head==tail))return true;
	else return false;
}

template <typename T> bool DynamicQueue<T> :: isFull(){
	if(head==0 && tail==N)return true;
	else return false;
}

template <typename T> unsigned int DynamicQueue<T> :: size(){
	return tail-head;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
	if(this->isEmpty())return false;
	else{
		*x=A[head];
		head++;
		return true;
	}
}

template <typename T> void DynamicQueue<T> :: grow(){
//here growth of the array storing queue happens only when the array is full
	if(head==0 && tail==N){
		T *temp = new T[N+CONST_GROWTH];
		for(int i=0;i<N;i++) temp[i]=A[i];	
		A=temp;
		tail++;
		N+=N+CONST_GROWTH;	
	}
	else return;
}	

template <typename T> void DynamicQueue<T>::QInsert(T x){
	if(tail!=N+1) {	//if last element of the queue is not present at the last in the array A
		A[tail]=x;
		tail++;
	}
	else{
		if(tail-head == N){	//when the queue is full already and an element is to be inserted	
			this->grow();
			A[tail]=x;
			tail++;
		}
		else{	//when the last element of the queue is present at the last of the array A but the array is not full
			for(int i=head;i<tail;i++)
				A[i-1]=A[i];	
			A[tail-1]=x;
		}
	}
}
