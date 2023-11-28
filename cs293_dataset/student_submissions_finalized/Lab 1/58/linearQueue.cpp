#include<iostream>
#include "queue.h"
using namespace std;

//I purposedly made an empty set to have the head=tail attribute so that when size() is called,it gives correct output.

template<typename T>bool DynamicQueue<T>::isEmpty(){

	return (tail==head);
}
	
template<typename T>bool DynamicQueue<T>::isFull(){

	return (tail-head==N);
}

// New queue of bigger size is created elements are copied to it.Later reassigned that to our original queue.
//This is gonna take more time cause its in a linear fashion.
	
template<typename T>void DynamicQueue<T>::grow(){

	T *B=new T[nextSize()];
	
	for(int i=0;i<N;i++){B[i]=A[i];}
	
	delete A;
	A=B;
	
	N=N+CONST_GROWTH;
}
	
template<typename T>unsigned int DynamicQueue<T>::size(){

	return (tail-head);
}

//When inserting in an empty list,I made sure that head takes 0,tail takes 1 after insertion cause empty list can be created by deleting single element not at 0positon
//This is cause i dont wanna change the constructor properties.
//If the queue is full,grow func is called.
//When the tail takes 'N' but size is not N,the elements are rearranged.
//This also takes much time as it is linear.
 	
template<typename T>void DynamicQueue<T>::QInsert(T x){

	if (isEmpty()) {A[0]=x;head=0;tail=1;return;}
	
	else if(isFull()){ grow();
	                   A[tail]=x;tail++;
	                   return;
	                 }
	              
	else if(tail==N){ for(int i=head;i<N;i++){A[i-head]=A[i];}
	                  tail=tail-N+size();A[tail]=x;tail++;
	                  head=0;
	                  return;
	                }   
	
	else A[tail]=x;tail++;return;
}

//Here while deleting an empty set,I reduced the tail rather than increasing the head cause I didn't want head to cross (N-1).
//This will not affect any other functionalities.
	
template<typename T>bool DynamicQueue<T>::QDelete(T *x){

	if(isEmpty()) return false;
	
	else if(size()==1){*x=A[head];A[head]=NULL;tail--;
	                   return true;}
	
	else {*x=A[head];A[head]=NULL;head++;
	      return true;}
}	      
	            
	              

	
	

