#include "queue.h"
template <typename T>
unsigned int DynamicQueue<T>::size(){
    if (head <= tail){          //depending on whether head is larger or tail we will define size differently
        return tail - head;
    }
    else {
        return N+tail-head;     //for tail < head we add the result to N to get correct size
    }
}
template <typename T>
bool DynamicQueue<T>::isEmpty(){
    if (size() == 0) return true;    //if size i.e. variable N is 0 then returning true
    else return false;
}
template <typename T>
bool DynamicQueue<T>::isFull(){
    if (size() == N-1) return true;     //to remove the ambiguity of full and empty we take N-1 as full
    else return false;
}
template <typename T>
void DynamicQueue<T>::grow(){
    int N_pre = N;      //previous value of N
    int sz = size();    //previous value of size stored
    N = nextSize();     //new value of N
    T *B = new T[N];    //new array 
    for (int i=head; i<sz; i = i+1){    //copying the previous elements
        B[i-head]=A[i%N_pre];       //i-head will be 0 for the first element and so on and modulus used as array is circular
    }
    delete[] A;
    A = B;          //deleting and copying the array in A
    tail = sz;       //specifying new head and tails
    head = 0;
    return;
}
template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if (isFull()){      //if array is full then growing it
        grow();
    }
    A[tail] = x;    //adding the element and then changing the tail in modulo fashion
    tail = (tail + 1)%N;
    return;
}
template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if (isEmpty()) return false;    //returning false for empty array
    *x = A[head];   //storing the deleted value pointer in x
    head = (head + 1)%N; //changing head in modulus fashion
    return true;
}