#include<iostream>
using namespace std;

template<typename T>
bool DynamicQueue<T>::isEmpty(){        // this method checks whether the queue is empty or not
	return (head == tail);				//the queue is empty when head is equal to tail in 
}										//linear queue


//this method checks whether the queue is full or not.
//Note: The queue is full when tail-head (which also represents the size of the queue) is equal to N which is equal to the array size. Also note that there are instance where tail-head is not equal to N but then also we can't add more objects in the queue and we need to grow the array(since head may not be equal to 0

template<typename T>					 
bool DynamicQueue<T>::isFull(){	 					 
		return (tail-head == N);		
}


template<typename T>
void DynamicQueue<T>::grow(){
	unsigned int m {nextSize()-N};		// m contains the GROWTH CONSTANT by which size of array is incremented 
	T *ptr; 
	if(N <= tail-head+m)         // when the head is too far from 0 that is even more than or equal to 0+GROWTH CONSTANT , I don't create a new array with increased size but a new array of the same size as before.
		N = nextSize();
	ptr = new T[N];
	
	int j=0;
	for (int i=head;i<tail;i++){					//this loop runs and copies the elements/
		ptr[j]=A[i];								//objects from initial array to the new 
		j++;										//aray with increases size
	}
	
	delete []A;	//deleting the initial array
	A = ptr;	//copying the pointer to the new array to A
	ptr = nullptr;	//making the ptr point to nullptr
	int size = tail-head; 
	head = 0;			//updating head and tail
	tail = head+size;
}


template<typename T>
unsigned int DynamicQueue<T>::size(){
	return (tail-head);  //returns size of the queue
}


template<typename T>
void DynamicQueue<T>::QInsert(T x){
	if(tail>=N){	//when tail is greate than or equal to N,that means we need to grow our array since otherwise A[tail] will be invalid and may lead to many type of errors or fauts
		grow();
	}
	A[tail] = x; 
	tail++;
}


template<typename T>
bool DynamicQueue<T>::QDelete(T *x){
	if(isEmpty())
		return false;
	else{
		*x = A[head];			//storing the value of the object to be deleted in given poointer x 
		head++;					//incrementing head 
		return true;
	}
}
