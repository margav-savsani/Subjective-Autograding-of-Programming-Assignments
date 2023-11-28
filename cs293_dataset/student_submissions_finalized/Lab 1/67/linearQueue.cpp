#include "queue.h"
template <typename T> bool DynamicQueue<T>::isEmpty(){
	return head==tail;
}
template <typename T> bool DynamicQueue<T>::isFull(){
	return head==0 && tail==N;
}
template <typename T> void DynamicQueue<T>::grow(){
	if(!isFull())	return;//not allowed to grow if array is not full
	T* b=new T[nextSize()];
	for(int i=0;i<N;i++){//copying the previous array
		b[i]=A[i];
	}
	N=nextSize();
	delete[] A;
	A=b;
}
template <typename T> unsigned int DynamicQueue<T>::size(){
	return tail-head;
}
template <typename T> void DynamicQueue<T>::QInsert(T x){
	if(tail!=N){//there is space available at end
		A[tail]=x;
		tail++;
		return;
	}
	if(head==0){//tail==N and head==0 at this point, i.e. the array is full
		grow();
		QInsert(x);
		return;
	}
	int size=DynamicQueue<T>::size();
	for(int i=0;i<size;i++){
		A[i]=A[head+i];//moving all the data such that head = 0
	}
	tail=size;
	head=0;
	A[tail]=x;
	tail++;
	return;
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	if(!size())	return false;//empty queue
	if(x)
		*x=A[head];
	else{//if x is NULL pointer
		T b=A[head];
		x=&b;
	}
	head++;
	return true;
}
