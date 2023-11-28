#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

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
  T getHead();
};

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return (head == tail);   // queue is empty when head == tail
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    return (tail == N);     
}

template <typename T>
void DynamicQueue<T>::grow(){
    if(isFull()){
        T *A1;     // A1 is the new array with larger size 
        A1 = new T[nextSize()];
        for(int i = head; i < tail; i++){   // copying elements from A to A1
            A1[i] = A[i];
        }
        N = nextSize();    
        A = A1;      
    }
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return (tail-head);
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
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

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return false;
    *x = A[head];
    A[head] = 0;    // deleting from the head
    head++;
    return true;
}

template <typename T>
T DynamicQueue<T>::getHead(){
  return A[head];
}


void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  //cout << "This function is to be implemented by you." << endl;
  Entry<int> *srcStnEntry = stnNameToIndex.get(srcStnName);
  Entry<int> *destStnEntry = stnNameToIndex.get(destStnName);
  StationAdjacencyList srcStn = adjacency[srcStnEntry->value];
  StationAdjacencyList destStn = adjacency[destStnEntry->value];
  listOfObjects<StationConnectionInfo *> *adj = srcStn.toStations;
  DynamicQueue<StationAdjacencyList> q;
  q.QInsert(srcStn);
  while(!q.isEmpty()){
    StationAdjacencyList stn = q.getHead();
    // BFS!
  } 
  return;
}
