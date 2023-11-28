#include "queue.h"
#include <iostream>

/*
	If head==tail, then I considered the circular queue to be full,
	and if head==-1 then queue is empty.
	grow() adds the empty array of size CONST_GROWTH to the end of the tail and
	before the head. note that the way I implemented it is such that if
	head==tail==0 then after the queue, head becomes CONST_GROWTH and
	tail becomes 0;
*/

template <typename T> bool DynamicQueue<T>::isEmpty() {
	return head==-1;
}

template <typename T> bool DynamicQueue<T>::isFull() {
	return head==tail;
}

template <typename T> void DynamicQueue<T>::grow() {  //should be defined!
	
	if (isFull()) {
		T* tmp;
		tmp =new T[N];
		tmp=A;
		A = new T[N+CONST_GROWTH];
		
		for (int i=0; i<N; i++) {
			A[(i+head+CONST_GROWTH)%(N+CONST_GROWTH)]=tmp[(i+head)%N];
		}
		
		head=0; tail=N;
		N=N+CONST_GROWTH;
	}
	

}

template <typename T> unsigned int DynamicQueue<T>::size() {
	return (N+head-tail)%N;
}

template <typename T> void DynamicQueue<T>::QInsert(T x) {
	
	if (isFull()) {
		grow();
		A[tail]=x;
		tail=(tail+1)%N;;
	}
	
	else {
		A[tail%N]=x;
		tail=(tail+1)%N;
	}
	
}

template <typename T> bool DynamicQueue<T>::QDelete(T* x) {
	
	if (isEmpty()) return false;
	
	else if ((tail-head)%N==1) {
		*x=A[head];
		A[head]=0;
		head=-1;
	}
	
	else {
		*x=A[head];
		A[head]=0;
		head++;
	}
	
	return true;
}
