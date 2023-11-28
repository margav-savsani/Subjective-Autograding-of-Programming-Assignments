#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>

#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty(){
	if (tail-head==0) return true;
	else return false;
}
 // a linearqueue is empty if head and tail are at the same positions.
template <typename T> bool DynamicQueue<T>::isFull(){
	if((head==0) && (tail==N)) return true;
	else return false;
}
 // a linearqueue is filled id head is at the start and tail-1 is at the end
template <typename T> void DynamicQueue<T>::grow(){
	T *S;
	S=new T[N+CONST_GROWTH];
	for(int i=0;i<N;i++){
	S[i]=A[i];}
	A=S;
	N=N+CONST_GROWTH;
}
	 // growing the queue is done by creating a new array
template <typename T> unsigned int DynamicQueue<T>::size(){
	return tail - head;
}
template <typename T> void DynamicQueue<T>::QInsert(T x){
	if(isFull()){
		grow();
	}//grows the queue if the queue is filled
	else if(tail==N){
		for(int i=0;i<size();i++){
			A[i]=A[head+i];
			tail=tail-head;
			head=0;
			
		}
	}//this is the case where even the queue is not filled but tail-1 is at the end
	A[tail]=x;
	tail=tail+1;
} // and finally inserting the element at the tail
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	if(isEmpty()) return false;
	else {
		*x=A[head];
		head=head+1;
		return true;}
}			 // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise


