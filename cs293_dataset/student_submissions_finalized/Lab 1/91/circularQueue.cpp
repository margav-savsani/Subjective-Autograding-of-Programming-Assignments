#ifndef CIRCULAR_QUEUE_CPP
#define CIRCULAR_QUEUE_CPP

#include "queue.h"

// startegy is to allow tail to go beyond N to indicate that the tail wraps back to the start

template <typename T> bool DynamicQueue<T>::isEmpty()
{
    // if head==tail, the queue is empty
    return (head == tail);
}

template <typename T> bool DynamicQueue<T>::isFull()
{
    // if tail==head+N, the queue is full
    return (tail == head + N);
}

template <typename T> void DynamicQueue<T>::grow()
{
    // creating new array of size nextSize()
    T* next_A = new T[nextSize()];
    // element at index i%N in A goes to index (i - head) % N in next_A
    for (unsigned int i = head; i < tail; i++) {
        next_A[(i - head) % N] = A[i % N];
    }
    // updating tail and head, taking care to treat full case separately
    if (!isFull())
        tail = (tail - head) % N;
    else
        tail = N;
    head = 0;
    delete[] A;
    A = next_A;
    N = nextSize();
}

template <typename T> unsigned int DynamicQueue<T>::size()
{
    // size = tail-head (as tail is allowed to go beyond N)
    return (tail - head);
}

template <typename T> void DynamicQueue<T>::QInsert(T x)
{
    // if queue is full, we grow queue and set tail element to x
    if (isFull()) {
        grow();
    }
    A[tail % N] = x;
    tail += 1;
}

template <typename T> bool DynamicQueue<T>::QDelete(T* x)
{
    // if queue is empty we return false
    if (isEmpty()) {
        return false;
    }
    // set *x to head element
    *x = (0 + A[head]); // to avoid dangling reference
    // update head appropriately
    head = (head + 1);
    if (head == tail) {
        head = tail = 0;
    }
    else {
        head = head % N;
    }
    return true;
}

#endif
