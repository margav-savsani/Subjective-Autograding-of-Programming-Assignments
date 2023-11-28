

#include<iostream>
#include "queue.h"
template <typename T>  bool DynamicQueue<T>::  isEmpty(){
  if (size() ==0){
  	return 1;}
  else return 0;}
  template <typename T>bool DynamicQueue<T>::  isFull(){//checking size is full or not
  if(size() ==N){
  	return 1;}
  else return 0;}
  
  template <typename T>void DynamicQueue<T>::  grow(){//growing array size 
  T *B ;
  B = new int[nextSize()];
  for(int i=0 ;i<N;i++){
 	B[i]=A[i];}
 	A=B;
 	}
  template <typename T>unsigned int DynamicQueue<T>:: size(){//size function for differebt possible cases in circular queue
    if(tail-head<0){
   	return N-(tail-head);}
    if( tail-head==0 and A[head] == NULL){
    	return 0;
    }
    if(tail-head==0 and !(A[head]== NULL)){
    	return N;}
    else return tail-head;
   }
 template <typename T> void DynamicQueue<T>::  QInsert(T x){//inserting element
	if(!size() == N){
		if(tail==N){
		A[0]=x;}
		else A[tail]=x;
		}
	else {
		grow();//growing array and again storing elements from 0 index
		for(int i=0;i<N;i++){
		A[i] =A[(head+i)%N];}
		A[N]=x;
	}
}
 template <typename T> bool DynamicQueue<T>::  QDelete(T *x){
	if(!size() ==0){//deleting element and just shiftinh head to next element returning true if size is not empty and false if empty
		*x = A[head];
		for (int i= head;i<size();i++){
            		 A[i%N]= A[(i+1)%N];}
   
		return 1;}
	else  return 0;
}





