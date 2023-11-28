#ifndef LINEAR_QUEUE_CPP
#define LINEAR_QUEUE_CPP

#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty()
{
    // queue is empty if head==tail
    return (head == tail);
}

template <typename T> bool DynamicQueue<T>::isFull()
{
    // queue is full if head==0 and tail==N (so that next insertion will have to be outside)
    return (tail == N && head == 0);
}

template <typename T> void DynamicQueue<T>::grow()
{
    // new array with size nextSize()
    T* next_A = new T[nextSize()];
    // element at index i in A goes to index (i-head) in next_A as head in A goes to 0 in next_A
    for (unsigned int i = head; i < tail; i++) {
        next_A[i - head] = A[i];
    }
    // updating tail, head, A, N
    tail = tail - head;
    head = 0;
    delete[] A;
    A = next_A;
    N = nextSize();
}

template <typename T> unsigned int DynamicQueue<T>::size()
{
    // size = tail-head, valid as tail >= head at all times
    return (tail - head);
}

template<typename T> void DynamicQueue<T>::QInsert(T x)
{
    // if array is full, we grow it and set tail element to x
    if (isFull()) {
        grow();
        A[tail] = x;
        tail += 1;
    }
    // else if not full but tail==N, we "consolidate" the array (so that head==0 and space is made at the end) and set tail element as x
    else if (tail == N) {
        for (unsigned int i = head; i < tail; i++) {
            A[i - head] = A[i];
        }
        A [tail - head] = x;
        tail = (tail - head) + 1;
        head = 0;
    }
    // else we can directly set tail element as x
    else {
        A[tail] = x;
        tail += 1;
    }
}

template<typename T> bool DynamicQueue<T>::QDelete(T* x)
{
    // if isEmpty() we return false
    if (isEmpty()) {
        return false;
    }
    // setting *x to the head element and incrementing head
    *x = (0 + A[head]); // to prevent dangling reference when A is eventually deleted
    head += 1;
    // if head==tail, the queue is empty, so we set both to zero to save future consolidations
    if (head == tail) {
        head = tail = 0;
    }
    return true;
}

#endif
