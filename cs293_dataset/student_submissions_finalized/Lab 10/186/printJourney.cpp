#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#define CONST_GROWTH 1000
#define INIT_SIZE 1000

template <typename K> class DynamicQueue {
private:
  K *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N+CONST_GROWTH; }
public:
  DynamicQueue() // default constructor
  {
    A = new K[INIT_SIZE];
    if (A != nullptr) N = INIT_SIZE;
    else N = 0;
    head = tail = 0;
  } 
  ~DynamicQueue(){delete[] A;}; // default destructor
  
  bool isEmpty(); // is the queue empty?
  bool isFull(); // is the queue full?
  void grow(); // grow the queue to its next size 
  unsigned int size(); // return the current number of elements in the queue
  void push(K x); // insert given element at tail of the queue; grow array size as necessary
  bool pop(); // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
  K delHead();
};

template <typename K>
bool DynamicQueue<K>::isEmpty(){
    return (head == tail);   // queue is empty when head == tail
}

template <typename K>
bool DynamicQueue<K>::isFull(){
    return (tail == N);     
}

template <typename K>
void DynamicQueue<K>::grow(){
    if(isFull()){
        K *A1;     // A1 is the new array with larger size 
        A1 = new K[nextSize()];
        for(int i = head; i < tail; i++){   // copying elements from A to A1
            A1[i] = A[i];
        }
        N = nextSize();    
        A = A1;      
    }
}

template <typename K>
unsigned int DynamicQueue<K>::size(){
    return (tail-head);
}

template <typename K>
void DynamicQueue<K>::push(K x){
    if(isFull()){
        if(size() == N) grow();    // if queue size is full then only growing the array
        else{                      // else rearranging elements from last to top of same array
            for(int i = 0; i < size(); i++){
                A[i] = A[i+head];
            }
            tail = tail - head;
            head = 0;
        }
    }
    A[tail] = x;        // Inserting new element at tail
    tail++;
}

template <typename K>
bool DynamicQueue<K>::pop(){
    if(isEmpty()) return false;
    //*x = A[head];
    A[head] = 0;    // deleting from the head
    head++;
    return true;
}

// return head element and delete it from queue
template <typename K>
K DynamicQueue<K>::delHead(){
  K x = A[head];
  pop();
  return x;
}

void dfs(listOfObjects<StationConnectionInfo *> *start){
  cout << start->object->trains->object << endl;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  listOfObjects<StationConnectionInfo *> *adjStn = adjacency[stnNameToIndex.get(srcStnName)->value].toStations;
  dfs(adjStn);
  
  return;
}

#endif
