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
        return(size()==(N-1));   // we will consider the circular queue is full when only one position is empty. 
                             //so if the size of the queue returns N-1 , then the queue is full.
                                  
    }

template <typename T>
    void DynamicQueue<T>::grow(){ // grow the queue to its next size 
        T *Arr;
        Arr = new T[N+CONST_GROWTH];  // creating new array with linearly increased size.
        for(int i=0; i<N-1; i++){      // here we used i<N-1 because we consider the queue full when only one position is left empty.
            Arr[i] = A[(head+i)%N];      // copying queue elements in the new array.
        }
        head=0;  //updating the value of head and tail
        tail=N-1;
        A = Arr;    // changing position pointer of the old array
        N = N+CONST_GROWTH;  // updating the current size of the array.
    }

template <typename T>
    unsigned int DynamicQueue<T>::size(){ // return the current number of elements in the queue
        return ((N+tail-head)%N);  // for circular queue, number of total elements is (size of array+tail-head)
    }

template <typename T>
    void DynamicQueue<T>::QInsert(T x){  // insert given element at tail of the queue; grow array size as necessary
        if(isFull()){   // if the queue is full, grow the size of the array
            grow();
        }
        else if(tail==N-1){  // else if the queue is not full but the last element is at index N-2 then shift the elements one place forward
            int s = size();
            for(int i=head; i<tail; i++){
                A[0] = A[i];
            }
            int prevtail = tail;
            tail = s;  // update the position of tail 
            for(int j=tail; j<prevtail; j++){ // delete the elements from the previous positions. 
                A[j] = NULL;
            }
        }
        A[tail] = x;  // insert the new element at the tail
        head = 0;
        tail= (tail+1)%N;  // again update the position of tail

    } 

template <typename T>
    bool DynamicQueue<T>::QDelete(T *x){ // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
        if(isEmpty()){
            return false;  // returns false if the queue is empty
        }
        *x = A[head];  // place the element present at head in *T
        A[head] = NULL; // delete the element present at head
        head = (head+1)%N;   // update the value of head
        return true;   // return true if successfully done
    }
