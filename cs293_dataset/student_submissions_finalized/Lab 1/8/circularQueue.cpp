#include<iostream>
#include "queue.h"

template<>
unsigned int DynamicQueue<int>::size(){
    return (tail - head);
}

template<>
bool DynamicQueue<int>::isEmpty(){
    return head == tail;
}

//i am filling only N-1 elements so that i can differentiate when the queue is full and when it is empty
//if i fill the queue with exactly N elements then in both full and empty cases we will have head==tail 
template<>
bool DynamicQueue<int>::isFull(){
    return (head - tail == 1 || tail - head == N-1);
}

template<>
void DynamicQueue<int>::grow(){
    N = nextSize();
    
    int *temp = new int[N];
    //copy the existing data to a new list temp
    for (int i = head; i < head+N-1; i++)   temp[i-head] = A[i%(N-1)];
    

    //pointing the A ptr to temp
    delete A;
    A = NULL;
    A = temp;

    //updating the head and the tail
    tail = N-1;
    head = 0;
}

template<>
void DynamicQueue<int>::QInsert(int x){
    //queue full
    if (isFull())
    {
        grow();
        A[tail] = x;
        tail++;
    }

    //queue full from end
    else if (tail == N-1 && head!=0)
    {
        A[tail%(N-1)] = x;
        tail = (tail+1) % N;
    }

    //queue not full from anywhere
    else {
        A[tail] = x;
        tail = (tail+1) % N;
    }
    
    
}

template<>
bool DynamicQueue<int>::QDelete(int* x){
    if (isEmpty()) return false;
    
    //changing head of the queue to effectively delete the element from the queue and returning the element in the variable x.
    *x = A[head];
    A[head] = -1;

    //updating the head
    head = (head+1) % (N);
    return true;
}