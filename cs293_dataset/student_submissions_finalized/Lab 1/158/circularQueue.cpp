//circularQueue.cpp

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include "queue.h"

using namespace std;
using namespace std::chrono;




template<typename T>unsigned int DynamicQueue<T>:: size(){
    return (N - head + tail)%N;}  //When tail is ahead of head, mod N will reduce the size to the correct value. modN remains ineffective as long as tail<head

template<typename T>bool DynamicQueue<T>::isEmpty() {
	if (head==tail) // head==tail is allowed to occur only in case of emptiness. In case queue is full, we maintain tail at 1 position behind head
 		return 1;
 	else
        return 0;

}

template<typename T>bool DynamicQueue<T>::isFull() {
	if ( size()==N-1) // size is N-1 when either head==0 and tail==N-1 OR tail is just behind head 
		return 1;
	else
        return 0;

}
template<typename T>void DynamicQueue<T>::grow(){

	T *X = new T[nextSize()]; 

    int p=0;
    for(int k=head;k!=tail;k++){
    if (k==N){k=0;} // makes sure that k, the index moving through the old array loops around
    
    X[p] = A[k];p++; // p is the index at which entry is amed in the new array


    }

	//changing aassociated values for the new array
	tail = N - head +tail ;
	head = 0;
	N = nextSize();
	delete[] A;
	A = X;




}



template<typename T>void DynamicQueue<T>::QInsert(T x){
	if (size()==N-1) // grows in case full, else just adds to the end
        grow();
    A[tail]=x;
    tail= (tail+1)%N; // mod makes sure tail loops around the array




}


template<typename T>bool DynamicQueue<T>::QDelete(T *x){
	if (head ==tail){return false;}// can't delete from an empty array

	else {
		*x = A[head];
		
		head = (head+1)%N;//mod makes sure head loops around
    return true;
	}






}
