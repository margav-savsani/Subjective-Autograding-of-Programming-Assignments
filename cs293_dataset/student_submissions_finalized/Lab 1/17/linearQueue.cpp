#include<iostream>
#include "queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty(){
     return (head==tail);}

template <typename T> bool DynamicQueue<T> :: isFull(){
    return (tail-head==N);}
    
template <typename T> void DynamicQueue<T> :: grow(){
       T* B;
	B= new T[nextSize()]; 
	for (int i=0; i<N; i++){
		B[i]=A[i]; 
	}
	delete [] A; 
	A=B; 
	N=nextSize(); 
}
 
        
template <typename T> unsigned int DynamicQueue<T> :: size(){
             return tail-head;}

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
     if (isEmpty()){
         return false;}
     else *x=A[head];
         head=head+1 ;
         return true;}  

