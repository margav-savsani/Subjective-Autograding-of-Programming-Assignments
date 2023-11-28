#include <iostream>
#include"queue.h"

template<typename T>bool DynamicQueue<T> ::  isEmpty(){
if(tail-head==0)  return 1;
     else return 0;
} 
template<typename T>bool DynamicQueue<T> ::  isFull(){
if(tail-head==N) return 1;
     else  return 0;}
template<typename T>void DynamicQueue<T> ::  grow(){
 T *b=new T[N+CONST_GROWTH ];                                                 
 for(int i=0;i<N;i++) b[i]=A[i];                                                                             
     A = b;                                                                                                   
   head=0;tail=N;
     N=N+CONST_GROWTH ; 
}
template<typename T>unsigned int DynamicQueue<T> ::  size(){
int a = tail- head;
return a;}
template<typename T>void DynamicQueue<T> ::  QInsert(T x){
  if(head!=0 && tail==N) {                                   
      for(int i=0;i<size();i++) A[i]=A[i+head];
      head=0;tail=tail-head;
      }
      if(size()==N){grow();}                                
      A[tail]=x;
      tail=tail+1;
}
template<typename T>bool DynamicQueue<T> :: QDelete(T *x){
if(head==tail){ return 0;}                                 
    
   else{         head=(head+1);
          return 1;
          }
}
