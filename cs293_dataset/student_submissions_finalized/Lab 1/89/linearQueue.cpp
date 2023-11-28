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
   if ((tail-head)==N) 
      return true;
  else 
      return false;
 } 

template <typename T> void DynamicQueue<T> :: grow(){
   T *B;                  
   B=new T[nextSize()];     //creating new array B with size equal to the size of the array A after growth
   
   for(int i=0; i<N; i++)
       B[i]=A[i];            // copying the elements of A into B 
   delete [] A;   //deliting the present array A
    A=B;           // equating array A to array B
   N=nextSize();
}
  
template <typename T> unsigned int DynamicQueue<T> :: size(){
   return tail-head;                   // for a linear queue, tail is always greater than head
 } 
  
template <typename T> void DynamicQueue<T> :: QInsert(T x){
  if (isFull()) 
    {
       grow();        // if the size of the array is full we have to grow it to the next size first and then insert
       A[tail]=x;
       tail++;
      } 
   else if (tail==N)
     {
       for(int i=head;i<tail;i++)
         {
           A[i-head]=A[i];      // if the array is not full and the last element is at the last index of the array we have to shift the array such that  
           tail=tail-head;      //   head becomes zero instead of growing the array unnecessarily  
           head=0;
          }
        A[tail]=x;
        tail++;
       }
       
    else 
      {
        A[tail]=x;
        tail++;
       }
}
       
template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
   if(isEmpty()) 
       return false;
   else
     {
       *x=A[head];
       head++;
       return false;
      }
  }  
        
              
