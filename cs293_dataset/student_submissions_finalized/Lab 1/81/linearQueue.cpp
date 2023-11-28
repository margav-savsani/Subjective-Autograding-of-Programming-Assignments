#include <iostream>
#include"queue.h"
using namespace std;
//*IMPORTANT ASSUMPTION:
//I AM USING ONLY N-1 SPACE FOR QUEUE FOR REDUCING IF CONDITIONS*//
template <typename T> bool DynamicQueue<T>::isEmpty(){
// if head and tail are same then there are no elements
    if(head==tail){ return true;}
    else return false;
}
template <typename T> bool DynamicQueue<T>::isFull(){
// As tail reaches end of an array it signs that it is full
    if(tail==N-1){return true;}
    else return false;
}
template <typename T> void DynamicQueue<T>::grow(){
// if place is left move the array movebackwards
if(head!=0){
for(int i=head;i<N;i++){A[i-head]=A[i];}
tail=tail-head;
head=0;
}
// grow the queue by making a new array and copying these elements in them
else{
    T *S;
    S = new T[this->nextSize()];
    for(int i=head;i<N-1;i++){S[i]=A[i];}
    A=S;N=this->nextSize();}
}
template <typename T> unsigned int DynamicQueue<T>::size(){
//return the size
return (tail-head);
}
template <typename T> void DynamicQueue<T>::QInsert(T x){
// if its full grow or else but it at the tail
    if(this->isFull()){this->grow();A[tail]=x;tail++;}
    else {A[tail]=x;tail++;} 
 }
 template <typename T> bool DynamicQueue<T>::QDelete(T *x){
 // just delete the head
    if(this->isEmpty()){return false;}
    else {head++;return true;}
 }
