#include "queue.h"

template <typename T> bool DynamicQueue <T> :: isEmpty(){
    if(head == tail)                       // if head and tail are at same index .. means no element
       	return true;
	else
	 	return false;
}

template <typename T> bool DynamicQueue <T> :: isFull(){
	if(tail - head == N)                   // tail = N and head = 0 ....means full                                 
		return true;
	else
		return false;
}

template <typename T> void DynamicQueue <T> :: grow(){
	int P = N;
	if(this-> isFull()){                  // if array is full ..then make new array of more size and copy elemens from older to new
		N = this->nextSize();
		T * B = new T[N];
		for(int i = 0 ; i < P ;i++)
			B[i] = A[i];
		T * c = A;
		delete(c);	
		A = B;
	}
}

template <typename T> unsigned int DynamicQueue <T> :: size(){
    return tail - head;
}

template <typename T> void DynamicQueue <T> :: QInsert(T x){
	if(tail == N){                       // if tail = N ..check if there is still some space left at the begining
		if(head == 0){					 // if there isn't then only grow...otherwise shift the elements of array
			this->grow();
			A[tail] = x;
			tail ++;
		}
		else{
			for(int i = head; i < N; i++)
				A[i - head] = A[i];

			tail = tail - head;
			head=0;
			A[tail] = x;
			tail ++;
		}
	}
	else{
		A[tail]= x;
		tail ++;
	}
}

template <typename T> bool DynamicQueue <T> :: QDelete(T* x){
	if(this-> isEmpty())
		return false;

	else{
		*x = A[head];
		head ++;                         // on deleting element index of head inc
		return true;
	}
}


