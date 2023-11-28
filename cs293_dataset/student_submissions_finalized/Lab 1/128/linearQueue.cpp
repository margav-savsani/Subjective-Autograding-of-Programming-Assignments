#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){
    //use size member for determining emptiness
    return (size() == 0);
}

template <typename T> bool DynamicQueue<T>::isFull(){
    //use size member for determining fullness
    return (size() == N);
}

template <typename T> void DynamicQueue<T>::grow(){
    //grow array on heap by allocating more memory, deleting the current heap
    // While expanding the array, the current queue is copied in order onto the bigger array
    // and the head and tail members are re-set correctly

    T *new_array = new T[nextSize()];
    for (int i = 0; i < size(); i++)
    {
        new_array[i] = A[(i+head)];
    }
    delete[] A;
    A = new_array;
    N = nextSize();
    tail = size();
    head = 0;
    
    
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    //note (importantly) that the size member function depends on the current values of head and tail
    //do not modify head or tail before calling size()
    return tail - head;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    
    //grow array if Full

    if (isFull()){ 
        grow();
    }

    //move elements of linear queue up to 0, so that we dont expand array unless full
    else if (tail == N){
        for(int i = 0; i < size(); i++){
            A[i] = A[i + head];
        }
        tail = size();
        head = 0;
        
    }

    //insertion operation
    A[tail] = x;
    tail += 1;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){

    //if queue is empty return false, also reset the indices.
    if(isEmpty()){
        head = 0;
        tail = 0;
        return false;
    }
    
    //delete object here (corresponds to incrementing the head)
    *x = A[head];
    head += 1;

    if(isEmpty()){
        head = 0;
        tail = 0;
    }
    return true;
}