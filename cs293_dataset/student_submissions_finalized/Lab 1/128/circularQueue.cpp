#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){
    //use size member for determining emptiness
    return (size() == 0);
}

template <typename T> bool DynamicQueue<T>::isFull(){
    //use special tail value for determining fullness
    return (tail == N+1);
}

template <typename T> void DynamicQueue<T>::grow(){
    //grow array by allocating new space on heap

    T *new_array = new T[nextSize()];
    for (int i = 0; i < size(); i++)
    {
        new_array[i] = A[(i+head) % N];
    }
    delete[] A;
    A = new_array;
    tail = N;
    head = 0;
    N = nextSize();
    
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    //the size member function depends on tail,head and N
    //do NOT change tail, head or N before calling size()
    
    if(tail >= head){return tail-head;}
    else {return (N + tail) - head;}
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    if (isFull()){ 
        grow();
    }

    A[tail] = x;
    tail += 1;
    tail %= N;

    //set tail to a special value if an insert led to the completion of the queue
    // this way we dont have to waste an array space
    if(tail == head){tail = N+1;}
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()){return false;}
    
    //delete object here (corresponds to incrementing the head)
    *x = A[head];
    head += 1;
    head %= N;
    return true;
}