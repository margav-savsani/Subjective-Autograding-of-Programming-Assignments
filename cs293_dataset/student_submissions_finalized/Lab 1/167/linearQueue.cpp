#include <iostream>
#include "queue.h"
using namespace std;

  template <typename T> bool DynamicQueue<T> ::isEmpty(){// is the queue empty?
     if (head==tail)              //if the queue is empty then head is equal to tail else not
	return true;
     else 
	return false;
  }
      
      
   template <typename T> bool DynamicQueue<T> ::isFull(){      // is the queue full?
      if (tail-head==N)           // if the queue is full then size should be equal to N
       return true;
      else 
       return false;
   } 
      
      
   template <typename T> void DynamicQueue<T> :: grow(){
      T *X=new T[nextSize()];                // grow the queue to its next size 
      for (unsigned int i=head;i<tail;i++){        
        X[i]=A[i];
        }                                        //I used a new array of nextSize(size) and copied all elements of a to x
      delete [] A;
      N=nextSize();
      A=X;
  }  
  
  
  template <typename T> unsigned int DynamicQueue<T> ::size(){
      return tail-head;                         //size=tail-head
  } 
  
  
  
  template <typename T> void DynamicQueue<T> ::QInsert(T x){     // insert given element at tail of the queue; grow array size as necessary
      if (size()==N){ 
        grow();         //when size=N we'll grow the queue and then insert
        A[tail]=x;
        tail++;
        }
        
      else if(tail==N ){
        unsigned int i=0;
        for (unsigned int j=head;j<tail;j++){     //when tail=N & size!=N ,I shifted all the elements to the leftmost (head=0) and inserted the new element
          A[i++]=A[j];
          }
        A[i++]=x;
        tail=i;
        head=0;
        }
      
      else 
       tail=tail+1;
       A[tail-1]=x;       //inserting the elment
  }
       
       
       
   template <typename T> bool DynamicQueue<T> ::QDelete(T *x){
       
       if (size()==0) return false;   //empty case
       else 
        *x=A[head];  //deleting the element and updating head
        head++;
        return true;
   } // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise


