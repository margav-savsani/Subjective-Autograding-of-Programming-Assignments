#include<iostream>
using namespace std;

template <typename T>
bool DynamicQueue <T>::isFull(){
		if(size() == N)    //if number of elements in array = size of array then the queue must be full
			return true;
		else return false;
	}
template <typename T>
bool DynamicQueue <T>::isEmpty(){
		if(size() == 0)  //head == tail for an empty queue
			return true;
		else return false;
	}

template <typename T>
void DynamicQueue <T>::grow(){
		N = nextSize();   //increasing N
		T*B;              //B is new array of increased size 
		B = new T[N];
		for (int i=0 ; i<N-1000; i++){
			B[i]=A[i];      //copying all elements of A in the same order
		}
		A=B;              //A is now the new array of increased size but the same elements
	}

template <typename T>
unsigned int DynamicQueue <T>::size(){ 
		return tail-head;     //difference of indices of head andd tail is the number of elements in array(tail is empty)
	}

template <typename T>
void DynamicQueue <T>::QInsert(T x){
		if(isFull())grow();   //increase size of array if full
		A[tail++] = x;       //inserting new element x in array and incrementing tail
	}

template <typename T>
bool DynamicQueue <T>::QDelete(T *x){
		if (isEmpty())return false;  //cannot delete element if queue is empty 
		*x = A[head];                //storing element at head at new location 
		//head++;
		for(int i=0;i<N-1;i++ ){     //shifting the array ahead
			A[i]=A[i+1];
		}
		tail--;
		return true;
	}