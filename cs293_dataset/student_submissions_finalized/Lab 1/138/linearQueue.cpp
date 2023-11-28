#include<iostream>

using namespace std;
#include"queue.h"

#define CONST_GROWTH 1000
#define INIT_SIZE 1000

// if the queue is empty, true is returned otherwise false is returned
template <typename T>bool DynamicQueue<T>:: isEmpty(){
	if(size()==0)return true;
	return false;
}
// if the queue is full, true is returned
template <typename T>bool DynamicQueue<T>:: isFull(){
	if(tail==N && head==0) return true;
	return false;
}

template <typename T>void DynamicQueue<T>:: grow(){
// grows the queue 
	if(isFull()){
		N=nextSize();
		T* B;
	B=new T[N];
	for(int i=0;i<N-CONST_GROWTH;i++){
		B[i]=A[i];
	}
	A=B;
	}
}

//returns the size of the queue
template <typename T>unsigned int DynamicQueue<T>:: size(){
	return tail-head;
}

//
template <typename T>void DynamicQueue<T>:: QInsert(T x){
    if(isFull()){
			grow();
		}
    if(tail==N&&head!=0){
        T* B;
			B=new T[N];
			int k=0;
			for(int i=head;i<tail;i++){
				B[k]=A[i];
				k++;
			}
			head=0;
			tail=k;
    }

//inserting the element
	A[tail]=x;
	tail=tail+1;//incrementing the tail
}

//deleting an element from the head
template <typename T>bool DynamicQueue<T>:: QDelete(T* x){
//element can be deleted only if the array is not empty
	if(size()!=0){
		*x=A[head];

		A[head]=0;
		head=head+1;
		return true;
	}
	return false;
}