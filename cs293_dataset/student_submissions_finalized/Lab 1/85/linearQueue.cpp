#include "queue.h"
#include <iostream>
using namespace std;


  
  template<typename T> bool DynamicQueue<T>::isEmpty(){
	  if(head== 0&& tail == 0){
		  return true;}
	  else return false;} // returns true if queue is empty
   template <typename T> bool DynamicQueue<T>::isFull(){
	  if(tail==N&& head==0){
		  return true;}
	  else return false;}
		 // returns true if queue is full
   template <typename T> void DynamicQueue<T>::grow(){
	  if(head==0 && tail==N){
		  T *B;
		  B=new T[N];   // create a new array and shift all elements of A into it
		  B=A;            
		  A=new T[N+CONST_GROWTH];  //increases size of A and add elements of it from newly created array
		  for(int i=0;i<N;i++){
			  A[i]=B[i];}
		  N=N+CONST_GROWTH;
	         		 
	 }} // grow the queue to its next size 
   template <typename T> unsigned int DynamicQueue<T>::size(){
	  int v=tail-head;
	  return v;} // return the current number of elements in the queue
   template <typename T> void DynamicQueue<T>::QInsert(T x){
	  if(tail==N&&head!=0){
		   for(int u=head;u<N;u++){
		   A[u]=A[u-head];}         
		   head=0;tail=N-head;
		   A[tail]=x;
		   tail=N-head+1;
		   
	  }
          if(tail==N&&head==0){   // if queue if full grows array size and add element at tail of the queue
		   grow();
		   A[tail]=x;
		   tail=N+1;
		   }
	  else A[tail]=x;
          int k=sizeof(A)/sizeof(A[0]);
           tail=k+1;} // insert given element at tail of the queue; grow array size as necessary
   template <typename T> bool DynamicQueue<T>::QDelete(T *x){

        if(head=0&&tail==0){return false;}
	else 
         {*x=A[head];
          A[head]=0;		 
	  head=head+1;
          return true;}}	  
	   // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise

