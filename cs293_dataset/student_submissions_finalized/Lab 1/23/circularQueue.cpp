#include "queue.h"
#include <iostream>
using namespace std;
#include <cmath>
//i have followed an algorithm in which head equals to tail leads to ambiguity whether full or empty
template<typename T> unsigned int DynamicQueue<T>::size(){int c=0;
                                                          if(tail>head)
                                                           return 
                                                           tail-head;
                                                          if(head>tail)
                                                            return 
                                                            N-(head-tail);           
                                                          /*if(head==tail){           //this can have a major flaw if all the members in the queue are zeroes;
                                                           for(int i=0;i<N;i++){      //but this is kinda time taking too this made the compilation took too much time 
                                                                  if(A[i]==0){c++;}   //and the compilation got killed.
                                                                  }
                                                           if(c==N-1)return 0;
                                                           else return N;};*/
                                                           if(head==tail){            //so this is the thing which i had obtained it from google which gives the size 
                                                                return sizeof(A)/sizeof(A[0]);};//directly
                                                           }
template<typename T> bool DynamicQueue<T>::isEmpty(){return  
                                                           size()==0;}
template<typename T> bool DynamicQueue<T>::isFull(){return 
                                                           size()==N;}
template<typename T> void DynamicQueue<T>::grow(){
                          if(isFull())                                      //i have changed it a bit from linear in such a way that when head is in between then in 
                          {                                                 //in the new array the head goes to 0 and tail goes to N
                                     T *B;
                                     B=new T[N];
                                     B=A;      
                                     A=new T[N+CONST_GROWTH];
                                     for(int i=head;i<N;i++){
                                                   A[i-head]=B[i];};
                                     for(int i=0;i<head;i++){
                                                   A[N-head+i]=B[i];};
                                     N=nextSize();}
                           else return;};

template<typename T> void DynamicQueue<T>::QInsert(T x){

                                  if(isFull()){
                                         head=0;
                                         tail=N;
                                         grow();
                                         A[tail]=x;
                                         tail++;
                                         }
                                  if((head<tail||head==tail)&&(tail<N)){
                                           A[tail]=x;
                                           tail++;};
                                      
                                   if((head!=0)&&(tail==N))//if tail==N and we are inserting a new element we cant insert it at N obviously so in order to add the 
                                      { tail=0;            //head shouldn't be 0 so tail is modified to 0
                                        A[tail]=x;
                                        tail++;  
                                          };
                                   if((tail<head)||(tail!=0)){
                                         if(head-tail==1){
                                          A[tail]=x;
                                          tail++;
                                               }  
                                               }; }         
                                

template<typename T> bool DynamicQueue<T>::QDelete(T *x){
                                 if(head==tail) return false;
                                 else{
                                 if(head<N){
                                    x=&A[head];
                                    A[head]=0;
                                    head++;
                                        }
                                 if(head==N){  //i have deleted this in a circular way too
                                    head=0;
                                    x=&A[head];
                                    A[head]=0;
                                    head++;
                                         }
                                 return true;
                                  }; 
                                   };


