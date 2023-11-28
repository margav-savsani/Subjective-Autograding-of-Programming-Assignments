#include <iostream>
#include<cmath>
#include "queue.h"
using namespace std;

   template <typename T> bool DynamicQueue<T> ::isEmpty(){
      if (tail==head)             //if the queue is empty then head is equal to tail else not
       return true;               
      else 
       return false;  
    }
      
      
   template <typename T> bool DynamicQueue<T> ::isFull(){
      if (size()==N-1) 
       return true;                   // if the queue is full then size should be equal to N-1 but the condition for linearqueue is diff from this
      else 
       return false;
    } 
      
      
   template <typename T> void DynamicQueue<T> :: grow(){    // grow the queue to its next size 
      T* X;
	X= new T[nextSize()]; // A new array is created with the nextSize
	if(head<tail){
		for (int i=head; i<tail; i++){
			X[i]=A[i];   //copying all the elements of A to X
		}
	}
	
	if(head>tail){
		for (int j=head; j<N; j++){
			X[j]=A[j]; 
		}
		
		for (int k=0; k<tail; k++){
			X[k]=A[k]; 
		}
		head+=CONST_GROWTH;
	}
	delete [] A; 
	A=X; 
	N=nextSize(); //size of the new array       
   } 
  
  
  template <typename T> unsigned int DynamicQueue<T> ::size(){
      return (N-head+tail)%N;     //size=(N-head+tail)%N diff from that of linear
   } // return the current number of elements in the queue
 
  
   template <typename T> void DynamicQueue<T> ::QInsert(T x){  // insert given element at tail of the queue; grow array size as necessary
      if (size()==N-1){
        grow();    //when size=N we'll grow the queue 
        
       }
      
      A[tail]=x;     //else just insert the element in circularqueue
      tail=(tail+1)%N;
       
}
    
   template <typename T> bool DynamicQueue<T> ::QDelete(T *x){
     if (head==tail) return false;
     else
       *x=A[head];    //deleting the element and updating head
       head=(head+1)%N;
       return true;
    }// delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise


