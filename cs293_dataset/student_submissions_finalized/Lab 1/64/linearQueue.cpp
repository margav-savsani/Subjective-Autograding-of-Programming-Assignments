#include <iostream>
using namespace std;
#include "queue.h"
template <typename T> bool DynamicQueue<T>::isEmpty(){
    return(tail==head);                                //queue is empty only when tail=head
}
template <typename T> bool DynamicQueue<T>::isFull(){
    return(tail-head==N);                              //the queue is full only when head = 0 and tail=N so tail-head=N
}
template <typename T> void DynamicQueue<T>::grow(){
    int temp=N;                                        //growing the array by creating a new array, copying all elements
    N=nextSize();                                      //from old array to new array
    T * B = new T[N];
    for (int i = 0; i < temp; i++) 
        B[i] = A[i];
    delete [] A;
    A = B;                                    
}
template <typename T> unsigned int DynamicQueue<T>::size(){
    return(tail-head);                                 //number of elements in the queue equals head-tail
}
template <typename T> void DynamicQueue<T>::QInsert(T x){
    if(isFull()){                                      //if queue is full we grow the array
        grow();
    }                          
    else if(tail==N){                    //if queue is not full but tail=N then we shift every element of array
        int temp=size();                 //backwards so that now head=0 and tail = size of array.
        for(int j=0;j<temp;j++){
            A[j]=A[head+j];
        }
        head=0;
        tail=temp;
    }
    else{                          //if queue is not full then we check if it is empty. If queue is empty then we
        if(isEmpty()){             //make head=tail=0
            head=tail=0;
        }
    }
    A[tail]=x;                     //finally we insert new element at tail and update the tail.
    tail++;
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()){                 //to delete first we check if queue is empty. If it is empty we return False,
        if(head!=0){               //otherwise we store element at head in variable x and increase head by 1 and
            head=tail=0;           //return True.
        }
        return 0;
    }else{
        *x=A[head];
        head++;
        return 1;      
    }
}