#include<iostream>
#include<cmath>
using namespace std;
#include"queue.h"
  
template <typename T>bool DynamicQueue<T>:: isEmpty(){
     if (tail-head==0){
        return true;
        }
     else {
         return false;
         }
      } // is the queue empty?
  template <typename T> bool DynamicQueue<T>:: isFull(){
     if (head==0 && tail-head==N-1){
         return true;
         }
      else if(head==1 && tail==N){
         return true;
         }
      else if(head>tail && head-tail==2){
         return true;
         }
     else {
         return false;
         }
      } // is the queue full?
  template <typename T> void DynamicQueue<T>:: grow(){
      T* S;
      S= new T[nextSize()];
      int j=0;
       if(head==0){
          for(int i=0;i<N-1;i++){
              S[j]=A[i];
              j=j+1;
              }
          A=S;
          N=nextSize();
          }
       else {
           for(int i=head; i<N;i++){
               S[j]=A[i];
               j=j+1;
               }
          if(tail!=N){
           for(int k=0; k<tail;k++){
               S[j]=A[k];
               j=j+1;
               }
             }
            A=S;
            head=0;
            tail=N-1;
            N=nextSize();
           }
      } // grow the queue to its next size 
  template <typename T> unsigned int DynamicQueue<T>:: size(){
      return (tail-head+N)%N;
      } // return the current number of elements in the queue
  template <typename T> void DynamicQueue<T>:: QInsert(T x){
       if(isFull()){
          grow();
          A[tail]=x;
          tail=tail+1;
          }
       else{
         if(tail==N-1){
          A[tail]=x;
          tail=0;
          }
         else {
           A[tail]=x;
           tail=tail+1;
           }
        }
        }
           // insert given element at tail of the queue; grow array size as necessary
  template <typename T> bool DynamicQueue<T>:: QDelete(T *x){
      if(isEmpty()){
         return false;
         }
      else{
         *x=A[head];
         if(head==N-1){
         head=0;
         return true;
           }
         else{
          head=head+1;
          return true;
          }
         }
        } // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise

