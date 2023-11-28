#include<iostream>
#include "queue.h"
using namespace std;

template <typename T> unsigned int  DynamicQueue<T>::size(){ //returns no of elements in the array, not the size of the array
    return tail;
}

template <typename T> bool DynamicQueue<T>::isEmpty(){
    if(size()==0) return true; //checking if size of array is zero which is equivalent to checking # of elements in the array is zero
    else return false;
}

template <typename T> bool DynamicQueue<T>:: isFull(){
    if(size()==N) return true; //checking if # of elements in the array is equal to current size of the array
    else return false;
}

template <typename T> void DynamicQueue<T>:: grow(){
    	T *B;
    	B=new T[nextSize()];
    	for(int i=0;i<N;i++){
     		B[i]=A[i];
     	}
     	//A=new T[nextSize()];
     	A=B;
     	N=nextSize();
}



template <typename T> void DynamicQueue<T>:: QInsert(T x){
    if(!isFull()){//if the array is not full we can directly insert the element at the last of the queue 
        A[tail]=x;
        tail++;
    }
    else if (isFull()){ //if the array is full, first we increase the size of the array and then insert the element
        grow();
        A[tail]=x;
        tail++;
    }
}

template <typename T> bool DynamicQueue<T>:: QDelete(T *x){
    if(isEmpty()) return false;
    else{ 
        for(int i=0;i<tail-1;i++){
            A[i]=A[i+1];//Here even though the time complexity is more I shifted the remaining elements to the left to have a simple array
        }
        return true;
    }
}
