#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#define CONST_GROWTH 40
#define INIT_SIZE 40

#include <vector>
template <typename T>
class DynamicQueue
{
private:
  T *A;              // the array used for implementing the dynamic dequeue
  unsigned int N;    // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N + CONST_GROWTH; }

public:
  DynamicQueue() // default constructor
  {
    A = new T[INIT_SIZE];
    if (A != nullptr)
      N = INIT_SIZE;
    else
      N = 0;
    head = tail = 0;
  }
  ~DynamicQueue() { delete[] A; }; // default destructor

  bool isEmpty(){
    return (tail == head); // When the head variable is the same as tail variable the queue becomes empty.
}      // is the queue empty?
  bool isFull(){
    return (size() == N);
}      // is the queue full?
  void grow(){
    unsigned int b = nextSize();
    T *B = new T[b]; // Alloting a new memory to a pointer.
    for (int i = head; i < tail; i++)
    { // copying the elements of the initial array to newly created array.
        // In the new array the elements are kept in a linear fashion.
        B[i - head] = A[i % N];
    }
    tail = N;   // tail becomes N
    head = 0;   // head again becomes 0
    N = b;      // grow the queue to its next size.
    delete (A); // freeing up the memory A initially pointed to.
    A = B;      // reallocating A to Newly created memory.
    B = NULL;   // making B point to NULL.
}         // grow the queue to its next size
  unsigned int size(){ // Gives the total number of elements present in the queue.
    return (tail - head);
} // return the current number of elements in the queue
  void QInsert(T x){
    if (isFull())
    {
        grow(); // just grow if full (in case of circular array.)
    }
    A[tail % N] = x;
    tail+=1;
}
  bool QDelete(T *x){
    if (size() == 0)
        return false;
    *x = A[head % N]; // storing the head in x.
    head+=1;           // head incremented.
    return true;
}
};

class QueueElem
{ 
public:
  int stn_index; // station index 
  int train_no;  // The journeyCode of the train
  QueueElem()
  {
    stn_index = -1;
    train_no = -1;
  }
  QueueElem(int name, int jCode)
  {
    stn_index = name;
    train_no = jCode;
  }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int destination_index = stnNameToIndex.get(destStnName)->value;   // Index of destination station
  listOfObjects<TrainInfoPerStation *> *destination_journey = NULL;  // Journeys are stored in form of vector of their Train no.
  DynamicQueue<QueueElem> queue_BFS;
  int index = stnNameToIndex.get(srcStnName)->value;  // Index of the station_Name
  StationAdjacencyList *current ;  // The adjacency of the current station.
  current =  adjacency;  
  listOfObjects<StationConnectionInfo *> *adj_stns = current[index].toStations;

  while (adj_stns != NULL) // Storing all the adjacent Station 
  {
    int ind_of_station = adj_stns->object->adjacentStnIndex;  // Index of reached station
    listOfObjects<TrainInfoPerStation *> *train = adj_stns->object->trains;

    while (train != NULL){
      if (ind_of_station == destination_index){
        if (destination_journey == NULL){
          destination_journey = new listOfObjects<TrainInfoPerStation *>(train->object);
        }
        else{
          listOfObjects<TrainInfoPerStation *> *iterator = destination_journey;
          while (iterator->next != NULL){
            iterator = iterator->next;
          }
          iterator->next = new listOfObjects<TrainInfoPerStation *>(train->object);
        }
        train = train->next;
        continue; 
      }
      queue_BFS.QInsert(QueueElem(ind_of_station, train->object->journeyCode));
      train = train->next;
    }
    adj_stns = adj_stns->next;
  }
  while (!queue_BFS.isEmpty()){                                    
    QueueElem *head = new QueueElem(); // Head of the Queue
    queue_BFS.QDelete(head);           // This stores the Head in the 'head' pointer and deletes it
    int trainno = head->train_no;      
    int stn_ind = head->stn_index;       // Gives Station index of the HEAD.
    adj_stns = adjacency[stn_ind].toStations;
    while (adj_stns != NULL){
      listOfObjects<TrainInfoPerStation *> *train = adj_stns->object->trains;
      int adjStn = adj_stns->object->adjacentStnIndex;
      while (train != NULL){
        if (train->object->journeyCode == trainno){
          if (adjStn == destination_index){
            if (destination_journey == NULL){
              destination_journey = new listOfObjects<TrainInfoPerStation *>(train->object);
            }
            else{
              listOfObjects<TrainInfoPerStation *> *iterator = destination_journey;
              while (iterator->next != NULL)
              {
                iterator = iterator->next;
              }
              iterator->next = new listOfObjects<TrainInfoPerStation *>(train->object);
            }
            break; 
          }
          queue_BFS.QInsert(QueueElem(adjStn, trainno)); // Adding the element
        }
        train = train->next;
      }
      adj_stns = adj_stns->next;
    }
  }
  listOfObjects<TrainInfoPerStation *> *source_dest_train = NULL;
  listOfObjects<TrainInfoPerStation *> *Total_source = stationInfo[stnNameToIndex.get(srcStnName)->value];
  vector<int> Train_nos;  // to store train no.s in dest
  while (destination_journey != NULL)
  {
    Train_nos.push_back(destination_journey->object->journeyCode);
    destination_journey = destination_journey->next;
  }
  while (Total_source != NULL){
    for (int i = 0; i < Train_nos.size(); i++){
      if (Train_nos[i] == Total_source->object->journeyCode){
        if (source_dest_train == NULL){
          source_dest_train = new listOfObjects<TrainInfoPerStation *>(Total_source->object);
        }
        else{
          listOfObjects<TrainInfoPerStation *> *iterator = source_dest_train;
          while (iterator->next != NULL){
            iterator = iterator->next;
          }
          iterator->next = new listOfObjects<TrainInfoPerStation *>(Total_source->object);
        }
      }
    }
    Total_source = Total_source->next;
  }
  if (source_dest_train == NULL){
    cout<< RED << "No direct journeys available" << RESET << endl;
    return;
  }
  
  printStationInfo(source_dest_train);
  return;
}

#endif
