#include "queue.h"
#include <iostream>
using namespace std;

template <typename T>
void DynamicQueue<T>::grow()
{
    N = nextSize(); // increasing the size of array
    T *temp = A;    // storing A's pointer in temp
    T *B = new T[N];
    for (int i = 0; i < tail; i++)
    {
        B[i] = A[i]; // copying the array
    }
    A = B;         // pointing A to B
    delete[] temp; // deleting the previous array
}
template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return tail - head; // size of an array
}
template <typename T>
bool DynamicQueue<T>::isFull()
{
    return size() == N; // full if size=n
}
template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return tail == head; // empty if head=tail
}
template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (isFull())
    { // if array is full then grow the array , insert x in tail and increment tail by 1
        grow();
        A[tail] = x;
        tail += 1;
    }
    else
    {
        if (tail < N)
        { // if array is not full and tail is not at the last position insert element at tail and increment tail by 1
            A[tail] = x;
            tail += 1;
        }
        else
        {
            // if array is full amnd tail is at last position, we need to rearrange the whole array and bring everything to front
            for (int i = head; i < tail; i++)
            {
                A[i - head] = A[i];
            }
            tail = tail - head;
            head = 0;
        }
    }
}
template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{ // for deleting an element delete it from head and increase head by 1
    if (isEmpty())
    {
        return false;
    }

    *x = A[head];

    head += 1;
    return true;
}
