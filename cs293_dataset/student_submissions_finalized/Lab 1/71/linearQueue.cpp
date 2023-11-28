#include<iostream>
#include<cassert>
#include"queue.h"
using namespace std;

template<typename T> bool DynamicQueue<T>::isEmpty(){
    if(size()==0) return true;  
    else return false;
}

template<typename T> bool DynamicQueue<T>::isFull(){
    if(size()==N) return true;
    else return false;
}

template<typename T> unsigned int DynamicQueue<T>::size(){
    return tail-head;   //as tail will always be on right side of head or equal to head ,size of the queue is tail-head
}

template<typename T> void DynamicQueue<T>::grow(){
    // grow command will be executed only if queue is full that means head=0 and tail=N

    T *B=new T[nextSize()]; //  creating a new queue of larger size which will be assigned to original queue after
                            //  copying all the elements to the new one
    for(int i=0; i<tail; i++){
        B[i]=A[i];  //copying element
    }
    N=nextSize();   //changing the current size of array
    A=B;    //assiging the new queue to the original one 
}

template<typename T> void DynamicQueue<T>::QInsert(T x){
    if(tail==N){
        if(isFull()) grow();    //if queue is full we need to grow the queue so that a new element can be inserted
        else{   //there is possibility that tail might be N but queue is not full, in that case we have to shift all elements to left
            int k=size();
            for(int i=0; i<k; i++){
                A[i]=A[N-k+i];
            }
            //after shifting head and tail of queue will change
            head=0; 
            tail=k;
        }
    }
    //assignining new element at the tail and increment of tail by 1 
    A[tail]=x;  
    tail+=1;
}

template<typename T> bool DynamicQueue<T>::QDelete(T *x){ 
    if(isEmpty()) return false;
    else {
        *x=A[head]; //assigning head element to pointer x
        head+=1;    //increment of head by 1
        return true;
    }
}