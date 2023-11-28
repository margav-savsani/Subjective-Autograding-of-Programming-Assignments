#include "queue.h"
#include <iostream>

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return tail - head;     //size of the queue will be the difference of the head and tail indices
}

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    if (size() == 0) return true;    //if size i.e. variable size() is 0 then returning true
    else return false;
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    if (size() == N) return true;   //queue full at size() = N
    else return false;
}

template <typename T>
void DynamicQueue<T>::grow(){
    N = nextSize();     //new size of array
    T *B = new T[N];    //new array
    
    for (int i=head; i<tail; i++){  //copying the elements from previous values
        B[i-head]=A[i];
    }

    delete[] A;
    A = B;
    tail = size();
    head = 0;
    return;
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    
    
    // std::cout << "Head: " << head << " Tail: " << tail << " " << size() << " " << N << std::endl;
    if (isFull()){
        grow();         //growing the array if full
    }
    if (!isFull() && tail == N){        //if not full but still the tail points out of bounds then copying array to indices 0 to size-1
        for (int i=head; i<tail; i++){
            A[i-head]=A[i];
        }
        tail = size();
        head = 0;
    }
    A[tail] = x;
    tail = tail + 1;    //changing the tail pointer index to next value
    return;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if (isEmpty()) return false;
    *x = A[head];   //storing value of popped element in x
    head = head + 1;    //changinf head pointer to next value
    if (head == N) head = 0; //if head goes out of bounds then start from 0
    return true;
}