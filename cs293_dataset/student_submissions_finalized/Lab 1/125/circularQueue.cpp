#include "queue.h"
unsigned int positiveMod(int x, int y){
	if(x>=0) return x%y;
	else{
		return (y+x%y)%y;
	}
}
template <class T>
bool DynamicQueue<T>::isEmpty(){
	if(head==tail) return true;
	else return false;
}
template <class T>
bool DynamicQueue<T>::isFull(){
	if(N+1==tail) return true; //tail = N+1 is an encoding for the queue being full
	else return false;
}
template <class T>
void DynamicQueue<T>::grow(){
	N = nextSize();
}
template <class T>
unsigned int DynamicQueue<T>::size(){
	if(isFull()) return N;
	return positiveMod((tail-head),N);
}
template <class T>
void DynamicQueue<T>::QInsert(T x){
	if(this->isFull()){
		T *B;
		B = new T[this->nextSize()]; //create a bigger array
		for(int i = 0; i<N; i++){
			//copy the original queue
			B[i]=A[positiveMod((i+head),N)];
		}
		B[N]=x;
		tail=N; //set Tail to the correct value
		head = 0; //set head to 0
		delete[] A;
		A=B;
		this->grow(); //update N
		return;
	}
	A[tail]=x;
	tail = positiveMod((tail+1),N); //update tail
	if(head==tail) tail = N+1; //Set tail to N+1 if queue is full.
}
template <class T>
bool DynamicQueue<T>::QDelete(T*x){
	if(this->isEmpty()){
		return false;
	}
	if(this->isFull()){
		//if tail is N+1, set tail to the correct value.(head)
		tail = head;
	}
	*x = A[head];
	if(head==positiveMod((tail-1),N)){
		head = tail = 0; //set head and tail to 0 if queue becomes empty
		return true;
	}
	head++;
	head = positiveMod(head,N); //update head.
	return true;
}
