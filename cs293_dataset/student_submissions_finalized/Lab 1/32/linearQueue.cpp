#include "queue.h"
#include<iostream>


template <typename T> bool DynamicQueue<T>::isEmpty()
{
    if (head==tail )
    return 1;

    else
    return 0;
}

template <typename T> bool DynamicQueue<T>::isFull()
{
    if (tail==N && head==0) // If all places of array are occupied
    return 1;

    else
    return 0;
}

template <typename T> void DynamicQueue<T>::grow()
{

    N=nextSize();   // Increase the size of the array
    T *arr = new T[N];  //Create a new array to copy elements to

    for(int i = head; i<=tail-1; i++)
    {
        arr[i-head]=A[i]; // Copy elements of the array
    }

      // Delete the previous array
    A=arr;
}

template <typename T> unsigned int DynamicQueue<T>::size()
{
      return tail-head;
}


template <typename T> void DynamicQueue<T>::QInsert(T x)
{
   if(isFull())
   {
      grow();  // Increase the array size and copy the elements

      A[tail]=x; // Add the new element to the end of the array
      tail++; // Shift tail by 1
    }

    else if(size()<N && tail==N)  // If array end is reached but
    // positions at the beginning
    // are empty due to deletion
    {
        for(int k =head; k<=tail-1; k++)
        {
            A[k-head]=A[k]; // Shift elements to re-occupy
                             //empty places
        }

        tail=tail-head; // New position of tail
        head=0;         // New position of head

        A[tail]=x;   // Add new element to end of array
        tail++;      // Shift tail by 1

    }

    else // If the array isn't full
    {
      A[tail]=x; //Add new element to array end
      tail++;  // Shift tail by 1
    }
}




template <typename T> bool DynamicQueue<T>::QDelete(T *x)
{
    if (head==tail) // If queue is empty
    {
        return false;
    }


    else
    {
       *x=A[head];
       head++; // Shift head by 1
       return true;
    }



}
