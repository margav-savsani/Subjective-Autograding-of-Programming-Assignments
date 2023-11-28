/*
    Name:- Tanmay Arun Patil
    Roll no. :- 210050156
*/

#include "queue.h"

template<typename T> bool DynamicQueue<T>::isEmpty()
{
    if(tail==head) return true;
    else return false; //To prevent ambiguity, the queue is full when array has 1 empty space left.
}

template<typename T> bool DynamicQueue<T>::isFull()
{
    if(tail == N-1 || tail - head == -1) return true;
    else return false;   //To prevent ambiguity, the queue is full when array has 1 empty space left.
                        //Either tail>=head or tail<head, signified by 1st and 2nd conditions in if() resp.
}

template<typename T> void DynamicQueue<T>::grow()
{
    if(isFull())
    {
        T* a = A; //Since we are making a new Queue to increase the size, another pointer is used to store the existing queue.

        int tmp = N; //Since we need this size to fill the elements in new queue.
        N = nextSize();
        
        A = new T[N];
        
        for(int i = 0, j = head; j==tail; i++, (j++)%tmp)
        {
            A[i] = a[j]; //Entering elements in new array of larger size.
        }

        head = 0;
        tail = tmp-1; //Starting the queue from index 0 helps us maintain order and use new space to its full capacity.
    }

    return;
}

template<typename T> unsigned int DynamicQueue<T>::size()
{
    if(tail>=head) return (tail - head);
    else return (tail + N - head); //Can be visualized easily.
}

template<typename T> void DynamicQueue<T>::QInsert(T x)
{
    if(isFull()) grow();

    A[tail] = x;
    (tail++)%N;
}

template<typename T> bool DynamicQueue<T>::QDelete(T *x)
{
    if(isEmpty()) return false;

    *x = A[head];
    (head++)%N;

    return true;
}