#include <iostream>
#include "queue.h"

template < typename T>
bool DynamicQueue<T> :: isEmpty(){
    return tail == head;
}
template < typename T>
bool DynamicQueue<T> :: isFull(){
    return tail == N && head == 0; //if array space is completely used
}
template < typename T>
void DynamicQueue<T> :: grow(){
    T *Anew;
    Anew = new T[nextSize()];
    N = N+CONST_GROWTH;
    for(int i=head; i<tail; i++){
        Anew[i] = A[i];             // new array is created and eleents are copied 
    }
    delete(A);
    A = Anew;
}
template < typename T>
unsigned int DynamicQueue<T> :: size(){
    return tail-head;
}
template < typename T>
void DynamicQueue<T> :: QInsert(T x){
    if(isFull())
        grow();
    else if(tail ==  N){
        for(int i=0; i<size(); i++){    // if array isn't full and tail is at last position, every element is shifted in order such that head is again at 0 and tail is at size() position.
            A[i] = A[head+i];           // this ennsures that array capacty is not increased unless the array is complete.
        }
        tail = size();
        head = 0;
    }
    A[tail] = x;
    tail++;
}
template < typename T>
bool DynamicQueue<T> :: QDelete(T *x){
    if(isEmpty())
        return false;  // understandable.
    *x = A[head];
    head++;
    return true;
}
