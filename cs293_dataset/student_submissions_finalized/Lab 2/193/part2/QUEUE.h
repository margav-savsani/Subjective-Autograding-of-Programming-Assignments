#include<iostream>
#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H
#define INIT_SIZE 10 //initial size is 10.

template <typename T> class DynamicQueue {
private:
  T *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N*2; }
public:
  DynamicQueue() // default constructor
  {
    A = new T[INIT_SIZE];
    if (A != nullptr) N = INIT_SIZE;
    else N = 0;
    head = tail = 0;
  } 
  ~DynamicQueue(){delete[] A;}; // default destructor
  
  bool isEmpty(); // is the queue empty?
  bool isFull(); // is the queue full?
  void grow(); // grow the queue to its next size 
  unsigned int size(); // return the current number of elements in the queue
  void QInsert(T x); // insert given element at tail of the queue; grow array size as necessary
  void QDelete(); // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
  void print(); //prints all the nodes of the queue.
  T getindex(int i); // returns the element at the index specified.
};

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
void DynamicQueue<T>::QDelete()
{
    head++;
}
template <typename T>
T DynamicQueue<T>::getindex(int i)
{
    return A[head + i];
}
template <typename T>
void DynamicQueue<T>::print(){
  for (int i=head;i<tail;i++){
    std::cout<<A[i].start_t<<" "<<A[i].end<<std::endl;
  }
}
#endif
