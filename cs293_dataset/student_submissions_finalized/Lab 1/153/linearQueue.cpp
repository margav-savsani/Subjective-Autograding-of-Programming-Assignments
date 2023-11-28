#include "queue.h"

/**
 * @brief Returns the size of the queue using the position of the head and tail
 * 
 * @return unsigned int: Size of the queue
 */
template <class T>
unsigned int DynamicQueue<T>::size(){
    return tail-head;
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
    return this->size()==N;
}

/**
 * @brief Checks if the queue is full. 
 * If not, it adjusts the elements such that the tail no longer hits the end.
 * If yes, it allots a bigger array and shifts the elements accordingly.
 */
template <class T>
void DynamicQueue<T>::grow(){
    // only adjust if queue is not already full
    if(!(this->isFull())){
        unsigned int cur_size = this->size();
        for(unsigned int i=0; i<cur_size; i++) A[i]=A[head+i]; //shift the elements such that the head is at index 0
        head=0;tail=cur_size;
        return;
    }

    // queue is indeed full, increase capacity
    T *temp = new T[N];

    for(unsigned int cur=head; cur<tail; cur++) temp[cur] = A[cur];
    delete[] A;

    N = this->nextSize();
    A = new T[N];
    for(unsigned int cur=head; cur<tail; cur++) A[cur] = temp[cur];
}

/**
 * @brief Checks if the tail hits the end of the array. If so, it calls grow() to make space for insertion. When that's done, it inserts the element.
 * 
 * @param x: The element to be inserted. 
 */
template <class T>
void DynamicQueue<T>::QInsert(T x){
    if(tail == N){
        this->grow();
    }

    A[tail] = x;
    tail+=1;
}

/**
 * @brief Checks if the queue is empty. 
 * If so, it returns false, indicating a failed delete. 
 * Otherwise, it moves the head one step forward and assigns the value at x with the deleted element
 * 
 * @param x: Parameter to hold the address of the deleted element. 
 * @return bool: Returns true or false if the operation was successful or unsuccessful respectively. 
 */
template <class T>
bool DynamicQueue<T>::QDelete(T *x){
    if(this->isEmpty()) return false;

    if(x != nullptr) *x = A[head];
    head+=1;

    return true;
}