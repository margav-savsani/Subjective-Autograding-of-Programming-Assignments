#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){  //Empty if tail = head
    return tail-head==0;
}

template <typename T> bool DynamicQueue<T>::isFull(){   //Queue is full when size of array = size of
    return tail==N && head==0;
}

template <typename T> void DynamicQueue<T>::grow(){     //Function to grow the array
    T *Temp;
    Temp = new T[nextSize()];
    for (int i = 0 ; i < N ; i++){
        Temp[i] = A[i]; 
    }
    A = Temp;
    N = nextSize();
}

template <typename T> unsigned int DynamicQueue<T>::size(){ //Returns the size of queue
    return tail-head;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){   //Inserts the element into queue
    if (isFull()){                                          //If queue is full, array is increased in size
        grow();
    }
    else if(tail==N){                                       //If tail reaches end of array, then this condition is invoked
        T *Temp;
        Temp = new T[N];
        for ( int i = 0 ; i < tail-head ; i++){
            Temp[i] = A[head+i];
        }
        A = Temp;
        tail = tail-head;
        head = 0;
    }
    A[tail]=x;
    tail++;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){  //Head is moved "deleting" the element
    if(isEmpty()){
        return 0;
    }
    x = &A[head];
    head++;
    return 1;
}





