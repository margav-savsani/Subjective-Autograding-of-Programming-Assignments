

struct Station {
  char stationName[32];
};

struct Journey {
  Station station1;
  float startTime;
  Station station2;
  float endTime;

};

struct Query{
  // define suitable fields here
  char QueryName[32];
  Journey journey;
};
#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#define CONST_GROWTH 1000
#define INIT_SIZE 1000

class DynamicQueue {
private:
  Journey *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N+CONST_GROWTH; }
public:
  DynamicQueue() // default constructor
  {
    A = new Journey[INIT_SIZE];
    if (A != nullptr) N = INIT_SIZE;
    else N = 0;
    head = tail = 0;
  } 
  // ~DynamicQueue(){delete[] A;}; // default destructor
  
  bool isEmpty(); // is the queue empty?
  bool isFull(); // is the queue full?
  void grow(); // grow the queue to its next size 
  unsigned int size(); // return the current number of elements in the queue
  void QInsert(Journey x); // insert given element at tail of the queue; grow array size as necessary
  bool QDelete(Journey *x); // delete element at head of the queue and place it in *Journey; returns false if queue is empty, true otherwise
  bool comparator(Journey a, Journey b); //a > b
  void show();
  unsigned int returnHead(){return head;}
  unsigned int returnTail(){return tail;}
  unsigned int  trueSize();
  Journey& operator[](int index)
  {
      return A[index];
  }
  

};


#endif
