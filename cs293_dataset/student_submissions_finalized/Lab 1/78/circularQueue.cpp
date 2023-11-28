#include"queue.h"



template <typename T> bool DynamicQueue<T>::isEmpty(){
	return(head==tail || (head==0 && tail==0));
} 

template <typename T> bool DynamicQueue<T>::isFull(){
	if(head==0 && tail== N)return true;
	else return false;
}

template <typename T> void DynamicQueue<T>::grow(){
	if(this->isFull()){	//growth happens only when the array storing the queue is full
		T *temp = new T[N+CONST_GROWTH];
		int a=0;
		int i=head;
		do{
			temp[a]=A[i];
			a++;
			i++;
		}
		while(i!=head);
		head=0;
		tail=a;
		A=temp;
		N+=CONST_GROWTH;
	}
	else return;
}

template <typename T> unsigned int DynamicQueue<T>::size(){
	return ((N-head+tail) % N);
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
	if(this->isFull()){	//when the array storing the queue is already full and a new element is to be inserted 
		this->grow();
		A[tail]=x;
		tail++;
	}
	else{	//when the queue is not full and a new element can be inserted in the existing queue
		A[tail]=x;
		tail=(tail+1)%N;
	}
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	if(this->isEmpty()) return false;
	else{
		*x = A[head];
		head=(head+1) % N;
		return true;
	}
}
