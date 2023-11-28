#include"queue.h"

//In this implementation the elements are in A[0] to A[head-1]
template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return (head==0); //Checks if queue is empty
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    return(head == N); //Returns 1 if max size has been reached 
}

template <typename T>
void DynamicQueue<T>::grow(){
    unsigned int M;
    M = nextSize(); // new size
    T *B; 
    B = new T[M]; // new array of larger size
    for(int i = 0 ; i < N ; i++){
        B[i] = A[i] ; //Copying the elements
    } 
    A = B;//Simply store new array in place of old
    N = M;
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return head; //returns current number of elements (tail will always be 0 hence number of elements is equal to head)
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()){
        grow(); // If it is full call grow
    }
    A[head] = x; //Simply insert at head
    head++;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return 0; //If empty 
    *x = A[0]; // return the element at tail
    for(int i = 0 ; i<(head-1) ; i++){
        A[i] = A[i+1]; //push back all elements
    }
    head--; 
    return 1;
}


