#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>

#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty(){
	if (head==tail) return true;//remember
	else return false;
}
 // queue is empty if head and tail are at the same position
template <typename T> bool DynamicQueue<T>::isFull(){
	if((head==0 && tail==N-1) || head==tail+1) return true;
	else return false;
	
}// took the possibility of head=tail+1 as filled case
 // queue is filled either if head is at the beginning or tail+1=head
template <typename T> void DynamicQueue<T>::grow(){
	T*S=new T[N+CONST_GROWTH];
	if(head<tail){
		for(int i=head;i<tail;i++){
			S[i]=A[i];}}
	else {
		for(int i=head;i<N;i++){
			S[i+CONST_GROWTH]=A[i];}
		for(int i=tail-1;i>-1;i--){
			S[i]=A[i];}
		head=head+CONST_GROWTH;
		}
	delete []A;
	A=S;
	S=NULL;
	N=N+CONST_GROWTH;
};// while growing, the queue need to grow after the tail but not in between the elements of the queue
template <typename T> unsigned int DynamicQueue<T>::size(){
	if(head==tail+1) return N-1;
	else if(head==0 && tail==N-1) return N;
	else {
		if(head<tail){return tail-head;}
		else return N-head+tail;
	}
} 
	
template <typename T> void DynamicQueue<T>::QInsert(T x){
	if(isFull()){
		grow();
		A[tail]=x;
		tail=tail+1;
	}
	else if(tail==N){
		A[0]=x;
		tail=1;
	}
	else{
		A[tail]=x;
		tail=tail+1;
	}
	
}// two new cases arise where the queue is filled or tail-1 is at the end but head is not at the beginning  

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	*x=A[head];
	if(isEmpty()) return false;
	else {
		if(head==N){
			head=0;
		}
		
		head=head+1;
		return true;}
}//we just increase the value of head by 1 keeping the case where head is N in mind

