//NAME: AKSHAT SINGH
//210020013
//LAB1

#include<iostream>
using namespace std;
#include "queue.h"
template <typename T> bool DynamicQueue<T>::isEmpty() 
{ 
  return (tail==head) ;                                   // WHEN HEAD EQUALS TAIL, MEANS NO ELEMENT REMAINS
}

template <typename T> bool DynamicQueue<T>::isFull(){ 
  return ((tail+1)%N==head);                                   // WHEN HEAD-TAIL=1 OR TAIL-HEAD=N-1, QUEUE IS FULL
  
}

template <typename T> void DynamicQueue<T>::grow(){
  T *B;
  int old=N;
  N=nextSize();
  B = new T[N];
  for(int i=0;i<(old-head+tail)%old;i++){                      // COPYING TO A LARGER ARRAY AND SORTING THEM PROPERLY AS NOW HEAD GOES TO STARTING OF THE QUEUE AND TAIL AT THE END
    B[i]=A[(i+head)%old];
  }
  delete[] A;
  A=B;
  head=0;
  tail=old-1;                                                 // TAIL WOULD BE EQUAL TO ORGINAL NUMBER OF ELEMENTS.
  
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    return (N-head+tail)%N;                                     // CONSIDERING BOTH CASES THAT TAIL IS BEHIND HEAD & HEAD IS BEHIND TAIL.(N-HEAD+TAIL%N) GIVES CORRECT RESULT IN BOTH CASES.
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
  if(isFull()){                                                 // CHECKING IF ELEMENT IS FULL, THEN GROWING IT USING THE grow funciton
    grow();             
    A[tail]=x;                                                  // ADDING THE NEW ELEMENT
    tail++;                                                     // INCREAMENTING THE TAIL.
  } 
  else{
    A[tail]=x;
    
    tail=(tail+1)%N;                                           // USING CIRCULAR INMPLEMENTATION FOR IMPLEMENTING

  }
}


template <typename T> bool DynamicQueue<T>:: QDelete(T *x){
  if(isEmpty()){                                               // CHECKING IF THE QUEUE IS EMPTY
    return false;
  }
  else{
    *x=A[head];                                               
    head=(head+1)%N;                                           // USING THE CIRCULAR IMPLEMENTATION TO INCREASE IT.
    return true;
  }

}

