#include <iostream>
//I assumed no.of elements present in queue can only be size of queue-1
using namespace std;
template < typename T > bool DynamicQueue < T > ::isEmpty() {
  if (head == tail) return true;   //not necessarily equal to 0
  else return false;
}
template < typename T > bool DynamicQueue < T > ::isFull() {
  if ((N - head + tail) mod N == N - 1) return true; //if no.of elements in queue is equal to N-1 then it is full
  else return false;
}
template < typename T > void DynamicQueue < T > ::grow() {
  T * B;
  B = new T[nextSize()];
  int j = 0;
  for (int i = head; i < N; i++) {
    B[j] = A[i];                        //copying all elements in last queue to new queue with nextsize
    j++;
  }
  if (tail < head) {
    for (int i = 0; i < tail; i++) {
      B[j] = A[i];
      j++;
    }
  }
  N = nextSize();
  head = 0;
  tail = j;
  A = B;
}
template < typename T > unsigned int DynamicQueue < T > ::size() {
  return (N + tail - head) mod N;        //no.of elements present in queue
}
template < typename T > void DynamicQueue < T > ::QInsert(T x) {
  if ((N - head + tail) mod N == N - 1) {
    grow();                               //if queue is full I grow its size 
    A[tail] = x;
    tail = (tail + 1) mod N;              //The advantage in circularqueue is that it can insert elements at left empty spaces also without creating new array and copu=ying which will increase time
  } else {
    A[tail] = x;                          //just insert element at tail
    tail = (tail + 1) mod N;              //update tail by 1
  }
}
template < typename T > bool DynamicQueue < T > ::QDelete(T * x) {
  if (head == tail) return false;   //if queue is full then return false
  else {
    *x = A[head];                   //stores element present at tail in x
    head = head + 1;                //updating head
    return true;
  }
}
