#include<iostream>
#include "queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty(){
   if(head==tail)
      return true;
   else 
      return false;
 }
 
template <typename T> bool DynamicQueue<T> :: isFull(){
   if (size()==N-1) 
       return true; 
   else 
      return false;
 }  
      
template <typename T> void DynamicQueue<T> :: grow(){
  T *B;                   //creating new array B with size equal to the size of the array A after growth
  B=new T[nextSize()];
  
  if(head<tail){
       for(int i=head; i<tail; i++)             // copying the elements of A into B  
           B[i]=A[i];
     }
     
  if(head>tail){
      for(int i=head; i<N; i++)
          B[i]=A[i];
      for(int i=0; i<tail; i++)
          B[i]=A[i];
      head=head+CONST_GROWTH;
    }   
                   
   delete [] A;   //deliting the present array A
    A=B;          // equating array A to array B
   N=nextSize();
 }  

template <typename T> unsigned int DynamicQueue<T> :: size(){
  return (N-head+tail)%N;    //for a circular queue, head can be greater than tail
 }
 
template <typename T> void DynamicQueue<T> :: QInsert(T x){
   if(isFull())
        grow();      // if the queue is full, we have to grow it to the nextsize first and then insert the next element  
         
     A[tail]=x;
     tail=(tail+1)%N;
}      
      
template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
   if(isEmpty()) 
       return false;
   else
     {
       *x=A[head];
        head=(head+1)%N;
       return false;
      } 
  }                    
