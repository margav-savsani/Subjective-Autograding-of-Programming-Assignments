#include<iostream>
using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty(){
    if(head == tail)
        return true;
    else
        return false;
}

template <typename T> bool DynamicQueue<T>::isFull(){
    if(head == (tail + 1)% N)
        return true;
    else
        return false;
}

template <typename T> void DynamicQueue<T>::grow(){
    T *B;
    unsigned int p = DynamicQueue<T> ::nextSize();
    B = new T[p];
    for(int i = 0;i < N - 1;i++){
        //this part assigns the previous values to new queue
        B[i] = A[(i + head)% N];
    }
    head = 0;
    tail = N - 1;
    A = B;
    N = p;
}

template <typename T> unsigned int  DynamicQueue<T>::size(){
    return(( N - head +tail) % N);
}

template <typename T> void DynamicQueue<T>:: QInsert(T x){
    if(isFull()){
        //this part grows the queue and inserts the element
        grow();
        QInsert(x);
    }
    else{
        //this part normally inserts the element
        A[tail] = x;
        tail = (tail + 1)%N;
    }
}

template <typename T> bool DynamicQueue<T>:: QDelete(T *x){
    if(DynamicQueue<T>::isEmpty())
        return false;
    else{
        *x = A[head];
        head = (head + 1)%N;
        return true;
    }
}