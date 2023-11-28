#include <iostream>
#include "queue.h"
using namespace std;

// My plan is to first circle the queue, if full then I would
// increase array length and reset the queue to head=0
//Tail would be one place ahead than last element in the queue.
//I would assume N-1 boxes are there instead of N for avoiding clash with full and empty
template <class T>
bool DynamicQueue<T>:: isEmpty(){
    return (head==tail)
    //when head is tail, that means no element is there
}

template <class T>
bool DynamicQueue<T>:: isFull(){
    int i = (N-head+tail)%N;
    if (i == N-1){
        return true;
    }
    else{
        return false;
    }
    //As assumed, max size is N-1
    //when head>tail, N-head+tail would work, but when head<tail, tail-head would work
}

template <class T>
void DynamicQueue<T>:: grow(){
    int s = nextSize(); 
    T* S = new T[s]; //creating new array
    for (int i = 0; i < tail; i++)
    {
        S[N+i] = A[i]; //shifting items below head to new places
    }
    for (int i = 0; i < N; i++)
    {
        S[i] = S[head+i]; //shifting entire queue to start
    }
    head = 0;
    tail = N; //resetting head and tail
    N = s;
    A = S;
    //resetting array and size
}

template <class T>
unsigned int DynamicQueue<T>:: size(){
    int i = (N-head+tail)%N;
    return i;
}

template <class T>
void DynamicQueue<T>:: QInsert(T x){
    if(this->isFull()){
        grow();
        A[tail] = x;
        tail++;
        //if full, grow and insert
    }
    else
    {
        A[tail] = x;
        tail = (tail + 1)%N;
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