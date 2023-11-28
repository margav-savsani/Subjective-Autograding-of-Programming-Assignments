/*Author:-Yuvraj Singh;Date:-05/08/22;Title:-LinearQueueImplementation*/
#include "queue.h"					//Including the header file queue.h
#include <iostream>
using namespace std;
//Member function isEmpty() returns true when both head and tail have same value that is the queue has no element and false otherwise
template <typename T> 
bool DynamicQueue<T>::isEmpty(){return (head==tail);}
//Member function isFull() returns true if the difference between head and tail indices is equal to the array size N
template <typename T> 
bool DynamicQueue<T>::isFull(){return tail-head==N;}
//Member function grow() creates a new array of nextSize and copies the elements of old array to the new array index by index
//It also updates the size N of the array to nextSize
template <typename T> 
void DynamicQueue<T>::grow(){
	T *B = new T[nextSize()];
	for (int i=head;i<tail;i++){
		B[i]=A[i];
	}
	N=nextSize();
	A=B;
}
//Member function size() returns the number of elements present in the array
template <typename T> 
unsigned int DynamicQueue<T>::size(){ return (tail-head);}
//Member function QInsert(T x) implements the insertion of element x at the tail of the queue according to the case
template <typename T> 
void DynamicQueue<T>::QInsert(T x){
	if (tail==N){					//If the queue has already reached the end
		if(!isFull()){			//Shifts elements to the start of the array if the queue is not full and then inserts x to tail 
			for(int i=head;i<tail;i++){
				A[i-head]=A[i];
			}
			tail=tail-head;
			head=0;
			A[tail]=x;
			tail++;
		}else{				//Otherwise grows the queue and then inserts x to tail
			grow();
			A[tail]=x;
			tail++;
		}
	}
	else{						//If the queue is not at the end then it simply inserts x to tail
		A[tail]=x;
		tail++;
	}
}
//Member function QDelete(T *x) returns false if the queue isEmpty otherwise stores the head element to the pointer *x, makes the second element the head and returns true 
template <typename T> 
bool DynamicQueue<T>::QDelete(T *x){
	if (isEmpty()){return false;}
	else{
		*x=A[head];
		head++;
		return true;
	}
}
/*End of Code*/

