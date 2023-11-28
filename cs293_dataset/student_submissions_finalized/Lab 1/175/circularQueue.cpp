#include <iostream>
#include "queue.h"

template <class T>
unsigned int DynamicQueue<T>::size(){ // here, we need to be careful, we need to take two cases depending on whether head is ahead of tail or vice versa
    if (tail >= head) return (tail - head);
    else return (N - (head - tail));
}
template <class T>
bool DynamicQueue<T>::isEmpty(){ // pretty straightforward
    return (size() == 0);
}
template <class T>
bool DynamicQueue<T>::isFull(){ // a bit complicated this time, it's 'N-1' and not 'N' because if we allowed 'N' then the conditions of empty and full would become identical
    return (size() == N - 1);
}
template <class T>
void DynamicQueue<T>::grow(){
    if (isFull()){ // firstly we check whether array is full or not
        T *B = new T[N - 1]; // 'B' is the temporary array where elements are copied from 'A'
        for (int i = 0; i < N - 1; i++){
            B[i] = A[(head + i) % N];
        }
        A = new T[N + CONST_GROWTH]; // 'A' is increased and elements are recopied into it
        for (int i = 0; i < N - 1; i++){
            A[i] = B[i];
        }
        delete[] B; // 'B' is no longer required
        head = 0;
        tail = N - 1;
        N += CONST_GROWTH;
    }
    return;
}
template <class T>
void DynamicQueue<T>::QInsert(T x){
    if (isFull()){ // grow the array if filled ... otherwise insert normally
        grow();
    }
    A[tail] = x;
    tail = (tail + 1) % N;
    return;
}
template <class T>
bool DynamicQueue<T>::QDelete(T *x){
    if (isEmpty()){ // as per problem statmenet
        return false;
    }
    else{
        x = &A[head]; // store the deleted element
        head = (head + 1) % N;
        return true;
    }
}