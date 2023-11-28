
#include<iostream>
using namespace std;
#include "queue.h"



template<typename T> bool DynamicQueue<T> ::isEmpty(){
  return !tail;
}
//if queue is empty then tail is zero so !tail will be 1 so the return value would be true
// and  if queue  is not empty  then using similar logic the  return  value would be false
template<typename T>bool DynamicQueue <T> :: isFull(){
  if(N==tail-head){
    return true;
  }
  return false;
}
// if difference in tail and head is equal to N then the queue is empty
template<typename T> unsigned int DynamicQueue<T>::size(){
return tail-head;    
}
//since queue is linear their difference just gives the size of the array 
template<typename T> void DynamicQueue<T> ::grow(){
  T*B;
  int s=nextSize();
  B= new T [s];
  N=s;
  B=A;  
  return ;
}
// in cpp we cannot directly add memory to an array so what we do here is we create another 
// array  with  more  space and copy the elements of the first array in to the second array

template<typename T> bool DynamicQueue<T> ::QDelete(T *x){
  
  if(head==tail){
    return false;
  }
  *x=A[head];
  head=head+1;
  N=N-1;
  return true;
}
// we  cannot  directly  delete the first  element in the array 
//since we deleted the element the size of the array 
//ie N should be decreased 
// or else the program will not work as we expect
// the head alsoo should be increased
template<typename T> void DynamicQueue<T> :: QInsert( T x){
  
  if(tail==N){
    grow();
  }
A[tail]=x;
N=N+1;
tail=tail+1;

}
//we check whether the queue is empty are full , if full array is grown and then inseted otherwise
// directly inserted and the value of N is increased and tail is changed accordingly

