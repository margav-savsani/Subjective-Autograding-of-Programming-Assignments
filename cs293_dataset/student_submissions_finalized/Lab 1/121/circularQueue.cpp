#include"queue.h"
#include<iostream>
#include<cassert>
using namespace std;

template<class T> bool DynamicQueue<T>::isEmpty(){
    return ((tail%N) == (head%N));    //if head and tail are same, queue is empty
}
template<class T> bool DynamicQueue<T>::isFull(){
    return (((tail+1)%N) == (head%N));     //if tail is just behind head (in mod N value circle), queue is full
}
template<class T> void DynamicQueue<T>::grow(){
    T*b = new T[nextSize()];     //new queue with larger size
    for(int i=0; i<N; i++){      //copying the values
        b[i]= A[(i+head)%N];
    }
    delete []A;     //deleting the old array
    tail=size();     //new value of tail
    head=0;         //new value of head
    A = b;          //A is now new array
    b = NULL;       //just so that b doesn't cause any problems from here on
    N = nextSize();   //increasing n
}
template<class T> unsigned int DynamicQueue<T>::size(){
    return ((N-head+tail)%N);      //expression is self explanatory...
}
template<class T> void DynamicQueue<T>::QInsert(T x){
    if (isFull()) grow();     //if queue is full, grow it
    A[tail] = x;     //inserting the element
    tail = (tail+1)%N;          //shifting the tail
    
}
template<class T> bool DynamicQueue<T>::QDelete(T* x){
    if(isEmpty()) return false;     //can't delete from empty queue
    *x = A[head];       //storing removed element in *x
    head= (head+1)%N;   //shifting the head
    return true;
}
