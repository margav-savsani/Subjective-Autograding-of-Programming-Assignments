#include "queue.h"

template <typename T>
bool DynamicQueue<T>::isEmpty() // Function to check whether the Queue is empty or not.
{
    return (tail == head); // When the head variable is the same as tail variable the queue becomes empty.
}

template <typename T>
bool DynamicQueue<T>::isFull() // Queue becomes full for the case when (tail - head is N).
                               // Note that we are allowing the tail to take values beyond N.
                               // We will operate the index based on modulo operations.
                               // eg= (N =5) head = 4, tail = 8. for this A[4] = starting element, A[(2 = 7%5)] = last element.
{
    return (tail - head == N);
}

template <typename T>
void DynamicQueue<T>::grow() // Grow function in circular array is called only when the array is full.
{
    unsigned int b = nextSize();
    T *B = new T[b]; // Alloting a new memory to a pointer.
    for (int i = head; i < tail; i++)
    { // copying the elements of the initial array to newly created array.
        // In the new array the elements are kept in a linear fashion.
        B[i - head] = A[i % N];
    }
    tail = N;   // tail becomes N
    head = 0;   // head again becomes 0
    N = b;      // grow the queue to its next size.
    delete (A); // freeing up the memory A initially pointed to.
    A = B;      // reallocating A to Newly created memory.
    B = NULL;   // making B point to NULL.
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{ // Gives the total number of elements present in the queue.
    return (tail - head);
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (isFull())
    {
        grow(); // just grow if full (in case of circular array.)
    }
    A[tail % N] = x;
    tail++;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (size() == 0)
        return false;
    *x = A[head % N]; // storing the head in x.
    head++;           // head incremented.
    return true;
}
