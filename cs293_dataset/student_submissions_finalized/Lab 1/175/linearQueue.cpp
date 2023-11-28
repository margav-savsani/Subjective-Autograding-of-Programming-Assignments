#include <iostream>
#include "queue.h"

template <class T>
unsigned int DynamicQueue<T>::size(){ // just the difference of tail and head
    return (tail - head);
}
template <class T>
bool DynamicQueue<T>::isEmpty(){ // pretty straightforward
    return (size() == 0);
}
template <class T>
bool DynamicQueue<T>::isFull(){ // pretty straightforward
    return (size() == N);
}
template <class T>
void DynamicQueue<T>::grow(){
    if (isFull()){ // first checked whether array is full or not
        T *B = new T[N]; // 'B' is a temporary array storing the contents of 'A'
        for (int i = 0; i < N; i++){
            B[i] = A[i];
        }
        A = new T[N + CONST_GROWTH]; // the size of 'A' is increased and elements are recopied into it
        for (int i = 0; i < N; i++){
            A[i] = B[i];
        }
        delete[] B; // 'B' is no longer needed
        N += CONST_GROWTH;
    }
    return;
}
template <class T>
void DynamicQueue<T>::QInsert(T x){
    if (tail != N){ // tail is not yet 'N' meaning the array still has space at the end
        A[tail] = x;
        tail ++;
    }
    else if (!isFull()){ // the array doesn't have space at the end but has at the start ... elements are shifted to make space at the end
        for (int i = 0; i < size(); i++){
            A[i] = A[head + i];
        }
        tail = size();
        head = 0;
    }
    else{ // array neither has space at the start or at the end, we need to grow the array
        grow();
        A[tail] = x;
        tail ++;
    }
    return;
}
template <class T>
bool DynamicQueue<T>::QDelete(T *x){
    if (isEmpty()){ // as per problem statement
        return false;
    }
    else{
        x = &A[head]; // store the deleted element
        head ++;
        return true;
    }
}