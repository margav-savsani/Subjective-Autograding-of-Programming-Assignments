#include "queue.h"
#include <cmath>

template <class T>
bool DynamicQueue<T>::isEmpty()
{
    // Checking if Queue is empty (head=tail)
    if (head == tail)
    {
        return true;
    }
    return false;
}

template <class T>
bool DynamicQueue<T>::isFull()
{
    // checking if size of the queue is N-1 (i.e, about to fill) so that its defined as Full in Circular Queue
    if (size() == N - 1)
    {
        return true;
    }
    return false;
}

template <class T>
unsigned int DynamicQueue<T>::size()
{
    // Size of the Circular Queue(Purely mathematic Calculation):
    return (N - (head - tail)) % N;
}

template <class T>
void DynamicQueue<T>::grow()
{
    // Creating a New Empty Array by increasing the size of the Array by nextsize func which grows in A.P. sequence
    T *B;
    B = new T[nextSize()];
    // Copying the previous Queue.
    // But now, we start freshly from the head element as the starting element in the fresh array, and then followed by copying remaining elements upto right end.
    // Then, we start from left End,and then we add the elements poto Tail element into the fresh array(continued).
    for (int i = head; i < N; i++)
    {
        B[i - head] = A[i];
    }
    for (int i = 0; i < tail; i++)
    {
        B[N - head] = A[i];
    }

    // deleting the previous array to free up memory
    delete[] A;

    // resetting head and tail
    head = 0;
    tail = N - 1;
    // updating N;
    N = nextSize();
    // Setting our fresh array as our array which is defined in parent class
    A = B;
}

template <class T>
void DynamicQueue<T>::QInsert(T x)
{
    if (isFull())
    {
        // growing if queue is full
        grow();
        // and then inserting the element
        A[tail] = x;
        tail++;
        // resetting tail
        tail = tail % N;
        // terminating func.
        return;
    }
    // resetting tail bfore insertion
    tail = tail % N;
    A[tail] = x;
    tail++;
}

template <class T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (isEmpty())
    {
        // returning false if empty
        return false;
    };
    if (head == N - 1)
    {
        // pointing about to delete element to *x which is passed as argument.
        *x = A[head];
        // setting head to 0 if head=N-1.
        head = 0;
        return true;
    }
    else
    {
        // pointing about to delete element to *x which is passed as argument.
        *x = A[head];
        // directly increasing head
        head++;
        return true;
    }
}
