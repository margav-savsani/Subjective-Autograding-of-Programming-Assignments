#include"queue.h"
//kartikn
//cs293 lab1

template<typename T>
bool DynamicQueue<T>::isEmpty(){
    return (head==tail);
} // is the queue empty?

template<typename T>
bool DynamicQueue<T>::isFull(){
    return (tail-head==N); 
} // is the queue full?

template<typename T>
void DynamicQueue<T>::grow(){
    if (!isFull()) return;    
    T* nuA = new T[nextSize()];//new loc
    for(int i=0;QDelete(nuA+i);i++){} //shift elements to new loc

    head=0;    
    N= nextSize();
    delete[]A;
    A=nuA;
} // grow the queue to its next size 

template<typename T>
unsigned int DynamicQueue<T>::size(){
    return (tail-head);
} // return the current number of elements in the queue

template<typename T>
void DynamicQueue<T>::QInsert(T x){
    if (isFull()) grow();
    else if (tail==N){ //shift elements when tail is reached without full queue
        for(int i=0;i+head<N;i++)
            A[i]=A[i+head];
        tail=tail-head;
        head=0;
    }
    A[tail++]=x;
} // insert given element at tail of the queue; grow array size as necessary

template<typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if (isEmpty()) return false;
    *x= A[head];
    head++;
    return true;
} // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise