#include<iostream>
#include "queue.h"
#using<namespasestd>

template <typename T> bool DynamicQueue<T> :: isEmpty(){
      return (head==tail);}

template <typename T> unsigned int DynamicQueue<T> :: size(){
             return (N-head+tail)%n;}
             
template <typename T> void DynamicQueue<T> :: grow(){
     T* B;
	B= new T[nextSize()]; 
	for (int i=0; i<N; i++){
		B[i]=A[i]; 
	}
	delete [] A; 
	A=B; 
	N=nextSize(); }             

template <typename T> boolDynamicQueue<T> :: isFull(){
     return(size()==N-1);}
     
template <typename T> void DynamicQueue<T> :: QInsert(T x){
     if(isFull()){grow();}
     else if( tail==N ){ 
		for(unsigned int i=0; i<size(); i++){
			A[i]=A[head+i];
		}
		tail=size(); 
		head=0; 
	} 
     A[tail] = x;
     tail = tail+1;
     return;}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
     if (isEmpty(){
         return false;}
     else *x=A[head];
         head=(head+1)%N;
         return true;}  
      
