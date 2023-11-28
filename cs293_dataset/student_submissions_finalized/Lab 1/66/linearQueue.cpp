#include <iostream>
using namespace std;
#include "queue.h"



 template <typename T> bool DynamicQueue<T>::isEmpty(){
     if(size()==0)
          { return true;}
     else
          { return false;}

 } 
  
 template <typename T>bool DynamicQueue<T>::isFull(){
     if(size()==N)
         {return true;}
     else
         {return false;}

 } 
 
  template <typename T>void DynamicQueue<T>::grow(){
     T *b=new T[N];                                                 // creating another array to copy elements
     for(int i=0;i<N;i++) b[i]=A[i];                                // copying elements
    
     A = new T[nextSize()];                                         // Increasing array size
     for(int i=0;i<N;i++) A[i]=b[i];
    
     delete[] b;                                                    // deleting array created                                                   
   
     head=0;tail=N;
     N=nextSize();                                                  // increasing variable representing size of array
  } 
  
  template <typename T>unsigned int DynamicQueue<T>::size(){
      return tail-head ;

  } 
  
  template <typename T>void DynamicQueue<T>::QInsert(T x){
      
      if(!(isFull())&&tail==N) {                                    // shifting elements to left if tail becomes N but array is not full
      for(int i=head;i<tail;i++) A[i-head]=A[i];
      head=0;tail=tail-head;
      }
      
      if(head==0&&tail==N){grow();}                                // increasing array size if it is full

      A[tail]=x;
      tail=tail+1;

  }
  
  template <typename T>bool DynamicQueue<T>:: QDelete(T *x){
    if(head==tail){ return false;}                                 
    
    if(head!=tail){
          A[head] =NULL;                                        
          head=(head+1)%N;
          return true;
          }

  }
