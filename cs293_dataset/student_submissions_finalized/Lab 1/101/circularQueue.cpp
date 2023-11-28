#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){  //Returns if queue is empty
    return (tail-head)==0;
}

template <typename T> bool DynamicQueue<T>::isFull(){   //Queue is full if number of elements in array = N-1
    return (tail-head)%N == N-1;
}

template <typename T> void DynamicQueue<T>::grow(){     //Grows the array
    T *Temp;
    Temp = new T[nextSize()];
    for ( int i = 0 ; i < (tail-head)%N + 1 ; i++){
        Temp[i] = A[(head+i) % N];
    }
    tail = (tail-head)%N;
    head = 0;
    A = Temp;
    N = nextSize();
}

template <typename T> unsigned int DynamicQueue<T>::size(){         //Returns the size of queue
    return (tail-head)%N;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){           //If queue is full, it's size is increase: Elements is then inserted into the queue
    if (isFull()){
        grow();
    }
    A[tail]=x;
    tail = (tail+1) % N;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){          //Head is moved, thereby "deleting" the element
    if(isEmpty()){  
        return 0;
    }
    x = &A[head];
    head = (head+1)%N;
    return 1;
}