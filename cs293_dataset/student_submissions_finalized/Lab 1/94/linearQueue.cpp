#include<iostream>
#include"queue.h"
template<typename T>bool DynamicQueue<T> :: isEmpty(){
    if(tail-head==0) return true; //head is same as tail
    else return false;

}
template<typename T>bool DynamicQueue<T>:: isFull(){
    if((N==tail)&&(head==0)) return true; //N-1 is last element so N is tail
    else return false;
}
template<typename T>void DynamicQueue<T> :: grow(){
    T *B;
    B=new T[nextSize()];
    for(int i=0;i<N;i++){//copying the elements to new array
        B[i]=A[i];
    }
    T*K;
    K=A;
    delete K;//deleting the space used by previous array
    A=B;
    N=nextSize();//incresing the size of N
}
template<typename T>unsigned DynamicQueue<T> ::size(){
    return (tail-head);
}
template<typename T>void DynamicQueue<T> ::QInsert(T x){
    if((N==tail)&&(head==0)){
        grow();
    }
    if((N==tail)&&(head!=0)){
        for(int i=0;i<tail-head;i++){ //shifting the elements to start of queue.
            A[i]=A[head+i];
        }
        tail=tail-head;
        head=0;
        
    }
    
    A[tail]=x;
    tail++;
}
template<typename T>bool DynamicQueue<T>::QDelete(T *x){
    if(tail==head) return false;
    else {
        *x=A[head];//stroing the deleted element in address x.
        head++;
        return true;
    }
    
}

