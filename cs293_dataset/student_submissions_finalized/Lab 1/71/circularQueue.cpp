#include<iostream>
#include"queue.h"
using namespace std;

template<typename T> bool DynamicQueue<T>:: isEmpty(){
    if(size()==0) return true;
    else return false;
}
template<typename T> bool DynamicQueue<T>:: isFull(){
    if(size()==N-1) return true;    //full size is considerd to be N-1 because if we consider full size as N then head will be same as tail
    else return false;              // in which case it will be difficult to differntiate empty situation and full situation
}
template<typename T> unsigned int DynamicQueue<T>:: size(){
    //there is possibility of position of tail on left of head so we need different algorithm for both

    if(tail>=head) return tail-head;    //if tail is on left of head tail-head will return size
    else return N+tail-head;            //else tail-0 will give size from index 0 to tail-1 and N-head will give size of remaining part of 
                                        // queue from head to index N-1
}
template<typename T> void DynamicQueue<T>:: grow(){
    T *B=new T[nextSize()]; //creating a new array of larger size later to be assigned to the original array
    for(int i=0; i<size(); i++){
        B[i]=A[(head+i)%N];     //copying elements from A to B such that head will be at index 0 and next element of queue to be assigned
    }                           // at next index and continue further 
    //after copying head and tail will change
    head=0;
    tail=size();
    N=nextSize();
    A=B;        //assigning new copied and larger array to the original array
}
template<typename T> void DynamicQueue<T>:: QInsert(T x){
    if(isFull()) grow();
    A[tail]=x;           //assigning new element at the tail
    tail=(tail+1)%N;    //incrementing tail circularly so that if tail=N it will converted to tail=0 making a circular queue
}
template<typename T> bool DynamicQueue<T>:: QDelete(T *x){
    if(isEmpty()) return false;
    else{
        *x=A[head];         //assigning head element to pointer x
        head=(head+1)%N;    //incrementing head circulary so that if head=N it will converted to head=0 making a circular queue
        return true;
    }
}