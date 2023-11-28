#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#define RESET   "\033[0m"
#define RED     "\033[31m"

using namespace std;

template <typename T> class myQueue{
  public:
  listOfObjects<T> * journeys;// HEAD of the linked list
  listOfObjects<T> * tail; // TAIL of the linked list
  int size;

  myQueue(){
    journeys = nullptr; tail = nullptr; size = 0;
  }
  void add(T num){
    listOfObjects<T>* toAdd = new listOfObjects<T>(num);
    if(tail!=nullptr){// non-empty queue
      tail->next = toAdd;
      toAdd->prev = tail;
      tail = tail->next;
    }
    else{// empty queue
      journeys = toAdd;
      tail = toAdd;
    }
    // increase the size of vector by 1
    size++;
  }
  int remove(){
    int first;
    if(size==0){
      return -1; // cannot remove anymore
    }
    else if (size==1){
      first = journeys->object;
      journeys = nullptr;
      tail = nullptr;
    }
    else{
      first = journeys->object;
      journeys = journeys->next;
    }
    size--; // reduce the size of the queue
    return first;
  }
  bool find(T num){ // do not use find for other than T = int 
    listOfObjects<T> * iterator = journeys;
    bool found = false;
    while(iterator!=nullptr){
      if (iterator->object == num){
        found = true;
        break;
      }
      iterator = iterator->next;
    }

    return found;
  }
  T search(int journeyCode){ // search for journeyCode in the TrainInfoperstation linked list - correct journeycode will always be present
    listOfObjects<T> * iterator = journeys;
    while(iterator!=nullptr){
      if (iterator->object->journeyCode == journeyCode){ // found will always be true
        break;
      }
      iterator = iterator->next;
    }

    return iterator->object;
  }
  void print(){
    listOfObjects<T> * iterator = journeys;
    while(iterator!=nullptr){
      cout<<"{"<<iterator->object<<"}";
      iterator = iterator->next; 
    }
    cout<<endl;
  }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{  // Linked list of valid journeys
  listOfObjects<TrainInfoPerStation *> * validJourneys = new listOfObjects<TrainInfoPerStation *>(nullptr);
  // To get the starting station index 
  Entry<int>* startStationEntry = stnNameToIndex.get(srcStnName);
  int startIndex = startStationEntry->value;

  // To getthe index of the end station
  Entry<int>* endStationEntry = stnNameToIndex.get(destStnName);
  int endIndex = endStationEntry->value;

  // Access the pointer to the out linked list of trains from the start stations to check which nodes to traverse during the BFS
  listOfObjects<StationConnectionInfo *> *toList = new listOfObjects<StationConnectionInfo *>(nullptr);
  toList = adjacency[startIndex].toStations; // to store the linked list of Stations which can be reached from the starting station
  
  
  // to store the journey codes of all the trains from start station to end station
  myQueue<int> journeys;
  myQueue<int> q;
  myQueue<TrainInfoPerStation *> validTrainInfo;
  listOfObjects<TrainInfoPerStation *> * currTrainNode = nullptr;
  listOfObjects<TrainInfoPerStation *> * endTrainCheck = nullptr;

  while(toList!=nullptr){
      // to iterate through the list of trains
      if(toList->object->trains!=nullptr) {
      currTrainNode = toList->object->trains;

      while(currTrainNode!=nullptr){
          journeys.add(currTrainNode->object->journeyCode);

          // Traverse the from station list of the startstation to get the correct traininfoperstation object
          listOfObjects<TrainInfoPerStation *> *fromList = stationInfo[startIndex];
          listOfObjects<TrainInfoPerStation *> * fromTrainNode = fromList;
          while(fromTrainNode!=nullptr){
            fromTrainNode = fromTrainNode->next;
          }
          fromTrainNode = fromList;
          while(fromTrainNode!=nullptr){
            if (fromTrainNode->object->journeyCode == currTrainNode->object->journeyCode){
              validTrainInfo.add(fromTrainNode->object);
              break;
            }
            fromTrainNode = fromTrainNode->next;
          }


          currTrainNode = currTrainNode->next;
      }
    }
    toList = toList->next;
  }
  // INITIALIZING THE QUEUE FOR IMPLIMENTING BFS
  q.add(startIndex);
  while(q.size>0){
    // Dequeue the first elemnt in the Queue
    int currStationIndex = q.remove();

    toList = adjacency[currStationIndex].toStations;
    // To iterate through the adjacent nodes of the station 
    while(toList!=nullptr){
      if (stnNameToIndex.getKeyAtIndex(toList->object->adjacentStnIndex)==(destStnName)){ // If toList is end Station, then check the to list of the end station for valid trains
         endTrainCheck = toList->object->trains;

        while(endTrainCheck != nullptr){
          bool found = false;
          found = journeys.find(endTrainCheck->object->journeyCode);
          if(found){
            if(validJourneys->object==nullptr){// adding the first elemnt in the linked list
              validJourneys->object = validTrainInfo.search(endTrainCheck->object->journeyCode);
            }
            else{// adding the subsequent elements in the linked list
            // To check whether the journey is already inserted in the valid journey list
              listOfObjects<TrainInfoPerStation *> * iterator = validJourneys;
              bool ispresent = false;
              while(iterator->prev!=nullptr){
                if (iterator->object->journeyCode == endTrainCheck->object->journeyCode){
                  ispresent = true;
                  break;
                }
                iterator = iterator->prev;
              }
              if (!ispresent){                
                // Add a new node
                listOfObjects<TrainInfoPerStation *> * toAdd = new listOfObjects<TrainInfoPerStation *>(validTrainInfo.search(endTrainCheck->object->journeyCode));
                validJourneys->next = toAdd;
                toAdd->prev = validJourneys;
                validJourneys = validJourneys->next; // to maintain the pointer to the end of linked list 
              }
            }
          }
          endTrainCheck = endTrainCheck->next;
        }
        toList = toList->next; 
        continue;
      }
      else{
        currTrainNode = toList->object->trains;
        while(currTrainNode != nullptr){
          bool found = false;
          found =journeys.find(currTrainNode->object->journeyCode);
          
          if(found){
            q.add(toList->object->adjacentStnIndex); // Add the adjacent station if at least one valid train is going there
            break;
          }
          currTrainNode = currTrainNode->next;
        } 
        toList = toList->next; 
      }    
    }
  }
  // To traverse to the head of the linked list to pass it to the print function
  while(validJourneys->prev!=nullptr){
    validJourneys = validJourneys->prev;
  }
  // To print the possible list of journeys from A to B 
  if(validJourneys->object==nullptr){
    cout<<RED<<"NO DIRECT JOURNEY AVAILABLE!!"<<RESET<<endl;
  }
  else{
    printStationInfo(validJourneys);
  }
 return;
}

#endif
