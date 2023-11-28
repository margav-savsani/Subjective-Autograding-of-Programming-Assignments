#include <iostream>

using namespace std;

template < typename T > bool DynamicQueue < T > ::isEmpty() {
  if (head == tail) return true; //not necessarily equal to 0
  else return false;
}
template < typename T > bool DynamicQueue < T > ::isFull() {
  if (tail - head == N) return true; //when no.of elements equal to N which is possible when head=0 tail=N
  else return false;
}
template < typename T > void DynamicQueue < T > ::grow() {
  T * B;
  B = new T[nextSize()];
  for (int i = 0; i < N; i++) {
    B[i] = A[i];   //copying all elements in last queue to new queue with nextsize
  }
  N = nextSize();
  A = B;
}
template < typename T > unsigned int DynamicQueue < T > ::size() {
  return tail - head;   //no.of elements present in queue
}
template < typename T > void DynamicQueue < T > ::QInsert(T x) {
  if (tail - head == N) {
    grow();                 //if queue is full I grow its size 
  } else if (tail == N) {
    T * B;                  //if there are no empty spaces in right but if there are on left then create a new queue with same size and copy elements in same order but shifting them to left
    B = new T[N];
    int j = 0;
    for (int i = head; i < tail; i++) {
      B[j] = A[i];
      j++;
    }
    int k = head;
    head = head - k;
    tail = tail - k;
    A = B;
    } else{
    A[tail] = x;           //just insert element at tail 
  }
  A[tail] = x;
  tail++;                 //update tail by 1
}
template < typename T > bool DynamicQueue < T > ::QDelete(T * x) {
  if (head == tail) return false;   //if queue is full then return false
  else {
    *x = A[head];                  //stores element present at tail in x 
    head = head + 1;               //updating head
    return true;
  }
}
