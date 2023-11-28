#include <iostream>
using namespace std;
#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty(){
          if(head==tail) {return true;}
          else {return false;}
}
        
template <typename T> bool DynamicQueue<T>::isFull(){
          if(tail-head==N) {return true;}
          else {return false;}
}



template <typename T> void DynamicQueue<T>::grow(){
          T *b=new T[nextSize()];                               //here i had made another array and copied al the elemments from their into a new array 

          for(int i=0;i<N;i++) b[i]=A[i];                       //copying elements of A into b
          A=b;                                                  // now making A to point out to new array
          head=0; tail=N;
          N = nextSize();                                       // changing variable representing size of array
}

template <typename T> unsigned int DynamicQueue<T>::size(){
          return tail-head;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
          if(tail==N&&head!=0) {                                // checking if tail reached end but array is not full
                for(int i=head;i<tail;i++) A[i-head]=A[i];      // shifting elements to left
                tail=tail-head;head=0;}
          if(isFull()) grow();                                  // increasing array size if it is full 
          A[tail]=x;
          tail=tail+1;                                          //making tail 0 if it is N-1 previously 
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
         if(isEmpty()) {return false;}// if the queue is empty we can't delete anything hence  return false
         else {   A[head]=NULL;
                          if(head==N-1) {head=0;tail=0;}       //making head 0 if it is N-1 previously 
                             else {head=head+1;}
                             return true;
                             }
         
}