#include "queue.h"

//CircularQueue

template <typename T> bool DynamicQueue<T>::isEmpty(){
    if(head == tail) return true;
    else return false;

    /*
        It seems reasonable that the above condition will
        arise when the queue is either empty or full.

        But the queue is never full for the user of the queue
        data type.
        As soon as the array gets full, the array grows.
        Hence the queue is never full.

        As far as code between inserting the last element and calling grow 
        function is concerned, it is understood that array is full.
        isFull() and isEmpty() functions are not to be used there
        as they will give erroneous results. The usage of these 
        functions in the definitions of other functions is in my hands.
        My duty is to make sure that they dont give erroneous result to the 
        user which they don't.

        The following code is written keeping the above reasoning in mind.

    */
}

template <typename T> bool DynamicQueue<T>::isFull(){
    return false;
}

template <typename T> void DynamicQueue<T>::grow(){
    unsigned int New_N = N + CONST_GROWTH;
    T* New_A = new T[New_N];
    
    for(int i = 0; i < N; i++){   //Copying elements from old to new array
        New_A[i] = A[(head + i)%N];
    }

    head = 0;
    tail = N;

    N = New_N;
    delete[] A;
    A = New_A;
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    unsigned int queueSize = (N + tail - head)%N;
    return queueSize;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    // The queue is designed such that queue can always insert
    // a new element.
    A[tail] = x;

    if((N + tail - head)%N == N-1){ //At this stage, tail is not modified, hence the condition.
        grow();
        return;
    }

    tail = (tail + 1)%N;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return false;

    *x = A[head];
    head = (head + 1)%N;
    return true;
}