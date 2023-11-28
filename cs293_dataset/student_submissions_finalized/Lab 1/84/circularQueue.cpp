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
	return (head = tail && tail == -1);  //If the queue is empty, head = tail = -1 --????????????
}

template <typename T> bool DynamicQueue<T>::isFull(){
	return (tail = head); //if the next element to be inserted is in the first place (head) itself, it means the array is full ----------
}

template <typename T> void DynamicQueue<T>::grow(){
	N = nextSize(); //
}

template <typename T> unsigned int DynamicQueue<T>::size(){
	if (tail = head){    //array is full  -----------
		return(N);     
	} 
	else if(tail > head){      //tail>head
		return (tail-head);
	}
	else
		return (N+tail-head);		//if tail<head, take mod...

}

template <typename T> void DynamicQueue<T>::QInsert(T x){

	if (tail = head){          // Array is full
		N = nextSize();         // Increase the size
		A[tail] = x;
		tail = tail+1;
	} 

	else{
		A[tail] = x;
		tail = tail+1;
	}
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    
    if (head = tail && tail = -1)          // If queue is empty  ----------------based on empty
    	return 0;        // return false
    else{
    	*x = A[head];     //placing first element in x
		head = head+1;   // moving head to next index deletes the first element	
		return 1;	
    }
}