#include<iostream>
using namespace std ;
#include "queue.h"
template <typename T>bool DynamicQueue<T>::isEmpty(){
      if(tail==head &&A[head]==NULL)   //empty and full condition is almost same ,just that empty head element is containing null
       return true;// for full we need to check whether it is full or not
       else return false;
  }



  template <typename T>bool DynamicQueue<T>::isFull(){
      if(tail==head &&A[head]!=NULL)//if head is not null then it is full in addition to condition of head and tail equality
       return true;// for full we need to check whether it is full or not
       else return false;
  } // is the queue full?
 template <typename T> void DynamicQueue<T>:: grow(){
     T *B=new T[N];
    for(int i=head;i<N;i++) B[i-head]=A[i];// here i had made another array and copied al the elemments from their into a new array 
    for(int i=0; i < tail;i++){// in starting i'm filling from head to n-1 then from o to tail
     B[N-head+i]=A[i];
    }
    A = new T[nextSize()];  
    for(int i=0;i<N;i++) A[i]=B[i];
    head=0;tail=N;// now making A to point out to new array
    N=nextSize();  // changing variable representing size of array

  } // grow the queue to its next size
 template <typename T> unsigned int DynamicQueue<T>::size(){

    if(isEmpty())
    return 0;// for number of elements
    else if(tail>head)
    return tail-head;
    else 
    return N-tail+head;
  } // return the current number of elements in the queue
  template <typename T>void DynamicQueue<T>::QInsert(T x){
     if(size()==N)//if no space is left in the array we can increse it's size then we can do ithe usual stuff of inserting the element
       grow();
        A[tail]=x;
        tail=(tail+1);

  } // insert given element at tail of the queue; grow array size as necessary
  template <typename T>bool DynamicQueue<T>:: QDelete(T *x){

     if(isEmpty())// if the queue is empty we can't delete anything hence false
        return false;
    
    A[head]=NULL;// 
    head=(head+1)%N;
    return true;

  } // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise



