#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#define CONST_GROWTH 1000
#include "queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty(){

	return(tail == head );
	
}

template <typename T> bool DynamicQueue<T>::isFull(){

	return(tail  == N );  //I made sure that when the queue has N elements occupied tail becomes N
	
}

template <typename T> void DynamicQueue<T>::grow(){
	T* b;
	b = new T[this->nextSize()];
	int c;
	if(tail !=N) c = ((N+tail-head)%N);    //c will be equal to size()
    else c=N;
	for( int i=0 ; i< c ; i++ ){
		b[i]= A[((head+i)%N)];
	}
	tail = c;
	head=0;

	
	N= this->nextSize();
	delete[] A;
	A = b;
	
}

template <typename T> unsigned int  DynamicQueue<T>::size(){

	if(tail==N) return N;
	return ((N+tail-head)%N) ;
	
}

template <typename T> void DynamicQueue<T>::QInsert(T x){

	if(!this->isFull()){
		A[tail]=x;
		tail++;
		tail= tail%N;
		if(tail==head) tail=N;  //making sure that when queue is full tail =N
		
	}
	
	else{
		this->grow();
		A[tail]=x;
		tail++;
		
	}	
	
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){

	if(tail==head) return 0;
	*x=A[head];
	head++;
	head=head%N;
	
	return 1;

}
