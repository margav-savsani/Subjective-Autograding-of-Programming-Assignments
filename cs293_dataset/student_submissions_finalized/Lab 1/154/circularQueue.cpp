/*
    CS293 Lab1
    Name: Govind Kumar
    Roll: 210050058
*/

# include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){
    return head == tail; 
}
template <typename T> bool DynamicQueue<T>::isFull(){
    return size() == N - 1; // not N to prevent ambiguity of head == tail
}
template <typename T> void DynamicQueue<T>::grow(){
    // similar to linear queue
    // make new array, copy elements, delete original array
    unsigned int curr_size = size();
    T* temp = new T[nextSize()];   // new array
    for(unsigned int i=0; i<curr_size; i++){
        temp[i] = A[(i+head) % N]; // because of circular implementation
    }
    head = 0;   // make head=0
    tail = curr_size; // and tail = size before growing
    delete[] A;  // deleting prev array
    A = temp;  // updating A
    N = nextSize();  // updating N
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    return (N + tail - head ) % N; // circular implementation so looping
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    if(isFull()){  // check if array is full before insert operation and grow if needed
        grow();
    }
    A[tail] = x;  
    tail = (tail + 1) % N;  // circular implementation so looping
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return false;  // check for empty before deleting
    *x = A[head]; 
    head = (head + 1) % N;  // circular implementation so looping
    return true;
}
