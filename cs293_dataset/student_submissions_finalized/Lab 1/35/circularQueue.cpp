#include<iostream>
#include "queue.h"
//#include<cassert>
using namespace std;

template<typename T> bool DynamicQueue<T>::isEmpty(){
//for the queue to be empty we need the head to coincide with tail
    if(head == tail) return true;
    else return false;
}

template<typename T> bool DynamicQueue<T>::isFull(){
//lets leave one place empty cuz otherwise the condition for isEmpty and isFull would be same
    if(head == (tail+1)%N ) return true;
    else return false;
}

template<typename T> void DynamicQueue<T>::grow(){
//since we cannot increase the size of an array once it was defined,
//We just need to define a new array and copy paste the elements
    T *B;
    B = new T[this->nextSize()];
    /*assert(tail>=0);
    assert(tail<N);
    assert(head>=0);
    assert(head<N);*/
    if(tail < head){
        for(int i=head;i<N;i++){
            B[i] = A[i];
        }
        for(int i=0;i<tail;i++){
            B[CONST_GROWTH+i] = A[i];
        }
        tail = tail + CONST_GROWTH;
        A = B;
    }
    else{
        for(int i=head;i<tail;i++){
            B[i] = A[i];
        }
        A = B;
    }
// I have left the elements from heads to the earlier right end to stay in their corresponding positions and
// the elements in the left side to the continuation of earlier right end
// Now the new tail is at old position + N
// Now change N value        
    N = this->nextSize();
    //assert(tail > head);
}

template<typename T> unsigned int DynamicQueue<T>::size(){
//size is simply the difference of tail and head modulus N
    //assert((tail-head)%N > 0);
    return (tail-head)%N;
}

template<typename T> void DynamicQueue<T>::QInsert(T x){
// First if the queue is not full then we can directly insert the element at the tail
    if(!this->isFull()){
        /*assert(tail>=0);
        assert(tail<N);*/
        A[tail] = x;
        tail = (tail+1)%N;
    }
// otherwise we need to use grow function first and do the usual    
    else{
        this->grow();
        /*assert(tail>=0);
        assert(tail<N);*/
        A[tail] = x;
        tail = tail+1;
    }
    return;
}

template<typename T> bool DynamicQueue<T>::QDelete(T *x){
//if the queue isn't empty we can simply change the head
    if(!this->isEmpty()){
        //A[head]=NULL;
        head = (head+1)%N;
        return true;
    }
    else return false;
}