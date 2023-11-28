#include "queue.h"
// Circular Queue
template <typename T>
bool DynamicQueue<T>::isEmpty(){
	// Empty when head  = tail and both head and tail are  = 0. The =0 part added because otherwise we cannot differentiate between a filled and empty list
	return (head == tail)&&(head==0);
}
template <typename T>
bool DynamicQueue<T>::isFull(){
        // See the comment in isEmpty()
	return (head == tail)&&(head!=0);
}
template <typename T>
void DynamicQueue<T>::grow(){
	// Make another check that the queue is full
	if (DynamicQueue<T>::isFull()){
		// Make a new array with the nextSize(). Does a method using less extra memory exist? 
		T* B = new T[DynamicQueue<T>::nextSize()];
		for(int i = 0; i< N; i++){
			// Copy A into B, and make it such that head becomes 0
			B[i] = A[(head+i)%N];
		}
		// Reset head and tail
		head = 0;
		tail = N;
		N = DynamicQueue<T>::nextSize();
		//Update N and make the original pointer point to this new array B
        T* C = A;
		A = B;
        delete[] C;
		
	}
}
template <typename T>
unsigned int DynamicQueue<T>::size(){
	// Just a tail-head also works, but this can be reused in circular list as well
    if(head == tail && head!=0){
        return N;
    }
    else if(head == tail && head == 0){
        return 0;
    }
	return (N+tail-head)%N;
}
template <typename T>
void DynamicQueue<T>::QInsert(T x){
	// Make it grow if full
	if(DynamicQueue<T>::isFull()){
		DynamicQueue<T>::grow();
	}
	// Put x at the tail and increment tail
	A[tail] = x;
	tail = (tail+1)%N;	
    if (tail == 0 && head == 0){
        //We have filled the array, with head and tail = 0
        // Need to shift everything to the right by atleast, so that we can distinguish from an empty array
        T* B = new T[N]; 
        for(int i = 0; i<N; i++){
            B[i] = A[(N+(i-1))%N];
        }   
        A = B;
        head = tail = 1;
    }
}	
template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(DynamicQueue<T>::isEmpty()){
        // Return false if the queue was empty
        return false;
    }
	*x = A[head];
	// Do mod N since 
	head = (head+1)%N;
	if(head == tail){ 
		//If the queue is empty, use this opportunity to reset head and tail, because there is no overhead of copying the elements. In circular lists, this also helps us maintain our standard that head=tail=0 means that list is empty, since this is the only place where a queue can be emptied
		head = tail = 0;
	}
    
    return true;
}
	

