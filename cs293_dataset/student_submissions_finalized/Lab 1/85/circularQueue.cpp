#include "queue.h"
#include <iostream>
using namespace std;

  template <typename T>bool DynamicQueue<T>:: isEmpty(){
           if(A[head]==0){
                  return true;}
          else return false;} // if the queue if empty returns false
   template <typename T>bool DynamicQueue<T>:: isFull(){
          if(sizeof(A)/sizeof(A[0])==N){  // checks if size of the queue is equal to N
                  return true;} 
          else return false;}
                 // returns true if queue if full
   template <typename T>void DynamicQueue<T>:: grow(){
          if(isFull()){
		  
                   T *B;
                  B=new T[N];            // create a new array and shift all elements of A into it
                  for(int v=0;v<N;v++){
			  B[v]=A[(head+v)%N];
	          delete A;		  
                  A=new T[nextSize()];    // increases the size of array and shifts all elements into A which were 
		                          // stored in new array 
                 for(int i=0;i<N;i++){
                          A[i]=B[i];}
                  N=N+CONST_GROWTH;
		  head=0;
		  tail=N;
                   
                   
         }}} // grow the queue to its next size
   template <typename T>unsigned int DynamicQueue<T>:: size(){
          int v=sizeof(A)/sizeof(A[0]);
          return v;} // return the current number of elements in the queue
   template <typename T>void DynamicQueue<T>:: QInsert(T x){
          if(isFull()){          // if queue is full grows size of it and adds elements at tail of the queue        
                     grow();
    		     A[tail++]=x;
	             }
          else {A[tail]=x;
           tail=(tail+1)%N;}} // inserts given element at tail of the queue
   template <typename T>bool DynamicQueue<T>:: QDelete(T *x){

        if(isEmpty()){return false;}
	if(size()==1){       
	   *x=A[head];
           A[head]=0;
	   head=-1;
	   tail=0;
	   return true;}
        else
         {*x=A[head];
          A[head]=0; 		 
          head=head+1;
          return true;}}
           // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
