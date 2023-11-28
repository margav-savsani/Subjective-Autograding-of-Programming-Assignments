#include <iostream>
#include "queue.h"
using namespace std;

// My plan is to first fill the given space, if full then I would increase array length
//Tail would be one place ahead than last element in the queue.
//I would assume N-1 boxes are there instead of N for avoiding clash with full and empty

template <class T>
bool DynamicQueue<T>:: isEmpty(){
    if (tail == head){
        return true;
    }
    else{
        return false;
    }
    //If tail = head, we confirm queue is empty
}

template <class T>
bool DynamicQueue<T>:: isFull(){
    if (tail == N && head == 0){
        return true;
    }
    else 
        return false;
    //If tail = N and head = 0 , then it is considered to be full
}

template <class T>
void DynamicQueue<T>:: grow(){
    if(head>0 && tail == N){
        for (int i = 0; i < tail-head; i++)
        {
            /* code */
            A[i] = A[head+i];
        }
        //this will move queue to origin and ensure to use unused space occured due to removing heads
        tail = tail-head;
        head = 0;
    }
    if(head == 0 && tail == N){
        int s = nextSize();
        T* S = new T[s];
        for (int i = 0; i < N; i++)
        {
            /* code */
            S[i] = A[i];
        }
        //If queue is full, we will grow array 
        N = s;
        A = S;
        //resetting array and size
    }
}

template <class T>
unsigned int DynamicQueue<T>:: size(){
    int i = (N-head+tail)%N;
    return i;
}

template <class T>
void DynamicQueue<T>:: QInsert(T x){
    if (tail == N ){
        grow();
        A[tail] = x;
        tail++;
        //if full, grow and insert
        //It calls grow whenever tail=N, then it check the case and do as given in grow
    }
    else{
        A[tail] = x;
        tail++;
        //else add normally
    }
}

template <class T>
bool DynamicQueue<T>:: QDelete(T* x){
    if (this->isEmpty()){
        return false;
    }
    else
    {
        A[head] = 0;
        head++;
        return true;
    }
    //If empty, then no need, else we remove prvs one and replace by 0.
}