#include "queue.h"
using namespace std;

template <typename T>
bool DynamicQueue<T>::isEmpty() // is the queue empty?
{
  return (size()==0);
};

template <typename T>
bool DynamicQueue<T>::isFull() // is the queue full?
{
  return (size()==N);
};

template <typename T>
void DynamicQueue<T>::grow() // grow the queue to its next size
{
  if (isFull())              // checking is Queue full?
  {
    unsigned int current_size = N; // number of elements in Queue
    N = nextSize();
    T *arr = new T[N]; // created new array with extended size
    for (unsigned int i = 0; i < current_size; i++)
      arr[i] = A[i]; // copying elements to new array
    A = arr;
  }
};

template <typename T>
unsigned int DynamicQueue<T>::size() // return the current number of elements in the queue
{
  return (tail - head);
};

template <typename T>
void DynamicQueue<T>::QInsert(T x) // insert given element at tail of the queue; grow array size as necessary
{
  unsigned int current_size = size();
  if (tail == N && head != 0) // arranging elements in array if possible when last reaches to end of array
  {
    for (unsigned int i = 0; i < current_size; i++)
      A[i] = A[head + i];
    head = 0;
    tail = current_size;
  }
  else if(current_size==N)
    grow(); // increasing size of Queue if needed
  A[tail] = x; // adding element to last of array
  tail++;
};

template <typename T>
bool DynamicQueue<T>::QDelete(T *x) // delete element at head of the queue and place it in *T; returns false if queue is empty, 						   true otherwise
{
  if (isEmpty()) // checking is Queue empty?
    return false;

  *x = A[head]; // putting element from Queue in *T
  head++;
  return true;
};
