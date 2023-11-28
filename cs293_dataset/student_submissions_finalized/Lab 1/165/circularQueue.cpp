#include "queue.h"
#include<iostream>
using namespace std;
template<typename T>
bool DynamicQueue<T>::isEmpty(){

    return(size() == 0);
}
template<typename T>
bool DynamicQueue<T>::isFull(){

    return(size() == N);
}

template<typename T>
void DynamicQueue<T>::grow(){
    T* B;
    
    B = new T[nextSize()];
    
    for(int i=0; i<=N-1 ; i++){
        B[i] = A[(head+i)%N];//copying elements into a new array of grown size
    }
    head = 0;
    tail = N;
    N = nextSize();
    delete(A);
    A = B;
}

template<typename T>
unsigned int DynamicQueue<T>::size(){
    
    return(tail - head );//size = tail - head 

}

template<typename T>
void DynamicQueue<T>::QInsert(T x){// insert given element at tail of the queue; grow array size as necessary
    

    if (isFull()){
        grow();
    }
     
    A[tail%N] = x; //set value of new tail

    tail = tail + 1;//position of tail goes back by 1 and if it goes to N, it comes back to 0
    
}

template<typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if (isEmpty())
        return false;
    *x = A[head%N];//store current value of head
    head = (head + 1);//head goes back by 1
    
    return true;
}
// delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise

