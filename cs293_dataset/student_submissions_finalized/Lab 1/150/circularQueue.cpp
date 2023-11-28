#include <iostream>
#include "queue.h"
using namespace std;

// i am maintaining tail and head with linear increase just while indexing i am taking care by using mod N
template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return (tail == head);
}

// maintaing grow when size reaches N creating a new dynamic array and pasting value one by one there
template <typename T>
void DynamicQueue<T>::grow()
{
    T *B = new T[nextSize()];
    for (int i = head; i < tail; i++)
    {
        B[i - head] = A[i % N]; // % is used to maintain circularity otherwise it will be out of bound
    }
    tail = N;
    head = 0;
    N = nextSize();
    delete (A);
    A = B;
}

/* simply substracting head and tail will give size  since they are increasing them linearly in insertion
 and deletion so if its N queue is full  and 0 if its empty*/

template <typename T>
bool DynamicQueue<T>::isFull()
{
    return ((tail - head) == N);
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return ((tail - head));
}

// head is increased linearly and will delete by changing head index since no long access.
template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (isEmpty())
    {
        return false;
    }
    else
    {
        *x = (A[head % N]);
        head = (head + 1);
        return true;
    }
}

// tail is increased linearly whereas the element in x is stored circularly in array if its not full otherwise first grow then store.
template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (isFull())
    {
        grow();
    }
    A[tail % N] = x;
    tail = (tail + 1);
}