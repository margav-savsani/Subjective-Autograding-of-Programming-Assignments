#include "queue.h"



template <typename T> bool DynamicQueue<T>::isEmpty()
{
    if (size()==0 ) // Check if array is empty
    return true;

    else
    return false;
}

template <typename T> bool DynamicQueue<T>::isFull()
{
    if ((head==tail) && size()!=0) // Check if array is full
    return true;

    else
    return false;
}

template <typename T> void DynamicQueue<T>::grow()
{

    N=nextSize(); // New size of array
    T *arr = new int[N]; // Create another array having
            //size as the new size

    if(tail==0) // If elements got filled linearly
    {

       for( int i = 0; i<N-CONST_GROWTH; i++)
       {
           arr[i]=A[i];
       }
       tail=N-CONST_GROWTH; // New value of tail
    }

    else // If there is curling around
    {
       int i=tail-1;
       int j=0;
       int c=0;

       //Add elements starting from the last element
       // in the queue to the new array
       while(j<=(N-CONST_GROWTH))
       {
          arr[i] = A[i-c];
          i--;
          j++;

          // If we reach beginning of first array,
          //go back around to the end
          if(i<0)
          {
             i=N-1;
             c=CONST_GROWTH;
          }
       }

       head=head+CONST_GROWTH; //New value of head
    }

    delete[] A;
    A=arr;
}

template <typename T> unsigned int DynamicQueue<T>::size()
{
      if(head!=tail)
      return ((N-(head-tail))%N);

      else // If array is full or empty
      {
         if(A==nullptr)
         return 0;

         else
         return N;
     }
}


template <typename T> void DynamicQueue<T>::QInsert(T x)
{
   if(isFull())
   {
      grow(); // Increase size of array

      A[tail]=x; //Add x to the end of queue
      tail++;
      tail=tail%N;
    }


    else
    {
      A[tail]=x;
      tail++;
      tail=tail%N;
    }
}




template <typename T> bool DynamicQueue<T>::QDelete(T *x)
{
    // If queue is empty
    if (isEmpty())
    {
        return false;
    }


    else
    {
       *x=A[head];

       head++;
       head=head%N;
       return true;
    }



}
