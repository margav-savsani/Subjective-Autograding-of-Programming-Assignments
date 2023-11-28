#include <iostream>
#include "queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty(){
    if(head == tail) return true; //when location of head and tail overlap, the linear queue is empty
    else return false;
}

template <typename T> bool DynamicQueue<T> :: isFull(){
    if(tail - head == N) return true; // when number of elements between head and tail equals the size of the queue, the linear queue is full
    else return false;
}

template <typename T> void DynamicQueue<T> :: grow(){
    int previous_N = N; // storing the original value of N in previous_N variable
    N = nextSize(); // this function returns new size of the queue and N is updated accordingly
    T *B = new T[N]; // a new array of new size is created
    for(int i = 0; i < previous_N; i++) B[i] = A[i]; // original elements are copied to the new array

    delete[] A;// freeing the heap storage
    A = B;// changing the variable name back to the same
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
    return tail - head; // this returns number of elements in the linear queue
}

template <typename T> void DynamicQueue<T> :: QInsert(T x){
    if(!isFull()){ //if queue is not full
        if(tail != N){ //if tail is not at the end of the queue
            A[tail] = x; //appending element at the end
        }
        else{ // if tail is at the end of the queue
            T *B = new T[N]; //new array creation
            for(int i = head; i < tail; i++){
                B[i - head] = A[i]; // copying elements to the new array starting from index 0
            }
            head = 0;
            tail = tail - head;
            delete[] A; // removing heap storage
            A = B;  // reallocating memory
        }
    }
    else{ //if queue is full
        grow(); // calling grow() function
        A[tail] = x; // appending element at the end of the grown queue
    }
    tail++;// new position of tail
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
    if(isEmpty()) return false; // if queue is empty , delete operation can't be done
    else{ // if queue is not empty
        int x_size = *(&x + 1) - x; //x_size stores size of array x
        T *y = new T[N];
        for(int i = 0; i < x_size; i++){
            y[i] = x[i]; // copying elements to new aray
        }
        y[x_size] = A[head]; // storing head element in the y array
        x = y; // reallocating memory
        return true;

    }
}