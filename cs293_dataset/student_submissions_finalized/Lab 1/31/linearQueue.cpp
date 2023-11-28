#include "queue.h"

template <typename T>
bool DynamicQueue<T>::isEmpty(){
	return (head==0 && tail==0); 
}

template <typename T>
bool DynamicQueue<T>::isFull(){
	return (size()==N); // if number of elements are N then true and viceversa
}

template <typename T>
void DynamicQueue<T>::grow(){
	if(size()==N){ // if the queue isFull, then increase its length by CONST_GROWTH
		T *B = new T[nextSize()];  // copy all the elements from A(initial array) to B(new array with increased size) index-wise
		for(int i=0; i<N; i++){
			B[i] = A[i];
		}
		delete[] A;   //deallocate memory of initial array(i.e where A is pointing to)
		A = B;        // Now, point A(initial array) to the new array(B)
		N = nextSize();  
	}
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
	return (tail-head);
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
	if(tail==N){          
		if(isFull())      //if its full, then grow the array
			this->grow();
		else{             //if tail is at the end, but head is not at the start(i.e some space is available at the start of the array), then rearrange the array such that head is 0
			for(int i=0; i<tail-head; i++)
				A[i] = A[head+i];	//copy elements one by one, to the start of the array(from head to tail)
			tail = tail-head-1;		//update tail and head
			head=0;

		}
	}	
	A[tail]= x;
	tail++;

}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
	if(isEmpty()) // if empty, then return false
		return false;
	*x = A[head];  //value to which 'x' points to will be that of the deleted element
	head++;
	return true;
}


