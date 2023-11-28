#include "queue.h"
#include <string.h>

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return head == tail; 
//In this implementation, markers pointing to the same location => empty
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    return tail == N; 
//condition reached in QInsert() when tail and head agree *after* inserting an element
}

template <typename T>
void DynamicQueue<T>::grow(){
    int M = nextSize(); 
    T *B = new T[M]; //larger array on the heap
    for(int i = 0; i < N; i++){
        B[i] = A[(head + i) % N]; //copying the N elements in B
    }
    //less expensive library operations for copying
    //memcpy(B, A + head, (N - head) * sizeof(T));
    //memcpy(B + N - head, A, head * sizeof(T));
    head = 0; //the markers shifted to new places 
    tail = N;
    delete[] A; //deleting the old array
    A = B;
    N = M; 
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    if(isFull()) return N; //full => N elements
    return (N + tail - head) % N; //N added since tail < head possible here
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()){
        grow();
        A[tail] = x;
        tail = (tail + 1) % N; //allows tail to circle around the array
        return;
    }
    A[tail] = x;
    tail = (tail + 1) % N; //moving the tail ahead but allowing circularity
    if(tail == head){ //if the markers coincide, no more space.
        tail = N; //acts as an indicator for isFull(), no other way for tail to exceed N-1
        return;
    } 
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return false;
    x = &(A[head]);
    head = (head + 1) % N;
    if(isFull()){ //if removed from a full queue (tail is N), need to switch back
        tail = (N + head - 1) % N;
    }
    return true;
}

/* Debugging function 
template <typename T>
void DynamicQueue<T>::display(){
    cout << "Array Size " << N << endl;
    cout << "Head " << head << endl;
    int s = size();
    for(int i = 0; i < s; i++){
        cout << A[(head+i)%N] << " "; 
    }
    cout << endl << endl;
}
*/
