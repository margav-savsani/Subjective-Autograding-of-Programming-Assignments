//NAME: AKSHAT SINGH
//210020013
//LAB1

#include<iostream>
using namespace std;
#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty() 
{ 
  return (tail-head==0) ;                                       // WHEN HEAD EQUALS TAIL, MEANS NO ELEMENT REMAINS
}

template <typename T> bool DynamicQueue<T>::isFull(){ 
  return ((tail-head)==N);                                       // ONLY WHEN TAIL-HEAD=N, QUEUE IS FULL
  
}

template <typename T> void DynamicQueue<T>::grow(){
  T *B;
  N=nextSize();
  B = new T[N];
  for(int i=0;i<(tail-head);i++){                        // COPYING THE ELEMENTS TO A BIGGER ARRAY
    B[i]=A[i];
  }
  delete[] A;
  A=B;                                                 // USING THE NEXT SIZE FUNCTION TO INCREASE THE SIZE OF THE QUEUE
}

template <typename T> unsigned int DynamicQueue<T>::size(){
  return (tail-head);                                            // FOR LINEAR QUEUE, TAIL IS ALWAYS >= HEAD. AS TAIL IS NEXT INSERTION SPOT. SO, TAIL-HEAD GIVES NUMBER OF ELEMENT

}

template <typename T> void DynamicQueue<T>::QInsert(T x){
  if(isFull()){                                                 // GROWING THE QUEUE IF IT IS FULL
    grow();
    A[tail]=x;                                                  // USING TAIL TO INSERT
    tail++;                                                     // INCREASING TAIL AFTER INSERTION
  }
  

  else if(tail==N){                                             // IF TAIL= N BUT QUEUE ISNT FULL THEN WE NEED TO RE ARRANGE THE ELEMENTS AND CHANGE HEAD & TAIL
    unsigned int sizearray= size();                                           // TOTAL ELEMENTS
    for(int i=0;i<sizearray;i++){
      A[i]=A[head+i];                                               // HEAD IS 1ST ELEMENT
    }
    head=0;                                                      // FIRST ELEMENT IS AT ZERO INDEX
    tail=sizearray;                      
    A[tail]=x;                                                   //ADDING USING THE USUAL PROCESS
    tail++;
  }

  else{
    A[tail]=x;                                                   // NO CONDITION THEN NORMAL ADDING AND INCREASING THE TAIL
    tail++;
  }
}

template <typename T> bool DynamicQueue<T>:: QDelete(T *x){
  if(isEmpty()){
    return false;
  }
  else{
    *x=A[head];
    head++;                                                 // STORING IT IN GIVEN *T
    return true;  
  }

}



