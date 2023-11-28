#include<iostream>
using namespace std;
#include "queue.h"
template<typename T> bool DynamicQueue<T> ::isEmpty(){
    return !tail;
}
//if queue is empty then tail is zero so !tail will be 1 so the return value would be true
// and if queue is not empty then using similar logic the return value would be false
// this is similar to linearQueue
template<typename T>bool DynamicQueue <T> :: isFull(){
    if(head<tail && N==tail-head){
        return true;
    }
    if (head>tail && N==head-tail){
        return true;
    }
    return false;

}
// if head is less than tail then it is similar to linearQueue if head is greater than tail ie the 
//queue is filled 
// from a different direction so head -tail is used
template<typename T> void DynamicQueue<T> ::grow(){
  T*B;
  B= new int [INIT_SIZE];
  B=A;
  return ;
}
// this is similar to linearQueue we define a new array and copy the old elements 
template<typename T> unsigned int DynamicQueue<T>::size(){

  if(head>tail){
    return N-head+tail;
  }
return tail-head;    
}
// if head is less than tail then tail-head is returned as the size otherwise the 
// return value is changed to N-head+tail which is taking into account the circular nature of the queue
template<typename T> bool DynamicQueue<T> ::QDelete(T *x){
  
  if(head==tail){
    return false;
  }
  *x=A[head];
  if(head<tail){
  head=head+1;
  }
  if(head==N-1){
    head=0;
  }
  if(head>tail && head!=N-1){
    head=head+1;
  }
  N=N-1;
  return true;
}
// for circular Queue this function is really different , here we got there cases if head =tail 
// the array is empty and return false,if head<tail then it is same as liear Queue
// if head >tail this is where the circular nature of the comes in to play
// if head=N-1 then nead is changed to 0, in other case it is incresed by one
// and as usual N is decreased
template<typename T> void DynamicQueue<T> :: QInsert( T x){
  int a;
  if(head<=tail){
    a=tail-head;
  }
  if(a==N)
if(a!=N && N==tail){
    A[0]=x;
}
else{
    A[tail]=x;
}
N=N+1;
tail=tail+1;
return ;
}
//here we find the position to add the element 