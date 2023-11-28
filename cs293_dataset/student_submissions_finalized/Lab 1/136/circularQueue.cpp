#include <iostream>
using namespace std;
template <typename T>
bool DynamicQueue<T>::isEmpty(){
//if head == tail then the array is empty
   return head==tail;
}

template <typename T>
bool DynamicQueue<T>::isFull(){
//the function QInsert is implemented in such a way that if the array is full after inserting the tail is set to -1
   return tail==-1;
}

template <typename T>
void DynamicQueue<T>::grow(){
//creating a temporary array and copying the array into this, starting from index 0
    T* B=new T[N];
    unsigned int j=0;
    for(int i=head;i<N;i++){
    	B[j]=A[i];
    	j++;
    }
    for(int i=0;i<head;i++){
    	B[j]=A[i];
    	j++;
    }
//resetting head and tail to 0 and N
    head=0;
    tail=N;
//deleting the array and creating a new one of nextsize
    N=nextSize();
    A = new T[N];
//copying the elements from temporary to A
    for(int i=0;i<tail;i++){
        A[i]=B[i];
    }
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
//if tail is -1 then the size is N else it is as per the given expression
    if(tail==-1){
        return N;
    }
    return (N-head+tail)%N;
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
//if the array is full then grow the array
    if(isFull()){
        grow();
    }
    A[tail]=x;
    tail=(tail+1)%N;//change tail
    if(tail==head){
    	tail=-1;//if array is full after insertion set tail to -1
    }
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *p){
   if(isEmpty()){
   	return false;
   }    
   *p=A[head];
   head=(head+1)%N;
   if(tail==-1){
        tail=head-1;
   }
   return true;
}