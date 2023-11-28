//LinearQueue.cpp

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include "queue.h"

using namespace std;
using namespace std::chrono;



template<typename T>bool DynamicQueue<T>::isEmpty() {
	if (head==tail) // a linear queue is empty only if head=tail=0
 		return 1;
 	else
        return 0;

}

template<typename T>bool DynamicQueue<T>::isFull() {
	if (tail==N && head==0) // we maintain the queue such that if full, then the head and tail are at 0 and N respectively
		return 1;
	else
        return 0;

}
template<typename T>void DynamicQueue<T>::grow(){
	// the queue grows by constant size and old array is deleted. Each element is effectively mapped to an index it had in the old array
	N = nextSize(); 
	T *B = new T[N];
	for (int i=head;i<=tail-1;i++) {B[i-head]=A[i];} 
	delete[] A;
	A = B;
	



}
template<typename T>unsigned int DynamicQueue<T>:: size(){
    return tail - head;} // head may not be at 0 always. So length of queue is not just tail; it is tail - head


template<typename T>void DynamicQueue<T>::QInsert(T x){
	if (isFull()){//grows and adds an element simply
        grow();
        A[tail]=x;
        tail++;
        }
        
    //if the tail is at N, and head >0 then an additional element can be filled into the array. However, to maintain linearity of queue, new element should be inserted at the end of queue. So, we shift all the elements to the left such that head becomes 0 again and then finally insert the new element. 
    else if (size()<N && tail==N){
        for(int k=head;k<=tail-1;k++){
            A[k-head]=A[k];
            }
        tail = tail - head;
        head = 0;
        A[tail]=x; tail++;
        }
    else {
        A[tail]=x; tail++;// when tail is not yet at N
        }

}


template<typename T>bool DynamicQueue<T>::QDelete(T *x){
	if (isEmpty()){return false;}

	else {
		*x = A[head];//simply increments the head. so, head=0 is not always true. 
		head++;
    return true;
	}






}



