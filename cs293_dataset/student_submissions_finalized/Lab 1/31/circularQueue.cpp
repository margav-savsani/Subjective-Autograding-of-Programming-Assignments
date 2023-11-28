#include "queue.h"

template <typename T>
bool DynamicQueue<T>::isEmpty(){
	return (head==0 && tail==0);
}

template <typename T>
bool DynamicQueue<T>::isFull(){
	return (size()==N);
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
	if(tail>head || (tail==0 && head==0))
		return (tail-head);	//circulation didnt happen(i.e same as linear-queue)
	else 
		return(N-head+tail); //circulation happened
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
	if(isEmpty())  //if empty, return false
		return false;
	*x = A[head];
	head++;
	return true;
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
	if(tail==N && !isFull()){ //if tail is at the end, but we have some space at the start of the array, then start filling that space, by making tail=0
		tail=0;		// this makes tail<head, unlike linear-queue
	}
	else if(isFull()){ //if isFull, then grow the array
		this->grow();
	}
	A[tail] = x;
	tail++;

}

template <typename T>
void DynamicQueue<T>::grow(){
	if(head<tail){	//general case(i.e same as linearQueue)
		T *B = new T[nextSize()];	
		for(int i=0; i<N; i++){	// copy all the elements from A(initial array) to B(new array with increased size) index-wise
			B[i]=A[i];
		}
		delete[] A; //deallocate memory of initial array(i.e where A is pointing to)
		A = B;		// Now, point A(initial array) to the new array(B)
		N = nextSize();
	}

	else {		// if circulation happened
		T *B = new T[nextSize()];
		int j=0;
		for(int i=head; i<N; i++){ //first copy elements one by one, from head to end of array, to B(new array pointer)  
			B[j]=A[i];
			j++;
		}
		for(int i=0; i<head; i++){// next copy elements one by one from index '0' to 'head-1', to B(new array) continuing the already existing elements
			B[j]=A[i];
			j++;
		}
		delete[] A; //deallocate memory 
		A=B;	// A points to new array now
		head = 0;
		tail = N;
		N = nextSize();
	}
}