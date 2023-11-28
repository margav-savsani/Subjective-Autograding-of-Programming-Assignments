#include "queue.h"
template <typename T>
bool DynamicQueue<T>::isEmpty() // Function to check whether the Queue is empty or not.
{
    return (tail == head); // When the head index is the same as index where the next element is to added then the queue becomes empty.
}

template <typename T>
bool DynamicQueue<T>::isFull() // Queue becomes full for the case when tail is equal to N.
{
    return (tail == N);
}

template <typename T>
void DynamicQueue<T>::grow() // grow function is called only when the Array is full and all its indices are filled.
{
    N = nextSize();  // grow the queue to its next size.
    T *B = new T[N]; // Alloting a new memory to the pointer.
    unsigned int s = size();
    for (int i = 0; i < s; i++)
    { // copying the elements of the initial array to newly created array.
      // Since elements in A are already such that head == 0 and tail == size().
        B[i] = A[i];
    }
    delete (A);
    A = B; // reallocating the A to Newly created memory.
    B = NULL;
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{ // Gives the total number of elements present in the queue.
    return (tail - head);
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (isFull()) // condition when no more memory to allocate next (tail == N)
    {
        if (head != 0) // If the array is accomodable in current size then shift the elements.
        {
            unsigned int s = size();
            for (int i = 0; i < s; i++)
            {
                A[i] = A[head + i];
            }
            tail = s;
            head = 0;
        }
        else
            grow(); // called only for case when head == 0 and tail == N.
    }
    A[tail] = x;
    tail++;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (size() == 0)
        return false;
    *x = A[head]; // storing the head
    head++;       // index of head incremented.
    return true;
}
