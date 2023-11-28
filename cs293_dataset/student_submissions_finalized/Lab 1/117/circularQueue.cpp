#include<iostream>
#include "queue.h"
#include<bits/stdc++.h>
using namespace std;



template <typename T> bool DynamicQueue<T>:: isEmpty(){
    return head == tail;// returns true if head = tail which signifies an empty queue
}

template <typename T> bool DynamicQueue<T>:: isFull(){
    return size() == N ;// if the difference between head and tail is the size, 
    //then it means the queue is full. Because are head and tail are ever increasing, we won't face the issue of head== tail signifying
    //empty and closed queue both
}

template <typename T> void DynamicQueue<T>:: grow(){
    T *temp;
    temp = new T[nextSize()];// created a new array of bigger size   
    for(int i =0; i<size(); i++){// for loop to copy data
        temp[i] = A[(head+i)%N];
    }

    delete A;
    A = temp;
    tail = N;
    N = nextSize();// increase N
    head = 0;
    return;
}

template <typename T> unsigned int DynamicQueue<T>:: size(){
    return tail - head ;// size is basically the difference between tail and head
}

template <typename T> void DynamicQueue<T>:: QInsert(T x){
    if(isFull()){// if the queue is full, we need to grow it
        grow();        
    }
    A[tail%N]= x;// we store the next element and increment
    tail= (tail+1);// tail by 1
}

template <typename T> bool DynamicQueue<T>:: QDelete(T* x){
    if(isEmpty()) return false;// if the queue is empty then this function should return false
    *x = A[head%N];//stores the deleted element in *x
    head= (head + 1);// increments the head as now the next element to be deleted is after this one
    return true;// returns true if the deletion was done
}