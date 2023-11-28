#include <iostream>
#include "queue.h"
using namespace std;
template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    if (head == tail)
        return true;  // it is obv. that if tail is equal to head then the size is zero.
    else
        return false;
};

template <typename T>
bool DynamicQueue<T>::isFull()
{
    if (tail == (N) && head == 0)  // its basically implies size = N.
        return true;
    else
        return false;
};

template <typename T>
void DynamicQueue<T>::grow()
{
    if (tail == (N) && head == 0)
    {
        T *Anew;
        Anew = new T[N]; // making a new array of type T and size N
        Anew = A; // copying A to Anew
        A = new T[N + CONST_GROWTH]; //Increasing the size of array A.
        N = N + CONST_GROWTH; // Increasing the value of N.
        for (unsigned int i = head; i < tail; i++)
        {
            A[i] = Anew[i]; // copying back Anew to A(with increased size).
        }
        return;
    }
};

template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return (tail - head); // size of array will always be equal to (tail - head).
};

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (tail == (N) && head == 0)
    { // if the array is full then the size of array will grow first and the will add the element.
        grow();
        A[tail] = x; // adding an element to the index tail
        tail++; // and then incrementing tail.
        return;
    }

    else if (tail == N)
    { // this is the case when tail is at end of array and head is now at 0th index
      // then tere will be space in array but can't be accessible.
        unsigned int k = size();
        for (unsigned int i = 0; i < k; i++)
        {
            A[i] = A[i + head]; // now copying the elements to the back empty indexes. 
        }
        head = 0;
        tail = k;
        A[tail] = x;
        tail++;
        return;
    }

    else
    { // normal case if there is space in array mormally.
        A[tail] = x;
        tail++;
        return;
    }
};

template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (head == tail)
        return false; // if there is no element in array then what to take out.
    else
    {
        *x = A[head]; // putting the the elemnt to be deleted in x
        head++;  // and incrementing the head.
        return true;
    }
}; 