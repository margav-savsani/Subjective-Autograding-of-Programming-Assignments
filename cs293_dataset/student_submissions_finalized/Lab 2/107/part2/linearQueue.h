#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H


#define CONST_GROWTH 100
#define INIT_SIZE 100

template <typename T> class LinearQueue {
private:
  T *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N+CONST_GROWTH; }
public:
  LinearQueue() // default constructor
  {
    A = new T[INIT_SIZE];
    if (A != nullptr) N = INIT_SIZE;
    else N = 0;
    head = tail = 0;
  }
  ~LinearQueue(){delete[] A;}; // default destructor
  T* allTravels();  // return the array A
  int size(); // return the current number of elements in the queue
  bool isFull(); // is the queue full?
  void grow(); // grow the queue to its next size
  void QInsert(T x); // insert given element at tail of the queue; grow array size as necessary
};

#endif
