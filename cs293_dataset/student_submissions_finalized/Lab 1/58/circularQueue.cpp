#include<iostream>
#include "queue.h"
#include<cstdlib>
using namespace std;

template<typename T>bool DynamicQueue<T>::isEmpty(){
		
	return (head==tail);
}

// The queue is set to be return full at N-1 elements,as applied in the class.
// We are using remainder function here whereever applicable.

template<typename T>bool DynamicQueue<T>::isFull(){

	return (N+tail-head)%N==(N-1);
}

//Im creating a new queue of bigger size and copying the elements into it,later reassigning the queue to our original one.
//We start from the head index and go across the entire queue ,if head becomes N,we make it to 0.

template<typename T>void DynamicQueue<T>::grow(){
	
	T *B=new T[nextSize()];
	
	int x=0;
	while(x<N-1){B[x]=A[(x+head)%N];x++;}
	
	delete A;
	A=B;
	head=0;tail=N-1;
	N=N+CONST_GROWTH;
}

template<typename T>unsigned int DynamicQueue<T>::size(){

	return (N+tail-head)%N;
}

//Im calling the grow() func when the queue is full.

template<typename T>void DynamicQueue<T>::QInsert(T x){

	if(isEmpty()){A[0]=x;head=0;tail=1;return;}
	
	else if(isFull()){grow();
	                  A[tail]=x;tail++;
	                  return;}
	             
	else if(tail==N){A[0]=x;tail=1;return;}
	
	else {A[tail]=x;tail++;return;}
}

//Here if head becomes N,we are taking remainder with N,to return it to 0.

template<typename T>bool DynamicQueue<T>::QDelete(T *x){
	
	if(isEmpty()) return false;
	
	else {*x=A[head];A[head]=NULL;
	      head=(++head)%N;
	      return true;}
}


