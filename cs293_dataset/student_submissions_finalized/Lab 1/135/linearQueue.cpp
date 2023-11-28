#include "queue.h"

template <typename T> bool DynamicQueue<T>:: isEmpty(){//tells whether the queue is empty or not
    return (head == tail);//if head is equal to tail that means there is no element in the array
}

template <typename T> bool DynamicQueue<T>:: isFull(){//tells whether the queue is full or not
    return (size() >= N);//if size is greater than the length of the array that means tail has already gone out of bound and hence the queue is full.
}

template <typename T> void DynamicQueue<T>:: grow(){//grows the array in order to store more elements
    if(isFull()){//grows only when the queue is full, does nothing otherwise
        //create an array of newsize
        T* newA;
        newA = new T[nextSize()];
        //copy the elements of the original array into the new array
        for(int i = 0; i<N; i++){
            newA[i] = A[i];
        }
        //change the current array to the new one
        A = newA;
        //change the size of the current array to the new array size
        N = nextSize();
    }
}

template <typename T> unsigned int DynamicQueue<T>:: size(){//gives the cuurent size of the queue
    return tail-head;//(tail-head) gives the size of the queue(since tail is always >= head)
}

template <typename T> void DynamicQueue<T>:: QInsert(T x){//inserts a new element x into the queue
    //if the queue is already full grows the queue then inserts the new element
    //if queue is full grow makes it such that it is no longer full
    //and if it was not full then we have space for the new element
    grow();
    //if tail is more than N, it means the front of the array is empty so we need to move the queue to the front of the arrays
    if(tail>=N){
        for(int i=0; i<size(); i++){
            A[i] = A[head+i];
        }
        head = 0;//now head is at start
        tail = size();//now tail is at the end of the queue
    }
    //add new element at tail position and increase tail
    A[tail] = x;
    tail++;
    //std::cout << N << " " << head << " " << tail << "\n";//debugging
}

template <typename T> bool DynamicQueue<T>:: QDelete(T *x){//deletes the element at the start of the head and stores it in x(given variable)
    //if queue is empty return false else delete element and return true
    if(isEmpty()){
        return 0;
    }
    else{
        //store element at head in x and move head to next position
        *x = A[head];
        head++;
        //std::cout << N << " " << head << " " << tail << "\n";//debugging
        return 1;
    }
}