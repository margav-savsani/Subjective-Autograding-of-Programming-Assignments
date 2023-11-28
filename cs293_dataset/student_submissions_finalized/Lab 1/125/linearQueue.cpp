#include "queue.h"
template <class T>
bool DynamicQueue<T>::isEmpty(){
	if(head==tail) return true;
	else return false;
}
template <class T>
bool DynamicQueue<T>::isFull(){
	if(head==0&&tail==N) return true;
	else return false;
}
template <class T>
void DynamicQueue<T>::grow(){
	N = nextSize();
}
template <class T>
unsigned int DynamicQueue<T>::size(){
	return tail-head;
}
template <class T>
void DynamicQueue<T>::QInsert(T x){
	if(this->isFull()){
		T *B;
		B = new T[this->nextSize()]; //create a larger array
		for(int i = 0; i<N; i++){
			B[i]=A[i];
		}
		B[tail]=x; //insert the element
		tail++;
		delete[] A;
		A=B;
		this->grow();
		return;
	}
	if(tail==N){
		//shift array if tail is N, and queue is not full
		for(int i = 0; i<tail-head; i++){
			A[i]=A[head+i];
		}
		tail = tail-head;
		head = 0;
		A[tail]=x;
		tail++;
		return;
	}
	A[tail]=x;
	tail++;
}
template <class T>
bool DynamicQueue<T>::QDelete(T*x){
	if(this->isEmpty()){
		//Cannot delete from an empty array
		return false;
	}
	*x = A[head];
	if(head==tail-1){
		head = tail = 0; //set head and tail to 0 if queue becomes empty
		return true;
	}
	head++;
	return true;
}
