#include <iostream>
#include "queue.h"
using namespace std;

template<typename T>
bool DynamicQueue<T>::isEmpty(){    //returns true if queue is empty else false
    return head==tail;
}

template<typename T>
unsigned int DynamicQueue<T>::size(){//returns the size of a queue
    return tail-head;
}

template<typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()){                   //if queue is full we will increase the size
        grow();
    }
    else if(tail==N){               //If the tail reaches the end but the queue is not full yet we will shift the queue backwards
        int k=size();
        tail=0;
        while(k--){
            A[tail]=A[head];
            head++;
            tail++;
        }
        head=0;                     //head will be at 0 after rearrangement
    }

    A[tail]=x;                      //adding the element
    tail++;
}

template<typename T>                
bool DynamicQueue<T>::isFull(){ 
    return ((tail==N)&&(head==0));
}

template<typename T>
void DynamicQueue<T>::grow(){
    N=nextSize();               //updating N
    T* B=new T[N];              //creating a new array of Ts
    int k=size();               
    for(int i=0;i<k;i++){       //copying the elements in A to B 
        B[i]=A[head];
        head++;
    }                           //where ever A's head may be B's head will be at the start
    head=0;
    tail=k;
    delete(A);                  //deleting the space allocated to A
    A=B;                        //updating A to B
}

template<typename T>
bool DynamicQueue<T>::QDelete(T* x){
    if(isEmpty()){
        return false;           //returning false for an empty queue
    }
    *x=A[head];                 //storing the value at *x
    head++;                     //updating head
    return true;
}