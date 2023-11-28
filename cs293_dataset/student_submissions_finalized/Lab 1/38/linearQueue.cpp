#include <iostream>
#include "queue.h"
using namespace std;



template <typename T>  bool DynamicQueue<T>::isEmpty() 
//As the function is empty only when the head of the queue equals to the tail of the queue, We are just checking if head == tail
{
    return (head == tail);
};

template <typename T> bool DynamicQueue<T>::isFull()
//The queue will be full only when head is 0 and tail is N 
{
    return ((tail == N) && (head == 0));
}

template <typename T> void DynamicQueue<T>::grow()
//(Remark:- We are assuming that the grow function is being called only when the queue is full and a new element is about to added to it.) For growing A, we are creating a new array B of more size than A, copy all the elements from A are now copied to B, and then doing A = B
{
    N = N + CONST_GROWTH;
    T *New_A;
    New_A = new T[N];
    for (int i = head; i < tail; i++)
    {
        New_A[i] = A[i];
    }
    A = New_A;
}

template <typename T> unsigned int DynamicQueue<T>::size()
//As the queue starts from head and goes till tail, size of the queue will be tail - head.
{
    return tail - head;
}

template <typename T> void DynamicQueue<T>::QInsert(T x)
//Here we are considering three cases
//		1) tail is not N: Here we can directly add element at the end of the queue at the position of tail and increase the tail.
//		2) tail is N, but head is not 0: Here, we can't directly add element of queue at the end as we can't access the N th index of the array. So We move the queue to the start and then add element at the tail position
//		3) tail is N, and head is 0: Here as we have no space in the queue, we grow the queue and add element at the tail.
{
    if (isFull()) grow();
    else if(tail == N)
    {
        for(int i = head ; i < tail ; i++) A[i - head] = A[i];
        tail = tail - head;
        head = 0;
    }
    A[tail] = x;
    tail++;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x)
//deleting element is just removing element at head so Here I am just increasing head by 1
{
    if (isEmpty()) return false;
    *x = A[head];
    head++;
    return true;
}
