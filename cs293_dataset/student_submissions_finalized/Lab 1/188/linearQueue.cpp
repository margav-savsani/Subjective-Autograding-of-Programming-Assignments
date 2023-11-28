
#include "queue.h"

	template <typename T> bool DynamicQueue<T>::isEmpty(){// is the queue empty?
	  	if(head == tail) return true;// tail-head gives us the no of elements in the queue
	  	else return false;
	  } 
	template <typename T> bool DynamicQueue<T>::isFull(){ // is the queue full?
	  	if(tail - head == N) return true;// tail-head gives us the no of elements in the queue
	  	else return false;
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
	  	return tail - head;
	  } // return the current number of elements in the queue
	template <typename T> void DynamicQueue<T>::QInsert(T x){// insert given element at tail of the queue; grow array size as necessary
	  	if(isFull()){
	  		grow();// have to grow size if queue is full 
	  		
	  	}
	  	A[tail] = x;// tail is the index where the next element must be inserted
	  	tail++;// tail must increase
	  	
	  } 
	template <typename T> bool DynamicQueue<T>::QDelete(T *x){// delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
	  	if(isEmpty()) return false;// if queue is empty it must return false
	  	else{
	  		*x = A[head];// stored in other value
	  		for(int i=head; i<tail ; i++){// we are shifting all the elements to the left so that head is always 0
	  			A[i] = A[i+1]; // this ensures that we grow when the elements are more than the size of array
	  		}
	  		tail--;// tail decreases as we shift the elements to left.
	  		return true;
	  	}
	  
	  } 

