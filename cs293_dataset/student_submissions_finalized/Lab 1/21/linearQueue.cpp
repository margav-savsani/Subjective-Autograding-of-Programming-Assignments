#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty() {
    return (head == tail);
}

template <typename T> bool DynamicQueue<T>::isFull() {
    return (size() == N );
}

template <typename T> unsigned int DynamicQueue<T>::size() {
     return ( tail - head );
}

template <typename T> void DynamicQueue<T>::grow() {
    int k = N;
    N = nextSize();
    T *B = new T[N];
    for (int i = 0; i < k; i++){
        B[i] = A[i];
    }
    A = B;
}

template <typename T> void DynamicQueue<T>::QInsert(T x) {
    if (isFull()){
        grow();
        A[tail] = x;
        tail = tail+1; 
    }

    else if(tail == N){
            int k = size();
            for(int i=0; i < k; i++){
                A[i] = A[head+i];
            A[k] = x;
            head = 0;
            tail = k+1; 
        }
    }

    
    else{
        A[tail] = x;
        tail = tail + 1;
    }
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x) {
    if (isEmpty()){
        return false;
    }
    else{
        *x = A[head];
        head = head +1;
        return true;
    }
}



