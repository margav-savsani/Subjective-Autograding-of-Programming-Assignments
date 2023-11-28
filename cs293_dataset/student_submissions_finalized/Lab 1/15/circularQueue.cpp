#include<iostream>
#include "queue.h"
using namespace std;
template<typename T>
bool DynamicQueue<T>::isEmpty(){        //returns true if queue is empty else returns false
    return head==tail;
}

template<typename T>
unsigned int DynamicQueue<T>::size(){   
    return tail-head;             //here head and tail are not indexes but their mod N are indexes
}

template<typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()){                       //Increasing the size if the queue is full
        grow();
    }
    A[tail%N]=x;                        //we do not loop we use tail%N as index
    tail=(tail+1);                    //We just increase the tail
}

template<typename T>
bool DynamicQueue<T>::isFull(){         //I can fill the array up to N which is the full size
    return (size()==N);
}

template<typename T>
void DynamicQueue<T>::grow(){
    T* B=new T[N+CONST_GROWTH];             //making a new array of T of increased size
    for(int i=0;i<size();i++){          //copying the elements of A in B
        B[i]=A[(head+i)%N];            
    }

    head=0;
    tail=N;                           //now it is arranged with head starting from 0
    N=N+CONST_GROWTH;                      //updating N
    delete(A);                          //deleting the space allocated to A
    A=B;
}

template<typename T>
bool DynamicQueue<T>::QDelete(T* x){
    if(isEmpty()){                      //returning false if the queue is empty
        return false;
    }
    *x=A[head%N];                         //storing the value at position pointed by x
    head=(head+1);                    //updating head
    return true;                        
}