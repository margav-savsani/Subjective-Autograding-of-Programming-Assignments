#include "queue.h"
template <typename T> bool DynamicQueue<T>::isEmpty(){
	return head==tail;
}
template <typename T> bool DynamicQueue<T>::isFull(){
	return tail==nextSize();//the implementation keeps tail==nextSize() if the queue is full
}
template <typename T> void DynamicQueue<T>::grow(){
	if(!isFull())	return;//grow not allowed if queue not full
	T* b=new T[nextSize()];
	for(int i=0;i<N;i++){//copying data to new array
		b[i]=A[(i+head)%N];
	}
	head=0;
	tail=N;
	N=nextSize();
	delete[] A;
	A=b;
	return;
}
template <typename T> unsigned int DynamicQueue<T>::size(){
	if(tail==nextSize())	return N;//tail==nextSize() implies
	return (N+tail-head)%N;
}
template <typename T> void DynamicQueue<T>::QInsert(T x){
	int s=size();
	if(s==N){//if queue is full
		grow();
	}
	if(s==N-1){//if queue will be full after this operation, tail=nextSize() is used to differentiate between full and empty
		A[tail]=x;
		tail=nextSize();
		return;
	}
	A[tail]=x;
	tail=(tail+1)%N;
	return;
}
template <typename T> bool DynamicQueue<T>::QDelete(T* x){
	if(isEmpty())	return false;
	if(isFull()){//if the queue was full, after deletion, a free space will be created, so tail needs to be placed in right place
		tail=head;
	}
	if(x)
		*x = A[head];
	else{
		T b=A[head];
		x=&b;
	}
	head=(head+1)%N;//updating head
	return true;
}
