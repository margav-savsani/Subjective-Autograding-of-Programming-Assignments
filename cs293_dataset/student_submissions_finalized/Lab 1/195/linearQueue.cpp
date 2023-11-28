#include<iostream>
#include<cmath>
using namespace std;
#include"queue.h"
  
 template <typename T>bool DynamicQueue<T>:: isEmpty(){
     if (tail==head){
        return true;
        }
     else{
        return false;
        }
      } // is the queue empty?
  template <typename T> bool DynamicQueue<T>:: isFull(){
     if ((tail==N)&&(head==0)){
         return true;
         }
     else {
         return false;
         }
      } // is the queue full?
  template <typename T> void DynamicQueue<T>:: grow(){
      N=nextSize();
      T* S;
      S= new T[N];
       for(int i=0; i<N-CONST_GROWTH; i++){
           S[i]=A[i];
           }
      A=S;
      } // grow the queue to its next size 
  template <typename T> unsigned int DynamicQueue<T>:: size(){
      return (tail-head);
      } // return the current number of elements in the queue
  template <typename T> void DynamicQueue<T>:: QInsert(T x){
      if(isFull()){
          grow();
          A[tail]=x;
          tail=tail+1;
          }
      else if(tail==N){
          int j=0;
          for(int i=head; i<tail;i++){
             A[j]=A[i];
             j=j+1;
             }
          tail=size();
          head=0;
          A[tail]=x;
          tail=tail+1;
          }
      else{
         A[tail]=x;
         tail=tail+1;
         }
        }
           // insert given element at tail of the queue; grow array size as necessary
  template <typename T> bool DynamicQueue<T>:: QDelete(T *x){
      if(isEmpty()){
         return false;
         }
      else{
         *x=A[head];
         head=head+1;
         return true;
         }
        } // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise

