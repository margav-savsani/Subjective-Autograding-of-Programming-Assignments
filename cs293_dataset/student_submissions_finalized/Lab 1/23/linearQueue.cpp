#include "queue.h"
#include <iostream>
using namespace std;
#include <cmath>
template<typename T> unsigned int DynamicQueue<T>::size(){return  
                                                            tail-head; 
                                                                   };
template<typename T> bool DynamicQueue<T>::isEmpty(){return 
                                                            head==tail;  //from lectures
                                                            }
template<typename T> bool DynamicQueue<T>::isFull(){return  
                                                           tail-head==N;
                                                           }
template<typename T> void DynamicQueue<T>::grow(){
                                               if(tail-head==N)
                                               {
                                                  T *B;
                                                  B=new T[N];
                                                  B=A;
                                                  A=new T[N+CONST_GROWTH];//increse the length of the array
                                                  for(int i=0;i<N;i++){
                                                              A[i]=B[i];};//copying the elements
                                                  N=nextSize();}//initializing the value of N to the next value
                                                  else 
                                                        return;
                                                     };

template<typename T> void DynamicQueue<T>::QInsert(T x){
                                                  if(isFull()){//checking the space in the queue
                                                  grow();}
                                                  A[tail]=x;
                                                  tail++;//incrementing the tail
                                                  }

template<typename T> bool DynamicQueue<T>::QDelete(T *x){
                                 
                                  
                                if(head==tail) return
                                                   false;
                                 else{
                                 *x=A[head];//stored the value of which have to be deleted
                                 A[head]=0;//not sure of how to delete so assigned the value to the default value 
                                 return 
                                        true; 
                                           }; 
                                               };/*210050160_vanapalli_raja_gopal*/


