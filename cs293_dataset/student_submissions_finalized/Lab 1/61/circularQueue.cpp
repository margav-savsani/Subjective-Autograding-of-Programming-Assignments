#include<iostream>
#include"queue.h"
using namespace std;
  
  template<typename T> bool DynamicQueue<T>::isEmpty(){// is the queue empty?
    if(head==tail){
        return true;// if head and tail point to the same index then the list is empty
    }
    return false;
   
  } 
  template<typename T> bool DynamicQueue<T>::isFull(){ // is the queue full?
     if(size()==N-1){// if the size of the queue becomes N-1 then it is full
        return true;//"N" cannot be used here as that would imply head=tail, a condition which
    }               //already being used
    return false;
  }
  template<typename T> void DynamicQueue<T>::grow(){ // grow the queue to its next size 
    if(isFull()){
        T* B=new T[nextSize()]; //A temporary array B with the incremented size is created
        int i=head,j=0;
        while(i%N!=tail && j<N-1){// The elements of the old array are copied into the new array starting from
            B[j]=A[i%N];//the 0th index
            j++;
            i++;
        }
        tail=N-1;//tail is reassigned
        head=0;//head is reassigned
        N=nextSize();//The size of the array is modified to the new size
        A=B;
    }
  }
  template<typename T> unsigned int DynamicQueue<T>:: size(){// return the current number of elements in the queue
    return (N+tail-head)%N;
  }; 
  template<typename T> void DynamicQueue<T>::QInsert(T x){ // insert given element at tail of the queue
    if(isFull()){
        grow(); //If the queue is full then the size of the array is increased using the grow()
    }
    A[tail]=x;
    tail=(tail+1)%N;// tail is reassigned
  }
  template<typename T> bool DynamicQueue<T>:: QDelete(T *x){// delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
    if(isEmpty()){
        return false; //checks if queue is empty
    }
    *x=A[head];
    head=(head+1)%N;
    return true;
  }

