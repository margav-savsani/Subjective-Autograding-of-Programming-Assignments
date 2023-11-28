#include "queue.h"
#include <iostream>

//IGNORE THE CODE WRITTEN IN COMMENTS

template <typename T> bool DynamicQueue<T>::isEmpty() {
	return (head==tail);                 // if head==tail then the queue is considered to empty
	//return head==-1;
}

template <typename T> bool DynamicQueue<T>::isFull() {
	return (tail-head==N);
	/*
	if(head==0 && tail==N) return true;
	return false;
	*/
}

template <typename T> void DynamicQueue<T>::grow() {
	
	if (isFull()) {                      //if the queue is full, then only the queue gets increased
		T* tmp;
		tmp =new T[N];
		tmp=A;
		A = new T[N+CONST_GROWTH];         //it works by creating a new queue of size N+CONST_GROWTH of A
		                                   //and copying the existing elements to it.
		for (unsigned int i=0; i<N; i++) {
			A[i]=tmp[i];
		}
	
		head=0; tail=N;
		N=N+CONST_GROWTH;
	}
	
	/*
	if(!isFull()) return;
	else {
		T *B;
		B=new T[N];
		B=A;
		A=new T[N+CONST_GROWTH];
		for (int i=0; i<N; i++) {
			A[i]=B[i];
		}
		N=N+CONST_GROWTH;
		return;
	}
	*/
}

template <typename T> unsigned int DynamicQueue<T>::size() {
	return (tail-head);
}

template <typename T> void DynamicQueue<T>::QInsert(T x) {
	
	if (isFull()) {                  // if the queue gets fulled then queue firsts grows in size
		grow();                        // then adds elements to it.
		A[tail]=x;
		tail++;
	}
	
	else if (tail==N) {              // if tail==N but queue is not yet full then shift the elements
		//T tmp[N];                    // so that head==0 and tail<N.

		for (unsigned int i=0; i<N; i++)
			A[i]=A[i+head];
		
	/*	for (int i=0; i<tail-head; i++)
			A[i]=tmp[i];*/
		
		tail=tail-head;
		head=0;

		A[tail]=x;
		tail++;
	}
	
	else {
		A[tail]=x;
		tail++;
	}
	
	/*
	if (isFull()) {grow(); A[tail]=x; tail=N+1; return;}
	else {
		if(tail==N) {
			for(int i=head; i<N; i++) {
				A[i-1]=A[i];
			}
			A[tail-1]=x; head=head-1;
			return;
		}
		else {
			A[tail]=x;
			tail=(tail+1)%N;
			return;
		}
	}
	*/
}

template <typename T> bool DynamicQueue<T>::QDelete(T* x) {
	
	if (isEmpty()) return false;                   // if the queue is empty then return false.
	
	/*else if (head==tail-1) {
		*x=A[head];
		A[head]=0;
	//	head=-1;
	}*/
	
	else {
		*x=A[head];
		A[head]=0;
		head++;
	}
	
	return true;
	
	/*
	if (head==-1) return false;
	else {
		if(tail==head+1) {*x=A[head]; A[head]=0; head=-1; return true;}
		else {*x=A[head]; A[head]=0; head++; return true;}
	}
	*/
}
