#ifndef PLANNER_H
#include "planner.h"
#endif

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

// Finds the train with a given Journey Code from list of Trains
TrainInfoPerStation* find(int jrnyCode ,listOfObjects<TrainInfoPerStation *> *listOfTrains){
  while(listOfTrains != nullptr){
    if(listOfTrains->object->journeyCode == jrnyCode) return listOfTrains->object;
    listOfTrains = listOfTrains->next;
  }
  return nullptr;
}

// Prints all Direct Journeys from given source station to destination
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // List of adjacent stations of source where trains departing from source go 
  listOfObjects<StationConnectionInfo *> *srcToStations = adjacency[stnNameToIndex.get(srcStnName)->value].toStations;

  listOfObjects<TrainInfoPerStation *> *directTrains = nullptr;       // list to store Direct Trains
  listOfObjects<int> *trainJourneyCode = nullptr;                     // list of JourneyCodes of trains departing from source
  listOfObjects<int> *itrJourneyCode = nullptr;

  // storing all journey codes of trains departing from source into trainJourneyCode
  while(srcToStations != nullptr){                 
    listOfObjects<TrainInfoPerStation *> *Trains = srcToStations->object->trains;
    while(Trains != nullptr){
      if(trainJourneyCode == nullptr){        // Inserting journey codes into the list trainJourneyCode
        trainJourneyCode = new listOfObjects<int>(Trains->object->journeyCode);
        itrJourneyCode = trainJourneyCode;
      }
      else{
        listOfObjects<int> *newJrnyCode = new listOfObjects<int>(Trains->object->journeyCode);
        listOfObjects<int> *temp = trainJourneyCode;
        while(temp->next != nullptr){
          temp = temp->next;
        }
        temp->next = newJrnyCode;
      }
      Trains = Trains->next;
    }
    srcToStations = srcToStations->next;
  }
  
  // Applying BFS for each journey Code that departs from the Source
  while(itrJourneyCode != nullptr){

    DynamicQueue<int> stnQueue;                             // Queue for BFS that stores current station's index
    stnQueue.push(stnNameToIndex.get(srcStnName)->value);   // push source station into queue
    while(!stnQueue.isEmpty()){           // loop through stations until stnQueue is empty

      int stn = stnQueue.delHead();       // get the head of stnQueue and delete it
      listOfObjects<StationConnectionInfo *> *stnAdj = adjacency[stn].toStations;     // adjacent toStations of stn 
      listOfObjects<StationConnectionInfo *> *stnAdj_temp = stnAdj;                   // copy of stnAdj for searching for journey Code
      while(stnAdj != nullptr){           // Loop through each station adjacent to the current station (stn)

        // list of trains departing to stations from adjacent station (stnAdj)
        listOfObjects<TrainInfoPerStation *> *toTrains = stnAdj->object->trains;
        // stations from which trains arriving at adjacent station (stnAdj)
        listOfObjects<StationConnectionInfo *> *stnAdjFrom = adjacency[stnAdj->object->adjacentStnIndex].fromStations;
        // list of trains arriving at adjacent station (stnAdj)
        listOfObjects<TrainInfoPerStation *> *fromTrains = stnAdjFrom->object->trains;
        // bools to check if current journey code is present in train lists
        bool foundinTo = false, foundinFrom = false;        
        TrainInfoPerStation *newDirectTrain = nullptr;      // new Direct Train
        TrainInfoPerStation *sameTrain = nullptr;           // same Train which arrives at stnAdj

        while(stnAdjFrom != nullptr){       // Check if train with current JourneyCode is arriving at adjacent station (stnAdj)
          fromTrains = stnAdjFrom->object->trains;
          sameTrain = find(itrJourneyCode->object,fromTrains);
          if(sameTrain != nullptr){
            foundinFrom = true;
            break;
          }
          stnAdjFrom = stnAdjFrom->next;
        }

        while(stnAdj_temp != nullptr){      // Check if train with current JourneyCode is departing from adjacent station (stnAdj)
          toTrains = stnAdj_temp->object->trains;
          newDirectTrain = find(itrJourneyCode->object,toTrains);
          if(newDirectTrain != nullptr){
            foundinTo = true;
            break;
          }
          stnAdj_temp = stnAdj_temp->next;
        }
        
        if(!foundinTo || !foundinFrom){       // If any one of them is false, continue
          stnAdj = stnAdj->next;
          continue;
        }

        if(stnAdj->object->adjacentStnIndex == stnNameToIndex.get(destStnName)->value){   // If stnAdj is the destination
          if(directTrains == nullptr){                                                    // insert new direct train into directTrains list
            directTrains = new listOfObjects<TrainInfoPerStation *>(newDirectTrain);
          }
          else{
            listOfObjects<TrainInfoPerStation *> *newTrain = new listOfObjects<TrainInfoPerStation *>(newDirectTrain);
            listOfObjects<TrainInfoPerStation *> *temp = directTrains;
            while(temp->next != nullptr){
              temp = temp->next;
            }
            temp->next = newTrain;
          }
          break;                                        // break out of loop
        }

        stnQueue.push(stnAdj->object->adjacentStnIndex);    // else push the stnAdj to the queue
        stnAdj = stnAdj->next;

      }
    }
    itrJourneyCode = itrJourneyCode->next;
  }

  if(directTrains != nullptr){      // Print all direct trains if there are direct trains
    printStationInfo(directTrains);
  }
  else{       // else print no direct trains available
    cout << "No direct journeys available\n";
  }
  return;
}
