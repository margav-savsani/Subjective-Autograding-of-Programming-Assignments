#include<iostream>
using namespace std;

template<typename T>
bool DynamicQueue<T>::isEmpty(){			// this method checks whether the queue is empty or not
	return (head == tail);					//the que is empty when head and tail are equal
}

template<typename T>
bool DynamicQueue<T>::isFull(){				//this method checks whether the queue is full or not 
	if(tail>head)
		return ((tail-head)%N == N-1);		//the queue is full when the their are N-1 elements in the array with size N 
	else
		return (N-(head-tail)%N == N-1);
}

template<typename T>
void DynamicQueue<T>::grow(){
	T *ptr;;
	ptr = new T[nextSize()];
	
	int j=0;
	for (int i=head;i!=tail;){	// this loop copies elements from initial array to new array 
		ptr[j]=A[i];
		i = (i+1)%N;
		j++;
	}
	N = nextSize();
	head = 0;	//updating head and tail 
	tail = j;
	delete []A;		//deleting initial array
	A = ptr;		//copying pointer to new array to A
	ptr = nullptr;	// making the ptr equal to nullptr 
}

template<typename T>
unsigned int DynamicQueue<T>::size(){
	if(tail>head)
		return ((tail-head)%N);		//the queue is full when the their are N-1 elements in the array with size N 
	else
		return (N-(head-tail)%N);		//returns the size of queue
}

template<typename T>
void DynamicQueue<T>::QInsert(T x){
	if(isFull()){		//if queue is full then grow the array(queue)
		grow();
	}
	A[tail] = x;		//inserting required element/object
	tail = (tail+1)%N;
}

template<typename T>
bool DynamicQueue<T>::QDelete(T *x){
	
	if(isEmpty())		//if queue is empty then return false
		return false;
	else{
		*x = A[head];		//storing the value of the object to be deleted/removed from the queue in given poointer x 
		head = (head+1)%N;		//incrementing head
		return true;
	}
}
