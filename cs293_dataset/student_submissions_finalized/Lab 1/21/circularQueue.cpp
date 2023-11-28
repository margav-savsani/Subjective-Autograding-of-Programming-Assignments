#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty() {
    return (head == tail); 
}

template <typename T> bool DynamicQueue<T>::isFull() {
    return (size() == N-1); // N-1 to avoid confusion b/w Empty and Full Queue
}

template <typename T> unsigned int DynamicQueue<T>::size() {
     if (tail >= head) return (tail - head);
     else return (N+tail-head);
}

template <typename T> void DynamicQueue<T>::grow() {
    int t = N;
    N = nextSize();

    // copy elements into new array
    T *B = new T[N];
    for (int i = 0; i < t-1 ; i++)	
        B[i] = A[(head + i)%t];

    A = B;
    head = 0;
    tail = t-1;
    }

template <typename T> void DynamicQueue<T>::QInsert(T x) {
    if (isFull()){
        int k = N;
        grow();
        A[tail] = x;
        tail = tail + 1;
    }
    
    else{
        A[tail] = x;
        tail = (tail + 1)%N;
    }
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x) {
    if (isEmpty()){
        return false;
    }
    else{
        *x = A[head];
        head = (head +1)%N;
        return true;
    }
}





