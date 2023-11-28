#include "queue.h"

template <typename T> bool DynamicQueue<T>:: isEmpty(){//tells whether the queue is empty or not
    return (head == tail);//if head is equal to tail that means there is no element in the array
}

template <typename T> bool DynamicQueue<T>:: isFull(){//tells whether the queue is full or not
    //we consider the array full if the array has 1 empty space
    //so if we want to create an empty circularqueue at the start we would have to put init_size to 1 instead of 0
    //as having an array of 1 is full with 0 elements and hence will instantly call grow
    //this is done to avoid confusion when checking for empty
    return (size() >= N-1);//if size is more than N-1, it means the array is full
}

template <typename T> void DynamicQueue<T>:: grow(){//grows the array in order to store more elements
    if(isFull()){//grows only when the queue is full, does nothing otherwise
        //create an array of newsize
        T *newA = new T[nextSize()];
        //copy the elements of the original array in the new array in proper order
        for(int i=0; i<size(); i++){
            newA[i] = A[(head+i)%N];
        }
        //change the current array to the new one
        A = newA;
        //now head is 0 and tail is N-1
        head = 0;
        tail = N-1;
        //change N to the new size of array
        N = nextSize();
    }
}

template <typename T> unsigned int DynamicQueue<T>:: size(){//gives the cuurent size of the queue
    return (N + tail-head)%N;//(N + tail-head)%N gives the size of the queue since now it follows modulo indexing
}

template <typename T> void DynamicQueue<T>:: QInsert(T x){//inserts a new element x into the queue
    //if the queue is already full grows the queue then inserts the new element
    //if queue is full grow makes it such that it is no longer full
    //and if it was not full then we have space for the new element
    grow();
    //add new element at tail position and increase tail while taking modulo N
    A[tail] = x;
    tail = (tail+1)%N;
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
        head = (head+1)%N;
        //std::cout << N << " " << head << " " << tail << "\n";//debugging
        return 1;
    }
}
