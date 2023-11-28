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
    return size() == N;
}
template <typename T> void DynamicQueue<T>::grow(){
    unsigned int curr_size = size();
    N = nextSize();
    T* temp = new T[N]; // create a new array of new size
    for(unsigned int i=0; i<curr_size; i++){
        temp[i] = A[i+head]; // copy the elements
    }
    head = 0; // make head = 0
    tail = curr_size; // and tail to current size
    delete[] A; // delete the original array
    A = temp; 
}
template <typename T> unsigned int DynamicQueue<T>::size(){
    return tail - head;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    if(isFull()){ // check if array is full before insert
        grow();
    }
    else if((tail == N) || (head > N/2)){ 
        // if the tail is reached but array not full or the head is greater than half of the size,
        // then rearrange to make head 0
        unsigned int curr_size = size();
        for(unsigned int i =0; i< curr_size; i++){
            A[i] = A[i+head];
        }
        head = 0;
        tail = curr_size;
    }
    A[tail] = x;
    tail++;
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return false;
    *x = A[head];
    head++;
    return true;
}
