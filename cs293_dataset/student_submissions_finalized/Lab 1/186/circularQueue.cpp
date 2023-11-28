#include <iostream>
#include "queue.h"

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    if(head == tail) return true;          // queue is empty when head == tail
    else return false;
}

template <typename T>
bool DynamicQueue<T>::isFull(){      
    if(size() == N) return true;           //Circular queue is full when size is N
    else return false;
}

template <typename T>
void DynamicQueue<T>::grow(){
    if(isFull()){
        T *A1;
        A1 = new T[nextSize()];             //A1 is a temporary array with larger size
        int temp = head, oldsize = size();
        for(int i = 0; i < size(); i++){    //copying elements from old array(A)into new one(A1)
            A1[i] = A[temp%N];              //along with rearranging them (starting from index 0)
            temp++;
        }
        N = nextSize();                     //incrementing N to nextSize
        A = A1;                             //copying A1 to A
        tail = oldsize;                 
        head = 0;
    }
}

template <typename T>
unsigned int DynamicQueue<T>::size(){      //returns current size of queue
    return (tail-head);           
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()){         //growing the array if the queue is full
        grow();
    }
    A[tail%N] = x;        //inserting new element at tail
    tail++;               //incrementing tail
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return false;
    *x = A[head%N];
    A[head%N] = 0;         // deleting from the front(at head)
    head++;                // incrementing head
    return true;
}
