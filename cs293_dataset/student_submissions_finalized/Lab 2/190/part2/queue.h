#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#define CONST_GROWTH 100
#define INIT_SIZE 100

#include <string>
#include <iostream>
using namespace std;


struct Journey {
  string station1;
  int start_time;
  string station2;
  int end_time;

  void print(){
    cout << start_time << " " << station2 << endl;
  }
};



class JourneyQueue {
public:
  Journey *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N+CONST_GROWTH; }
  JourneyQueue() // default constructor
  {
    A = new Journey[INIT_SIZE];
    if (A != nullptr) N = INIT_SIZE;
    else N = 0;
    head = tail = 0;
    // cout << "queue initialized" << endl;
  } 
  ~JourneyQueue(){delete[] A;}; // default destructor
  
  bool isEmpty(); // is the queue empty?
  bool isFull(); // is the queue full?
  void grow(); // grow the queue to its next size 
  unsigned int size(); // return the current number of elements in the queue
  void QInsert(Journey x); // insert given element at tail of the queue; grow array size as necessary
  bool QDelete(Journey *x); // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
  void display(int t);
  void sort();
};

#endif
