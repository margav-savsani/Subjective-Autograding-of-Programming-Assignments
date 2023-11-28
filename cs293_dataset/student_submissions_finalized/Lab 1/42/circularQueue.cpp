#ifndef CIRQ_H //Just in case the file was copied twice
#define CIRQ_H
#include<iostream>

using namespace std;

template <typename T>
bool DynamicQueue<T>::isEmpty(){ // If the head and tail point to the same element, it means the queue is empty
    return (head == tail);
}

template <typename T>
bool DynamicQueue<T>::isFull(){ 
    //My head and tail aren't integers modulo n, rather, they keep on increasing until the array becomes empty, in which case I'll reset everything to 0. Although the head and tail don't directly point to the elements that are to be added and deleted, they have information that allows us to get those indexes out of them (The hash function is mod N, where N is the size of the array through which the queue is stored, which gives us the indices.)
    if (isEmpty()) return false;
    return ((tail - head) % N == 0);
}

template <typename T>
void DynamicQueue<T>::grow(){

    // The nextSize() function increases the value of N, but only when the array is full , i.e., no space left in the array (even after adjustment and shifting). 

    // A new array B is defined, with the size being the new length of the queue. The old array is then deleted, but that just deletes the space and not the pointer, which we point again to the new queue. 

    if (isFull()) {
        N = nextSize();
        T *B = new T[N];
        int N1 = N - CONST_GROWTH;
        for (int i=head%N1;i<N1;i++){
            B[i - head%N1] = A[i];
        }
        for (int i=0;i<tail%N1;i++){
            B[N1 - head%N1 + i] = A[i];
        }
        delete[] A;
        tail = size();
        head = 0;
        A = B;
    }
}

template <typename T>
unsigned int DynamicQueue<T>::size(){

    // The size is as calculated below, will work for all tail and head. This is because, when the difference of tail and head reaches the value of N, that means the array is full (the tail pointer has cycled all the way back to the same place, but now it's become N + head, by my system.)
    return (tail - head);
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    // Growing the queue just in case the queue is full (That condition is checked inside the grow function, could have put the condition outside as well, but I didn't put it because of redundancy). I then assign x to the index tail % N, and increment the tail index (Since I don't care whether it's modulo n or not, I don't take the remainder).

    grow();
    A[tail%N] = x;
    tail++;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    // Two cases here, one where the queue is empty, in which case I return false, and when the queue is non-empty, in which case, I assign the value of the head element to the value that the pointer points to, and then increment the head pointer, since that element can't be explicitly deleted from the array, we just don't consider it by incrementing the head value.

    // After the deletion, if the queue was empty, I just assigned the head and the tail to 0, instead of whatever value it was in previously (I need not have done this, but it helps visually, to reset everything to the initial state). I then return true at the end

    if (isEmpty()) return false;
    *x = A[head%N];
    head++;
    if (isEmpty()){
        head = 0;
        tail = 0;
    }
    return true;
}

#endif