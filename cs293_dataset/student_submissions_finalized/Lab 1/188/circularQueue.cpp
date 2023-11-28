#include "queue.h"
  // adding template <typename T> is necessary for compilation. To override class functions, we include the header file and then use <class_name>::function to override the function of class
  template <typename T> bool DynamicQueue<T>::isEmpty(){// is the queue empty?
  	if(head == tail) return true;// if tail=head then there are no elements in queue
  	else return false;
  } 
  template <typename T> bool DynamicQueue<T>::isFull(){ // is the queue full?
  	if((N + (tail - head)) % N == N - 1) return true;// as this is circular array tail-head may not give us the no of elements in the queue
  	else return false;// so we have to use the above expression for finding size. also we donot allow size to become N here as it overlaps with size=0 in case of circular queue
  }
  template <typename T> void DynamicQueue<T>::grow(){// grow the queue to its next size 
    
  	T* B = new T[nextSize()];// first creating a new bigger array with nextSize()
	  	for (int i=0; i<N; i++){
	  		B[i] = A[i]; // copying the elements of first array into other one
	  	}
	  	A = B; //now re-assigning this big array to the array
	  	B = NULL;// making B to null
	  	N = nextSize();// changing N to its new size
	  }
  
  template <typename T> unsigned int DynamicQueue<T>::size(){
  	return (N + (tail - head)) % N; // size for circularQueue
  } // return the current number of elements in the queue
  template <typename T> void DynamicQueue<T>::QInsert(T x){// insert given element at tail of the queue; grow array size as necessary
  	if(isFull()){
  		grow(); // if Full we have to grow our Queue
  	}
  	A[tail] = x;// tail is the index where the element is to be inserted
  	tail = (tail + 1) % N;// tail move to the next index in a circular way
  	 
  } 
  template <typename T> bool DynamicQueue<T>::QDelete(T *x){// delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
  	if(isEmpty()) return false;
  	else{
  		*x = A[head]; // storing the head element
  		A[head] = 0; // making head element to zero
  		head = (head+1)%N;// head moves to next posn in case of circular array
  		return true;
  	}
  
  } 
