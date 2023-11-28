#include "queue.h"

			        
template <typename T> bool DynamicQueue<T>::isEmpty(){
	if(head==tail){
	       return true;}
	else
	{return false;}}
	       	       // is the queue empty?
template <typename T> bool DynamicQueue<T>:: isFull(){
	if(head==0&&tail==N){
	       return true;}
       else{
	       return false;}	}       // is the queue full?
template <typename T> void DynamicQueue<T>:: grow(){
                       T*B ;
		       B= new T[nextSize()];
		      N=nextSize();
		      for(int i=0;i<(tail-head);i++){
			      B[i]=A[i];}
		      delete A;
		      A=B;}

	

       	// grow the queue to its next size 
template <typename T> unsigned int DynamicQueue<T>:: size(){
	return (tail-head) ;} // return the current number of elements in the queue
template <typename T> void DynamicQueue<T>:: QInsert(T x){
	if(tail<N){
	A[tail]=x;	
           tail++;
	   }
	else if(head!=0&&tail==N){
		for (int i=0; i<(tail-head);i++){
			A[i]=A[head+i];}
	     	
		tail=tail-head;
		head=0;
		A[tail]=x;
		tail++;}
	else{
		grow();
		A[tail]=x;
               tail++;}}
		
	      	// insert given element at tail of the queue; grow array size as necessary
template <typename T> bool DynamicQueue<T>:: QDelete(T *x){
	if (head==tail){
	       return false;}
        else{*x=A[head];
		head++;
		return true;}}
	       
			
	       	       // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise


