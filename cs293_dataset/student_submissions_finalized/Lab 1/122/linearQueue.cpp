#include<iostream>
#include "queue.h"
  
  template <typename T>  bool DynamicQueue<T>::  isEmpty(){
  if (size() ==0){
  	return 1;}
  else return 0;}
  template <typename T>bool DynamicQueue<T>::  isFull(){
  if(size() ==N){
  	return 1;}
  else return 0;}
  
  template <typename T>void DynamicQueue<T>::  grow(){//growing array size
  T *B ;
  N=nextSize();
  B = new int[nextSize()];
  for(int i=0 ;i<N;i++){
 	 B[i]=A[i];}
 	 A=B;head=0;tail=N;}
  template <typename T>unsigned int DynamicQueue<T>:: size(){//return size of array
   return tail-head;}
 template <typename T> void DynamicQueue<T>::  QInsert(T x){//inserts a element
 	if(!size()==N && tail==N){
		for(int i=0;i<size();i++){
			A[i]=A[head+i];//shifting the array  to left if last element is occupied
}
}
	if(!size() ==N && !(tail==N)){
		A[tail]=x;
		tail+=1;}
	if(size()==N){
		grow();//growing array if size is full
		A[N]=x;//adding element at the end
		tail+=1;}
}

 template <typename T> bool DynamicQueue<T>::  QDelete(T *x){//deleting a element 
	if(!size() ==0){
		*x = A[head];
		for(int i= head;i<size();i++){//shifting elements to left
			A[i] = A[i+1];}
		
		return 1;//returning true if array is not empty
}
	else  return 0;//returning false if array is not empty
}



