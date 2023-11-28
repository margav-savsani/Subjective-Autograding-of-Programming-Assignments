#include<iostream>
#include "queue.h"
using namespace std;

template <typename T> 

    bool DynamicQueue<T>::isEmpty(){  // is the queue empty?
        return(tail==head);    //checks if tail is equal to head. if the index where next element will be inserted is equal  
                               // to the index from where the first element is to be deleted, then it must be empty. 
    } 

template <typename T>
    bool DynamicQueue<T>::isFull(){ // is the queue full?
        return(size()==N);   // if head is 0 means elements are starting from index 0 and 
                                 //if tail is N means the next element will be stored in index N.
                                 // which implies queue is full. 
    }

template <typename T>
    void DynamicQueue<T>::grow(){ // grow the queue to its next size 
        T*  Arr;
        Arr = new T[N+CONST_GROWTH];  // creating new array with linearly increased size.
        for(int i=0; i<N; i++){
            Arr[i] = A[i];      // copying queue elements in the new array.
        }
        delete A;
        head = 0;
        tail = N;
        A = Arr;    // changing position pointer of the old array
        N = N+CONST_GROWTH;  // updating the current size of the array.
    }

template <typename T>
    unsigned int DynamicQueue<T>::size(){ // return the current number of elements in the queue
        return (tail-head);  // for linear queue, number of total elements is (tail-head)
    }

template <typename T>
    void DynamicQueue<T>::QInsert(T x){  // insert given element at tail of the queue; grow array size as necessary
        if(isFull()){   // if the queue is full, grow the size of the array
            grow();
        }
        else if(tail==N && head!=0){  // else if the queue is not full but the last element is at index N-1 then shift the elements one place forward
            int s = size();
            for(int i=0; i<size(); i++){
                A[i] = A[head+i];
            }
            int prevtail = tail;
            head=0;
            tail = s;  // update the position of tail
            
        }
        A[tail] = x;  // insert the new element at the tail
        tail++;  // again update the position of tail

        } 

template <typename T>

    bool DynamicQueue<T>::QDelete(T *x){ // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
        if(isEmpty()){
            return false;  // returns false if the queue is empty
        }
        *x = A[head];  // place the element present at head in *T
        A[head] = NULL; // delete the element present at head
        head++;   // update the value of head
        return true;   // return true if successfully done
    }