/*Author:-Yuvraj Singh;Date:-05/08/22;Title:-CircularQueueImplementation*/
#include "queue.h"					//Including the header file queue.h
#include <iostream>
using namespace std;
//Member function isEmpty() returns true when both head and tail have same value that is the queue has no element and false otherwise
template <typename T> 
bool DynamicQueue<T>::isEmpty(){return (head==tail);}
//Member function isFull() returns true when tail is just behind head in circular queue that is there is only one position left at the tail
//Leaving one position prevents ambiguity between queue being empty and full
template <typename T> 
bool DynamicQueue<T>::isFull(){return head==(tail+1)%N;}
//Member function grow() creates a new array of nextSize and copies the element of old array by traversing it in circular fashion and pastes it in the new array starting from 0th index
//It also updates the size of array n to nextSize
template <typename T> 
void DynamicQueue<T>::grow(){
	T *B = new T[nextSize()];
	int i=head,j=0;
	while (i!=tail){
		B[j]=A[i];
		i=(i+1)%N;
		j++;
	}
	N=nextSize();
	A=B;
	head=0;
	tail=j;
}
//Member function size() returns the number of elements present in the array
template <typename T> 
unsigned int DynamicQueue<T>::size(){return ((tail-head+N)%N);}
//Member function QInsert(T x) implements the insertion of element x at the tail
template <typename T> 
void DynamicQueue<T>::QInsert(T x){
	if (isFull()){			//If queue isFull then it first grows and then inserts x to tail
		grow();
		A[tail]=x;
		tail=(tail+1)%N;	//tail incremented in circular fashion
	}
	else{				//Else it just inserts x to tail
		A[tail]=x;
		tail=(tail+1)%N;	//tail incremented in circular fashion
	}
}
//Member function QDelete(T *x) returns false if the queue isEmpty otherwise stores the head element to the pointer *x, makes the next element in the circular queue the next head and returns true
template <typename T> 
bool DynamicQueue<T>::QDelete(T *x){
	if (isEmpty()){return false;}
	else{
		*x=A[head];
		head=(head+1)%N;
		return true;
	}
}	
/*End of Code*/		
		
