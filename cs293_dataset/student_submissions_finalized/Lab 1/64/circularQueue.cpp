#include <iostream>
using namespace std;
#include "queue.h"
template <typename T> bool DynamicQueue<T>::isEmpty(){
    return(head==tail);                 //queue is empty if head=tail
}
template <typename T> bool DynamicQueue<T>::isFull(){
    return(((head-tail)+N)%N==1);       //queue is full if either (tail=N-1 and head=0) or (head-tail=1)
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
    return((N+tail-head)%N);            //as tail-head can be negative in circular queue so we use modulo function
}
template <typename T> void DynamicQueue<T>::QInsert(T x){
    if(isFull()){                       //if queue is full and tail=N-1 then we grow array size and insert new
        if(tail==N-1){                  //element and increse tail by 1
            grow();
            A[tail]=x;
            tail++;
        }else{                          //if queue is full but tail is not equal to N-1 then we first grow size of
            int temp=N;                 //array and then shifts elments upto tail to the right of N and then shifts
            grow();                     //every element left so that now head is 0 and tail is N-1 but the order of
            for(int i=0; i<tail; i++){  //queue remains same
                A[temp+i]=A[i];
            }
            tail=temp+tail;
            for(int i=0; i<temp-1; i++){
                A[i]=A[head+i];
            }
            head=0;
            tail=temp-1;
            A[tail]=x;
            tail++;
        }
    }
    else if(tail==N-1){                //if queue is not full but tail=N-1 then we check if queue is empty
            if(isEmpty()){             //if queue is empty we make head=tail=0
                head=tail=0;
                A[tail]=x;
                tail++;           
            }else{
                A[tail]=x;             //insert new element at tail and make tail=0
                tail=0;
            }
    }
    else{
            if(isEmpty()){            //if queue is not full and tail is not equal to N-1 then we check if it is empty         //if it is empty we make head=tail=0
                head=tail=0;
            }
            A[tail]=x;                //insert new element at tail and increase tail by 1
            tail++;
    }
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()){                                //to delete we check if queue is empty.
        head=tail=0;                              //if is empty then we make head=tail=0
        return 0;                                 //and return False
    }else{                           //if queue is not empty we store the element at head in variable x and increase
        *x=A[head];                  //head by 1.
        head=(head+1)%N;
        return 1;
    }
}