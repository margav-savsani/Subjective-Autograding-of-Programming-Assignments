
#include<iostream>
using namespace std;

#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){// is the queue empty?

  if (head == tail){//it is empty if head and tail are equal
    return true;
  }
  return false;
} 


template <typename T> bool DynamicQueue<T>::isFull(){// is the queue full?
  if (tail == -1){ //have assigned tail is -1 to mean queue is full

    return true;
  }
  return false;
}; 


template <typename T> void DynamicQueue<T>::grow(){// grow the queue to its next size
  T* B;
  B = new T[nextSize()]; //make a new array of new size
  for (int i = 0; i < N; i++){
    int j = i+head;
    if (j > N-1){
      j = j%N;//looping around
    }
    B[i] = A[j]; //assign old data to start of new array
  }
  delete[] A;
  A = B;
  head = 0;
  tail = N;
  N = nextSize();
};  
  
  
template <typename T> unsigned int DynamicQueue<T>::size(){// return the current number of elements in the queue

  if(tail == -1){
    return N; //is it is -1, then queue is full
  }
  if (tail < head){
    return tail+N-head; //looping around
  }
  return tail-head;//general case
}; 
  
  
template <typename T> void DynamicQueue<T>::QInsert(T x){// insert given element at tail of the queue; grow array size as necessary

  if(tail == -1){//if queue is full, it will have to be grown
    grow();
  }

  A[tail] = x;
  tail+=1;//increment tail
  if (tail ==N){
    tail = 0;//looping
  }

  if(tail == head){
    tail = -1;//if loop has become full, that should be specified
  }

  
}; 
  
  
template <typename T> bool DynamicQueue<T>::QDelete(T *x){// delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
  if (isEmpty()){
    return false;//check for empty array
  }
  *x = A[head];//assigning value to *x
  if(tail == -1){
    tail = head;//if queue was full earlier, make it non-full now
  }
  head += 1;//head is incremented as the first element is removed
  if(head == N){
    head = 0;//looping
  }
  
  return true;
  
}; 

/*
int main(){
  cout << "yes" <<endl;
  DynamicQueue<int> q1;
  cout << q1.isEmpty() << endl;
  cout << q1.size() << endl;
  q1.QInsert(4);
  q1.QInsert(5);
  cout << "yess" << endl;
  cout << q1.isEmpty() << endl;
  cout << q1.size() << endl;
  int cont = -1;
  cout << "yes" << endl;
  cout << q1.QDelete(&cont) << endl;
  cout << cont << endl;
  cout << q1.isEmpty() << endl;
  cout << q1.size() << endl;
  cout << q1.QDelete(&cont) << endl;
  cout << cont << endl;
  cout << q1.isEmpty() << endl;
  cout << q1.size() << endl;
  cout << q1.QDelete(&cont) << endl;
  cout << endl << "phase 2" << endl << endl;

  cout << q1.size() << endl;
  q1.QInsert(2);
  q1.QInsert(9);
  cout << q1.isFull() << endl;
  cout << q1.size() << endl;
  q1.QDelete(&cont);
  cout << cont << endl;
  q1.QInsert(7);
  q1.QInsert(2);
  cout << q1.isFull() << endl;
  cout << q1.size() << endl;
  q1.QInsert(6);
  q1.QInsert(8);
  cout << q1.size() << endl;
  cout << q1.isFull() << endl;
  
  cout << q1.QDelete(&cont) << endl;
  cout << cont << endl;
  cout << q1.isEmpty() << endl;
  cout << q1.size() << endl;
  cout << q1.isFull() << endl;
};

*/




