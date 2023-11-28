#include "queue.h"


//LinearQueue

bool JourneyQueue::isEmpty(){
    if(size() == 0) return true;
    else return false;
}

bool JourneyQueue::isFull(){
    //Queue is considered FULL when it has N elements.
    if(size() == N) return true;
    else return false;
}

void JourneyQueue::grow(){
    // grow() is called only when queue is full i.e. when head = 0 and tail = N
    unsigned int New_N = N + CONST_GROWTH;
    Journey *New_A = new Journey[New_N];

    //Copying elements from A to New_A
    for(int i=0; i<N; i++){
        New_A[i] = A[i];
    }

    head = 0;
    tail = N;
    N = New_N;
    delete[] A;
    A = New_A;
}

unsigned int JourneyQueue::size(){
    unsigned int queueSize = tail - head;
    return queueSize;
}

void JourneyQueue::QInsert(Journey x){

    if(tail == N){
        for(int i=0; i < size(); i++){
            A[i] = A[head + i];
        }
    }
    tail = tail - head;
    head = 0;

    A[tail] = x;
    tail++;

    if(isFull()){
        grow();
    }
}

bool JourneyQueue::QDelete(Journey *x){
    if(isEmpty()){
        return false;
    }

    *x = A[head];
    head++;
    return true;
}

void JourneyQueue::display(int t){
    sort();
    for(int i = head; i != tail; i++){
        if(A[i].start_time >= t) A[i].print();
    }
}

void JourneyQueue::sort(){
    unsigned int i, j, min_idx;
 
    // One by one move boundary of
    // unsorted subarray
    for (i = head; i < tail - 1; i++)
    {
       
        // Find the minimum element in
        // unsorted array
        min_idx = i;
        for (j = i+1; j < tail; j++)
        if (A[j].start_time < A[min_idx].start_time)
            min_idx = j;
 
        // Swap the found minimum element
        // with the first element
        if(min_idx!=i){
            // swap(&arr[min_idx], &arr[i]);
            Journey temp = A[min_idx];
            A[min_idx] = A[i];
            A[i] = temp;
        }
    }
}
