#include<iostream>
#include "queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty()// I eliminated the condition of full queue having equal head and tail hence head=tail only when empty
{
	if(head==tail)return true;
	else return false;
}

template <typename T> bool DynamicQueue<T> :: isFull()// The tail is always greater than the head and the indexes are actually represented by the modulus of the numbers from head to tail
{
	if((tail-head)==N) return true;
	else return false;
}

template <typename T> unsigned int DynamicQueue<T> :: size()
{
	return tail-head;
}

template <typename T> void DynamicQueue<T> :: grow()
{
	
		T* newArr= new int[N+CONST_GROWTH];//new array created
	
		for(int i=head;i<tail;i++){
			newArr[i-head]=A[i%N];// indexes of the elements are modulus of the numbers from head to tail 
		}
		head=0;
		tail=N;
		delete []A;
		A=newArr;
		N=N+CONST_GROWTH;
		return;
	
}

template <typename T> void DynamicQueue<T> :: QInsert(T x)
{// only 2 conditions possible here either queue is full or not 
	
		if(this->isFull()){
			this->grow();
			A[tail]=x;
			tail++;
			}
		
	
		
		else{
			A[tail%N]=x;
			tail++;
		}
}
		
template <typename T> bool DynamicQueue<T> :: QDelete(T* x)
{
	if(this->isEmpty()) return false;
	
	x=&(A[head]);	
	head++;
	return true;
}
