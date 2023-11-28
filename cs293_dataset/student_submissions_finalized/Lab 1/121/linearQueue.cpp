#include"queue.h"
#include<iostream>
#include<cassert>
using namespace std;

template<class T> bool DynamicQueue<T>::isEmpty(){
    if (tail==head) return true;  //if tail and head are at the same position it means queue is empty
    else return false;   //else, tail is behind (greater than) the head and so the queue is non empty
}
template<class T> bool DynamicQueue<T>::isFull(){
    if (tail < N) return false;  //if the tail is equal to N then the max limit of array is reached and further
                                 // elements cannot be inserted, we need to appropriately grow the array/ adjust
                                 // the first element of array
    else return true;
}
template<class T> void DynamicQueue<T>::grow(){
    if (head > 0){   //head is the max number of spaces we may gain by shifting elements, so if that  is more than 0,we can shift
        for(int k=0; k<(tail-head); k++){  //copying the values from old to new array
            A[k] = A[k+head];
        }
        tail = tail-head;     //new value of tail
        head=0;    //new headd is zero
        
    }
    
    else{     //if shifting isn't possible, we extend the array
        N = nextSize();
        T* b = new T[N];   //new array with required size
        for (int i=head; i < tail; i++){     //copying the values from old to new array
            b[i] = A[i];
        }
        delete []A;    //deleting the old array 
        A = b;    //ptr A now points to new array 
        b = NULL;    //so that b doesn't cause any problems from here on
    }
    
}
template<class T> unsigned int DynamicQueue<T>::size(){
    return (tail-head);   //current size of queue is 
}
template<class T> void DynamicQueue<T>::QInsert(T x){
    if (isFull()) grow();     //if required, growing queue
    A[tail] = x;     //storing x in last position of queue
    tail++;      //increasing tail by 1
}
template<class T> bool DynamicQueue<T>::QDelete(T* x){
    if(isEmpty()) return false;
    *x = A[head];     //storing value of front element in *x
    head++;     //increasing head by 1, which simulates deletion of first element and pushing second element as first
    assert(head<=tail);      //post condition
    return true;
}