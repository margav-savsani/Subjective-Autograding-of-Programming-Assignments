#include <iostream>
#include<cmath>
#include "queue.h"

using namespace std;



template <typename T>  bool DynamicQueue<T>::isEmpty() 
//Even here the queue is empty if head == tail
{
    return (head == tail);
};

template <typename T> bool DynamicQueue<T>::isFull()
//Here isFull is different from linear, here there are two cases,
//		1) head > tail: Here to avoid tail = head case we are only inserting N-1 elements in queue of size N.
//		2) tail > head: Here the queue will only be full if head = 0 and tail = N-1
{
    return (tail+1 == head || (tail == N-1 && head == 0));
}

template <typename T> void DynamicQueue<T>::grow()
//Here also there will be two cases as above and here also we are assuming grow is being called when queue is full.
//		1) head > tail: Here first I am creating an array of increased size. and copy the elements of A to the new array by 
//			- All elements from 0 to tail will be copied directly.
//			- the elements from head to N of the queue will be added at the end of the new queue
//		2) head < tail: Here we directly copy elements from head to tail to the new array
//		make A equal to new array.
{
    if (head == 0)
    {
        T *New_A;
        N = (N + CONST_GROWTH);
        New_A = new T[N];
        for (int i = head; i < tail; i++)
        {
            New_A[i] = A[i];
        }
        A = New_A;
    }
    else 
    {
        T *New_A;
        New_A = new T[(N + CONST_GROWTH)];
        for (int i = 0; i < tail; i++)
        {
            New_A[i] = A[i];
        }
        for(int i = head; i < N; i++)
        {
            New_A[i + CONST_GROWTH] = A[i];
        }
        A = New_A;
        head = head + CONST_GROWTH;
        N = (N + CONST_GROWTH);
    }
}

template <typename T> unsigned int DynamicQueue<T>::size()
//here size will be (N+tail-head)%N and in this case tail maybe less than head.
{
    return (tail-head+N)%N;
}

template <typename T> void DynamicQueue<T>::QInsert(T x)
//QInsert(T x) - here also we'll whave two cases
//		1) If the queue is full then grow the queue. and add element at the position of the tail.
//		2) if the queue is not full, directly add element at the position of tail 
//		(Remark:- In circular queue, if tail = N-1 after add an element make sure tail becomes 0)
{
    if (isFull()) grow();
    A[tail] = x;
    tail = (tail+1)%N;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x)
//just delete the element af the position of head and make sure head don't crosses N-1.
{
    if (isEmpty()) return false;
    *x = A[head];
    head = (head+1)%N;
    return true;
}
