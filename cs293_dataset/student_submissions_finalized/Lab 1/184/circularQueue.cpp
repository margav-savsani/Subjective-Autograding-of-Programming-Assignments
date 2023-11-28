#include<iostream>
#include "queue.h"
using namespace std;

template <typename T> unsigned int DynamicQueue<T> :: size(){ //returns # of elements in the array, not the size of the array
    return (N-head+tail)%(N);
}

template <typename T> bool DynamicQueue<T> :: isEmpty(){
    if(size()==0) return true;
    else return false;
}

template <typename T> bool DynamicQueue<T> :: isFull(){                  // I am defining full array at N-1 elements only
    if(size()==N-1) return true;//here I am using N-1 because I want to fill elements upto N-1 places only so that we should get confused betwewen empty and full array
    else return false;
}

template <typename T> void DynamicQueue<T> :: grow(){
    T *B;
    	B=new T[nextSize()];
    	for(int i=head;i<tail;i++){
     		B[i]=A[i];
     	}
     	//A=new T[nextSize()];
     	A=B;
     	N=nextSize();
}

template <typename T> void DynamicQueue<T> :: QInsert(T x){
    if(!isFull()){
        A[tail]=x;
        tail=(tail+1)%(N);
    }
    else{
        grow();
        A[tail]=x;
        tail=(tail+1)%(N);
    }
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return false;
    else{
        head=(head+1)%(N);
        return true;
    }
}
