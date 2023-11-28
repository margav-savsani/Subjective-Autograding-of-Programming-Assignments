#include "queue.h"

template <typename T> bool DynamicQueue<T> :: isEmpty(){     /* to check if the array is empty or not */ 
	if (head==tail) return true;
	else return false;
	}
	

template <typename T> bool DynamicQueue<T> :: isFull(){     /* to check if the array is filled or not */
	if ((tail-head)==N) return true;
	else return false;	
	}
	

template <typename T> void DynamicQueue<T> :: grow(){       /* increses size of array in case required */
	T *B;
	B = A;                                              /* address of A is assigned to B*/
	A = new T[nextSize()];
	for(int i=0;i<N;i++){A[i]=B[i];}                    /* copying previous data */
	N=nextSize();
	}
	
	
template <typename T> unsigned int DynamicQueue<T> :: size(){ /*returns the current size of array*/
	return (tail-head);
	}
	

template <typename T> void DynamicQueue<T> :: QInsert(T x){   /* inserts an element at tail*/ 
	if(tail==N){
		if(isFull()) grow();                           /* if full then need to grow its size*/
		else {
			for(int i=0;i<tail-head;i++){A[i]=A[head+i];}
			tail = size();
			head = 0;                              /*moving the array to front */
			} 
		}	
	A[tail]=x;
	tail++;
	}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){ /*delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise*/
	if(isEmpty()){return false;}
	*x = A[head];
	head++;
	return true;
	}



















