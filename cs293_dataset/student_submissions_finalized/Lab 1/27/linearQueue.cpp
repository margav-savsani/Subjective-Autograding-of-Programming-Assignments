#include<iostream>
#include "queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty()// only condition where queue is empty will be when head==tail
{
	if(head==tail)return true;
	 return false;
}

template <typename T> bool DynamicQueue<T> :: isFull()// for queue to be full head should be at 0 index and tail at N
{
	if(head==0 && tail==N) return true;
        return false;
}

template <typename T> unsigned int DynamicQueue<T> :: size()
{
	return tail-head;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x)
{
	if(tail==N){                    // if tail is N 2 conditions are there that queue is full or just it needs to be shifted
		if(this->isFull()){ // if queue is full we grow the array 
			this->grow();
			A[tail]=x;
			tail++;
			}
		else{
			int size =tail-head;
			for(int i=0;i<size;i++){  // if not full we shift the elements to the start
			
			A[i]=A[i+head];
			}
			head=0;
			A[size]=x;
			tail=size+1;
		}
	}
		
	else{      
		A[tail]=x;
		tail++;
	}
}

template <typename T> void DynamicQueue<T> :: grow()
{
	
		T* newArr= new int[N+CONST_GROWTH];   // create a new array with new size and then copy all the elements from previous array . then we delete the previous array and assign the variable the pointer of the new array,thereby completely replacing the previous array
	
		for(int i=0;i<N;i++){
			newArr[i]=A[i];
		}
		delete []A;
		A=newArr;
		N=N+CONST_GROWTH;
	
}


		
template <typename T> bool DynamicQueue<T> :: QDelete(T* x)
{
	if(this->isEmpty()) return false;
	
	x=&(A[head]);	
	head++;
	return true;
}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
