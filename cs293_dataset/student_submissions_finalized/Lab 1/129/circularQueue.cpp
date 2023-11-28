#include "queue.h"
#include <iostream>
using namespace std;

template <typename T>
void DynamicQueue<T>::grow()
{

    T *y = A; // copying A's pointer into y

    T *B = new T[nextSize()];
    for (int i = head; i < N; i++)
    { // copying the whole array into a new array of greater length and even rearranging it
        B[i - head] = A[i];
    }
    for (int i = 0; i < head; i++)
    {
        B[N - head + i] = A[i];
    }

    A = B; // copying B's pointer into A
    delete[] y;
    head = 0; // I have rearranged so my head is zero and tail is already N

    N = nextSize(); // increasing N
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{
    if (tail == N)
    {             // if the array has N elements ,next element should get added outside the array so tail is already N.
        return N; // and so size is N if tail is N .
    }

    return (N + tail - head) % N; // else just return the normal length obtained using this formula .
}

template <typename T>
bool DynamicQueue<T>::isFull()
{
    return (size() == N); // array is full if the size is N
}

template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return size() == 0; // array empty when size is zero
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    // cout<<N<<" "<<head<< " "<<tail<<endl; some tests
    if (isFull())
    { // if array is full ,then grow
        grow();
        A[tail] = x;           // adding element at tail
        tail = (tail + 1) % N; // increasing the tail by 1
    }
    else
    {
        A[tail] = x; // adding an element at tail
        if (size() == N - 1)
        { // if size = N-1 , then ,after adding an element ,size becomes N so tail should point at the next element to be added so it should point at N
            tail = N;
        }

        else
        { // else do normal operations on tail , increase it's length in circular  manner
            tail = (tail + 1) % N;
        }
    }
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    // cout<<N<<" "<<head<< " "<<tail<<endl; some tests
    if (isEmpty())
    {
        return false; // can't delete from an empty array
    }
    if (isFull())
    {                 // Now , this statement is written because I had put my tail to N now after deleting element at head , 1 place becomes empty so we would point tail there because
                      // the last element inserted was just besides head in circular manner and increase the head in circular manner
        *x = A[head]; // storing the deleted element
        tail = head;

        head = (head + 1) % N;
        return true;
    }

    *x = A[head];
    head = (head + 1) % N;
    return true;
}
