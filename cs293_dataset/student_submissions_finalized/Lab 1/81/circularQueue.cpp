#include <iostream>
#include"queue.h"
using namespace std;
//*IMPORTANT ASSUMPTION:
//I AM USING ONLY N-1 SPACE FOR QUEUE FOR DISTINCTION B/W EMPTY AND COMPLETED QUEUE*/
template <typename T> bool DynamicQueue<T>::isEmpty(){
// if head and tail are same then there are no elements
    if(head==tail){ return true;}
    else return false;
}
template <typename T> bool DynamicQueue<T>::isFull(){
// As tail reaches behind the head circle is full
    if(head==tail+1){return true;}
    else return false;
}
template <typename T> void DynamicQueue<T>::grow(){
// grow the queue by making a new array and copying these elements in them
    T *S;
    S = new T[this->nextSize()];
    for(int i=0;i<tail;i++){S[i]=A[i];}
// make space between tail and head
    for(int i=head;i<N;i++){S[i+CONST_GROWTH]=A[i];}
    head=head+CONST_GROWTH;
    A=S;N=this->nextSize();
}
template <typename T> unsigned int DynamicQueue<T>::size(){
//return the size
return((N-head+tail)%N);

}
template <typename T> void DynamicQueue<T>::QInsert(T x){
// if its full grow or else but it at the tail
    if(this->isFull()){this->grow();A[tail]=x;tail=(tail+1)%N;}
    else {A[tail]=x;tail=(tail+1)%N;} 
 }
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
// just delete the head
    if(this->isEmpty()){return false;}
    else {head=(head+1)%N;return true;}
 }
