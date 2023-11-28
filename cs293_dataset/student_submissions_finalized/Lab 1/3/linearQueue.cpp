#include <iostream>

using namespace std;

#define CONST_GROWTH 1000
#define INIT_SIZE 1000

template <typename T> bool DynamicQueue<T>:: isEmpty()  // checks whether the array is empty or not
{
    return (tail == head);
}

template <typename T> bool DynamicQueue<T>:: isFull()   // checks whether the array is full or not
{
    return (tail - head == N);
}

template <typename T> void DynamicQueue<T>:: grow()     // grows the array
{
    N = N + CONST_GROWTH;
    T *B = new T[N];
    for(int i=head,j=0;i<tail;i++,j++)                  // copies the array A into B
    {
        B[j] = A[i];
    }
    tail = tail - head;
    head = 0;
    A = B;
}

template <typename T> unsigned int DynamicQueue<T>:: size() // returns the size of the array
{
    return tail - head;
}

template <typename T> void DynamicQueue<T>:: QInsert(T x)   // insert a provided element into the array at the tail
{
    if(tail == N)
    {
        for(int i=head,j=0;i < tail;i++,j++)
        {
            A[j] == A[i];
        }
        tail = tail - head;
        head =0;
    }
    A[tail] == x;
    tail++;

    if(isFull())                                        // checking the array full case at the last so that 
    {                                                   // there wont be the problem of continous rearranging of array
        grow();
    }
}

template <typename T> bool DynamicQueue<T>:: QDelete(T *x)  // copies the value at head into x and delete the head
{
    if(isEmpty())                                       // checks the empty case before deletion
    {
        return false;
    }
    *x = A[head];
    head++;
    return true;
}