#ifndef _CIRCULAR_QUEUE_C
#define _CIRCULAR_QUEUE_C

#include "queue.h"

/**
 * @brief Returns the size of the queue using the position of the head and tail
 * 
 * @return unsigned int: Size of the queue
 */
template <class T>
unsigned int DynamicQueue<T>::size(){
    return (tail-head+N)%N;
}

/**
 * @brief Checks if the queue has no elements, using head and tail
 * 
 * @return bool: Whether the queue is empty 
 */
template <class T>
bool DynamicQueue<T>::isEmpty(){
    return (head==tail);
}

/**
 * @brief Checks if the queue has reached it's maximum capacity for the safe operation
 * 
 * @return bool: Whether the queue has reached maximum operable size 
 */
template <class T>
bool DynamicQueue<T>::isFull(){
    return this->size()==(N-1);
}

/**
 * @brief Checks if the queue is full. 
 * If yes, it allots a bigger array and shifts the elements accordingly.
 */
template <class T>
void DynamicQueue<T>::grow(){
    // don't grow if queue is not full
    if(!(this->isFull())){
        return;
    }
    unsigned int old_arr_size = N;
    unsigned int queue_size = this->size();

    T *temp = new T[N];

    for(unsigned int cur=0; cur<queue_size; cur++) temp[cur] = A[(cur+head)%N];
    head=0;tail=queue_size;
    delete[] A;

    N = this->nextSize();
    A = new T[N];

    for(unsigned int cur=head; cur<tail; cur++)
        A[cur] = temp[cur];
}

/**
 * @brief Checks if the queue has reached maximum operable capacity. If yes, it calls grow() to make space and then inserts the element at the respective spot.
 * 
 * @param x: The element to be inserted. 
 */
template <class T>
void DynamicQueue<T>::QInsert(T x){
    if(this->isFull()){
        this->grow();
    }

    A[tail] = x;
    tail = ((tail+1)%N);
}

/**
 * @brief Checks if the queue is empty. 
 * If so, it returns false, indicating a failed delete. 
 * Otherwise, it (cyclically) moves the head one step forward and assigns the value at x with the deleted element
 * 
 * @param x: Parameter to hold the address of the deleted element. 
 * @return bool: Returns true or false if the operation was successful or unsuccessful respectively. 
 */
template <class T>
bool DynamicQueue<T>::QDelete(T *x){
    if(this->isEmpty()) return false;

    if(x != nullptr) *x = A[head];
    head = ((head+1)%N);

    return true;
}

#endif