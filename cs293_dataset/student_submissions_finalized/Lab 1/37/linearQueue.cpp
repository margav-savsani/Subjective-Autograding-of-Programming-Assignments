#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#define CONST_GROWTH 1000
#include "queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty(){

    return(tail == head );
    
}

template <typename T> bool DynamicQueue<T>::isFull(){

    return(tail-head  == N );
    
}

template <typename T> void DynamicQueue<T>::grow(){
    T* b;
    b = new T[this->nextSize()]; //creating an array with increased size
    int c = tail-head;
    for( int i=0 ; i< c ; i++ ){  //copying elements from original array to larger array
            b[i]= A[((head+i)%N)];
        }
    tail = tail-head;
    head=0;
    N= this->nextSize();
    delete[] A;
    A = b;
    
}

template <typename T> unsigned int  DynamicQueue<T>::size(){

    return tail-head ;
    
}

template <typename T> void DynamicQueue<T>::QInsert(T x){

    if(this->isFull()){
        this->grow();   //when the queue is full we need to increase its size
        A[tail]=x;
        tail++;
        
    
    }
    
    else if(tail!=N){
        A[tail]=x;
        tail++;
        
    }
    else{    //case where queue is not full but tail=N
        for(int i = 0 ; i <tail-head ; i++ ){
            A[i]=A[head+i];    //rearranging elements so that they start from index=0
        }
        tail=tail-head;
        head=0;
        A[tail]=x;
        tail++;
    }    
    
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){

    if(tail==head) return 0;
    *x=A[head];
    head++;

    
    return 1;

}