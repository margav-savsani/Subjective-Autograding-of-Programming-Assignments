#include<iostream>
using namespace std;

template <typename T>
bool DynamicQueue <T>::isFull(){
		if(size()== N-1)    //if number of elements in array = size of array then the queue must be full
			return true;
		else return false;
	}
template <typename T>
bool DynamicQueue <T>::isEmpty(){
		if(head == tail)    //head == tail for an empty queue
			return true;
		else return false;
	}

template <typename T>
void DynamicQueue <T>::grow(){
		N = nextSize();    //increasing N
		T *B;              //B is new array of increased size 
		B = new T[N];
		for(int i = 0; i < N-1-1000; i++){
			B[i] = A[i];
		}
		A = B;           //A is now the new array of increased size but the same elements
	}

template <typename T>
unsigned int DynamicQueue <T>::size(){
		return (N-(head-tail))%N;  //head-tail=part of the circular queue that is empty if the queue passes through index 0 and N-1
	}

template <typename T>
void DynamicQueue <T>::QInsert(T x){
		if(isFull())grow();
		A[tail++] = x;
	}

template <typename T>
bool DynamicQueue <T>::QDelete(T *x){
		if (isEmpty())return false;
		*x = A[head];    //storing the element at head at new location
		head++;          //new head will be at (old head+1)
		return true;
	}