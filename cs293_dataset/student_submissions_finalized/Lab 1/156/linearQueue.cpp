
#include "queue.h"

template <typename T> unsigned int DynamicQueue<T>::size(){
	return tail-head;
}

template <typename T> bool DynamicQueue<T>::isEmpty(){
	if(size()==0) return true;
	else return false;
}

template <typename T> bool DynamicQueue<T>::isFull(){
	if(size()==N) return true;
	//on being full the head and tail indexes would be the same , but thats in the empty queue too so we 
	//have to assure that N is not equal to zero 
	else return false;
}

template <typename T> void DynamicQueue<T>::grow(){
	//we need to delete the initial array and reallocate a new one with new size as else it
	//would give an malloc top size error
	N = nextSize();
	A = (T*)realloc(A,N*sizeof(T));
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
	//check first if array is full or not , if full then first grow its size and then insert the new element
	//if not full but tail is at n then rearrange first and then insert the next element
	if(isFull()){
		grow();
	}
	else if(tail==N){
		int sz = size(); //tail has to be changed to size() and size() depends on tail and so storing it is req.
		for(int i=head;i<tail;i++){
			A[i-head] = A[i];
		}
		tail = sz;
		head = 0;
	}
	A[tail] = x;
	tail++;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	if(size()==0) return false;
	else{
		*x = A[head];
		head = head + 1;
		return true;
	}
}