#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


/** Queue Implementation from Previous lab **/

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
};

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return (head==tail);    // Queue is empty if head equals tail
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    return (head==0 && tail==N);    // Queue is full if head is 0 and tail is N
}

template <typename T>
void DynamicQueue<T>::grow(){
    unsigned int sz = (tail-head);   // Store current size
    T* B = A;                        // Store a pointer to current array
    N = nextSize();                  // Get next size
    A = new T[N];                    // point A to a new bigger array

    for(unsigned int i=0; i<sz; i++){  // fill the elements in A using B
        A[i] = B[i];
    }
    delete[] B;                      // delete old array
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return (tail-head);              
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(tail==N){                    // Handle if tail has reached the end
        if(isFull()){               // If array is full then grow
            grow();                 
        }   
        else{                       // else shift all elements back
            unsigned int sz = (tail-head);      // store current size (number of elements)
            for(unsigned int i=0; i<sz; i++){   
                A[i] = A[head+i];               // copy all elements backwards
            }
            head = 0;               
            tail = sz;
        }
    }

    A[tail] = x;
    tail++;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty())
        return false;
    else{
        *x = A[head];
        head++;
        return true;
    }
}
// === Queue ends === //



// If there are multiple trains between two stations then each train is an edge
// struct for edges of graph storing index of station to which its pointing and journeycode of its train
struct edge{
  int stnIndex;
  int journeyCode;
  edge(int i, int j)
    : stnIndex(i), journeyCode(j)
  {}
  edge()
    : stnIndex(-1), journeyCode(-1)
  {}
};



void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex = stnNameToIndex.get(destStnName)->value;

  // if no train leaves from source then end
  if(adjacency[srcIndex].toStations == nullptr){
    cout << "No direct journeys available" << endl;
    return;
  }
  // if no train reaches the destination then end
  if(adjacency[destIndex].fromStations == nullptr){
    cout << "No direct journeys available" << endl;
    return;
  }

  // Linked list for storing journey codes of direct journey
  listOfObjects<int> *directJourneyCodes = nullptr;

  // Queue for modified BFS
  DynamicQueue<edge> Q;

  // Each edge containing journeycode and index station of station which is pointed by it is stored separately in bfs queue

  // First add only those edges adjacent to source which have journey code in the intersection of all journeys which start from source and all journeys which end at destination
  listOfObjects<StationConnectionInfo *> * stns1 = adjacency[srcIndex].toStations;
  while(stns1 != nullptr){  // Iterate over stations adjacents to source
    listOfObjects<TrainInfoPerStation *> *trains1 = stns1->object->trains;
    while(trains1 != nullptr){  // Iterate over all trains in the adjacent stations


      listOfObjects<StationConnectionInfo *> * stns2 = adjacency[destIndex].fromStations;
      while (stns2 != nullptr){ // Iterate over all stations adjacent to destination
        bool found = 0;
        listOfObjects<TrainInfoPerStation *> *trains2 = stns2->object->trains;
        while(trains2 != nullptr){  // Iterate over all trains in the adjacent stations
          // If match is found then add the edge of that journey code
          if(trains1->object->journeyCode == trains2->object->journeyCode){
            edge e(stns1->object->adjacentStnIndex, trains1->object->journeyCode);
            Q.QInsert(e);
            found = 1;
            break;
          }

          trains2 = trains2->next;
        }
        if(found) break;
        stns2 = stns2->next;
      }
      
      
      trains1 = trains1->next;
    }
    stns1 = stns1->next;
  }
  

  // Now pop first edge from queue each time and add its adjacent edge containing the same journeyCode till destination is found or no adjacent edge is possible
  while(!Q.isEmpty()){
    // pop first element
    edge curr(0, 0);
    Q.QDelete(&curr);

    // If reached destination then add that journeycode to directJourneyCodes linked list
    if(curr.stnIndex == destIndex){
      listOfObjects<int>* node = new listOfObjects<int>(curr.journeyCode);
      node->next = directJourneyCodes;
      directJourneyCodes = node;
      continue;
    }

    // Add its adjcent edge with same journeycode
    listOfObjects<StationConnectionInfo *> * stns = adjacency[curr.stnIndex].toStations;
    while(stns != nullptr){
      listOfObjects<TrainInfoPerStation *> *train = stns->object->trains;
      bool found = 0;
      while(train != nullptr){
        if(train->object->journeyCode == curr.journeyCode){
          edge e(stns->object->adjacentStnIndex, curr.journeyCode);
          Q.QInsert(e);
          found = 1;
          break;
        }
        train = train->next;
      }
      if(found) break;
      stns = stns->next;
    }
  }

  // Get info of direct journeys from source in directJourneys linked list using allJourneys from source and the computed directJourneyCodes
  listOfObjects<TrainInfoPerStation *> * allJourneys = stationInfo[srcIndex];
  listOfObjects<TrainInfoPerStation *> * directJourneys = nullptr;
  
  listOfObjects<int> * d = directJourneyCodes;
  while(d != nullptr){
    listOfObjects<TrainInfoPerStation *> * a = allJourneys;
    while(a != nullptr){
      if(d->object == a->object->journeyCode){
        listOfObjects<TrainInfoPerStation *> * node = new listOfObjects<TrainInfoPerStation *>(a->object);
        node->next = directJourneys;
        directJourneys = node;
        break;
      }
      a = a->next;
    }  
    
    d = d->next;
  }

  // Print result
  if(directJourneys != nullptr){
    printStationInfo(directJourneys);
  }
  else{
    cout << "No direct journeys available" << endl;
  }

  return;
}
