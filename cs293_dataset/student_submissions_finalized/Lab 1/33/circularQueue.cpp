#include<iostream>  // Here is the code for Circular Queue Abstract Data Type .
#include"queue.h"
#include<cmath>
using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty(){ // Is the Queue empty ?
    return ( head==tail ) ;  // When head==tail implies that the circular queue is empty .
}
template <typename T> bool DynamicQueue<T>::isFull(){ // Is the Queue full ?
    return ((head == tail+1)||((head==0)&&(tail==N-1))) ; // According to my convenience , the queue was declared to be full when the num of elements in the array is equal to N-1 .
}
template <typename T> void DynamicQueue<T>::grow(){ // grows the array size to next value .
                                    // grow() function has to be called when the max array size = number of elements in Queue .
    T *New_A ;  // creating a new array named New_A .
    New_A = new T[N]; // of size N .
    New_A = A ;  // copying all the elements of A into New_A .
    delete A ;   // deleting the old array to save memory .
    T *A ;
    A = new T[nextSize()];  // Again creating new array named A whose size equal to N+CONST_GROWTH .
    for(int p=0;p<tail;p++){
        A[p] = New_A[p] ;  // Copying all the elements of New_A from index 0 to index tail as it is into A .
    }
    for(int p=head+CONST_GROWTH;p<nextSize();p++){
        A[p] = New_A[p-CONST_GROWTH] ; // 
    }
    head = head+CONST_GROWTH ; // Updating the index of head .
    N = nextSize(); // Updating the value of N .
    return ;
}
template <typename T> unsigned int DynamicQueue<T>::size(){
    return ((N-head+tail)%N); // size() func gives the current number of elements present in the array .
}
template <typename T> void DynamicQueue<T>::QInsert(T x){ //insert given element x at tail of the queue; grow array size as necessary .
    if(!tail==N){  // First case : when tail != N .
        A[tail] = x ; // element x will get inserted at the last of the array .
        tail++;  // tail gets updated .
        return ;
    }
    else if(isFull()){ // Second case : If the array is full then the grow func was called and the max size gets updated .
        grow();
        A[tail] = x ;  // element x will get inserted at the last of the array .
        tail++;  // tail gets updated .
        return ;
    }
    else{  // Final case : When tail = N but head != 0 .
        T *B ;
        B = new T[N]; // In this case all the elements in the array were moved a unit forward and leave a place at the last .
        B = A ;
        for(int m=head;m<tail;m++){
            A[m-1] = B[m] ;
        }
        head--;
        A[tail] = x ;  // The element x will get inserted at the last place which was created .
        return ;
    }
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x){ // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise .
    if(isEmpty()) return false ; // if it's empty then it returns false .
    else{
        T *New_A ;  // otherwise the first element gets removed .
        New_A = new T[N]; 
        New_A = A ;
        delete A;
        A = new T[N] ;
        for(int l=head+1;l<tail;l++){
            A[l] = New_A[l] ;
        }
        return true ;  // it returns true .
    }
}
