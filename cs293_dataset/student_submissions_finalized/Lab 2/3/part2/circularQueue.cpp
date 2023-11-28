#include <iostream>

using namespace std;

#define CONST_GROWTH 1000
#define INIT_SIZE 1000

template <typename T> class DynamicQueue {
private:
  T *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N+CONST_GROWTH; }
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
  bool QDelete(T *x); // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
  int find(T x);
};

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
    A[tail] = x;
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

template<typename T> int DynamicQueue<T> :: find(T x)
{
    for(int i=head;i<tail;i++)
    {
        if(strcmp(x,A[i])==0) return i;
        
    }
    return -1;
}