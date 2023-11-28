#include <iostream>
#include "queue.h"
using namespace std;

/*template <typename T> 
class DynamicQueue<T>::DynamicQueue(){
	unsigned int N =  INIT_SIZE;  //N -> Array size (initially INIT_SIZE)
    T *A = new T[N];
    unsigned int head = 0;  //Index of first element
    unsigned int tail = 0;  //Index of next element to be inserted (index of last element = t-1)
    unsigned int nextSize() { return N+CONST_GROWTH; }
}*/
 
template <typename T> bool DynamicQueue<T>::isEmpty(){
	return (tail == 0);  //If the queue is empty, tail = zero (means element to be inserted is at the index 0)
}

template <typename T> bool DynamicQueue<T>::isFull(){
	return (head == 0 && tail == N); //No. of elements in the queue = array size
}

template <typename T> void DynamicQueue<T>::grow(){
	N = nextSize(); //
}

template <typename T> unsigned int DynamicQueue<T>::size(){
	return (tail - head);     // elements are from head to tail-1 so no.of elements from head to tail-1 = tail-1-head+1
}

template <typename T> void DynamicQueue<T>::QInsert(T x){

	if (tail == N){
		N = nextSize();
		A[tail] = x;
		tail = tail+1;
	} 

	else{
		A[tail] = x;
		tail = tail+1;
	}
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    
    if (tail == 0)       // If queue is empty, 
    	return 0;        // return false
    else{
    	*x = A[head];    //placing first element in x
		head = head+1;   // moving head to next index deletes the first element		
		return 1;
    }
}