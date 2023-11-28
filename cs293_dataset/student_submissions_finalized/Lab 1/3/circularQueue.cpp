#include <iostream>

using namespace std;

#define CONST_GROWTH 1000
#define INIT_SIZE 1000

template <typename T> unsigned int DynamicQueue<T>:: size()
{
    return ((tail - head + N)%N);
}

template <typename T> bool DynamicQueue<T>:: isEmpty()
{
    return (size() == 0);
}

template <typename T> bool DynamicQueue<T>:: isFull()
{
    return (size() == N - 1);                           // leaves an element so that there wont be a confussion between
}                                                       // the cases of empty and full array

template <typename T> void DynamicQueue<T>:: grow()     
{
    T *B = new T[N + CONST_GROWTH];
    for(int i=head,j=0;j<size();i++,j++)
    {
        if(i==N) i=0;
        B[j] = A[i];
    }
    tail = size();
    head = 0;
    A = B;
    N = N + CONST_GROWTH;
}

template <typename T> void DynamicQueue<T>:: QInsert(T x)
{
    if(isFull())
    {
        grow();
    }
    if(tail == N)
    {
        tail = 0;
    }
    A[tail] == x;
    tail++;
}

template <typename T> bool DynamicQueue<T>:: QDelete(T *x)
{
    if(isEmpty())
    {
        return false;
    }
    if(head == N)
    {
        head = 0;
    }
    *x = A[head];
    head++;
    return true;
}
