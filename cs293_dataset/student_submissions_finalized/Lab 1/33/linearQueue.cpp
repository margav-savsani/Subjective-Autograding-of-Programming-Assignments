#include<iostream>  // Here is the code for linear Queue Abstract Data Type .
#include"queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty(){  // Is the array empty ?
    return head==tail ;  // The Queue will be empty when head becomes equal to tail .
}
template <typename T> bool DynamicQueue<T>::isFull(){  // Is the array Full ?
    return (head==0&&tail==N) ; // The Queue will be full when both the head = 0 and tail = N at a time .
}
template <typename T> void DynamicQueue<T>::grow(){ // grows the array size to next value .
                    // grow() function has to be called when the max array size = number of elements in Queue .
    T *New_A ;   // This func creates new array whose size equal to N+CONST_GROWTH and copies the same elements from the old array .
    New_A = new T[N]; 
    New_A = A ;  // Old array elements will be in New_A array now .
    delete A ;
    N = nextSize() ;
    A = new T[nextSize()]; // New array of max size equal to N+CONST_GROWTH .
    for(int p=0;p<N-CONST_GROWTH;p++){
        A[p] = New_A[p] ; // Copying the elements of the old array .
    }
    return ;
}
template <typename T> unsigned int DynamicQueue<T>::size(){ 
    return tail-head ;  // size() func gives the current number of elements present in the array .
}
template <typename T> void DynamicQueue<T>::QInsert(T x){ //insert given element x at tail of the queue; grow array size as necessary .
    if(!tail==N){  // First case : when tail != N .
        A[tail] = x ; // The element x will be inserted at the last of the array .
        tail++; // tail value gets updated .
        return ;
    }
    else if(isFull()){ // Second case : If the array is full then the grow() func is called and the max size gets updated .
        grow();
        A[tail] = x ; // The element x will be inserted at the last of the array .
        tail++;  // tail value gets updated .
        return ;
    }
    else{   // Final case : When tail = N but head != 0 .
        T *B ; 
        B = new T[N]; // In this case all the elements in the array were moved a unit forward and leave a place at the last .
        B = A ;
        delete A ;
        A = new T[N] ;
        for(int m=head;m<tail;m++){
            A[m-1] = B[m] ;
        }
        head--;
        A[tail] = x ; // The element x will get inserted at the last place which was created .
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
