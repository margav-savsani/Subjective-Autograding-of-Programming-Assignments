#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


using namespace std;

// Created a new class for the Queue in BFS
// Stores the Station indexes 
// and journey codes of individual train journeys
// Has a default constructor and a parametrized constructor
////////////////////////////////////////////////////////////
class stnNodes{
  public:
    int index;
    int jCode;
    int prevJrnyTime;
    int stopNo;
    // will have to add member variables for prevJrnyTime and stopNo
    stnNodes(){;}
    stnNodes(int idx, int code){
      this->index = idx;
      this->jCode = code;
    }
};

// Removes the first element in the queue
// Takes the head of the queue as input and returns the modified head with the deleted first element
/////////////////////////////////////////////////////////////////
listOfObjects<stnNodes> * Dequeue(listOfObjects<stnNodes> * head){
  // will have to change Deque implementation so as to not entirely remove the
  // vertex, but rather only move the head, and keep a processed pointer at the start
  if(head == nullptr || head->next == nullptr)
    return nullptr;
  listOfObjects<stnNodes> *previous = head;
  head = head->next;
  delete previous;
  head->prev = nullptr;
  return head;
}

//
// Create a new function called inQueue, which will check if the current station has already been processed or not
// bool inQueue(listOfObjects<stnNodes> * start, int code){
//   while(start != nullptr){
//     if(code == start->object->jCode)
//       return true;
//     start = start->next;
//   }
//   return false;
// }

// Adds new elements to the queue
// Takes in the tail of the queue, and the object to be inserted
// Returns the modified tail with the added Entry
/////////////////////////////////////////////////////////////////////////////
listOfObjects<stnNodes>* Enque(listOfObjects<stnNodes> * tail, stnNodes obj){
  if(tail == nullptr)
    tail = new listOfObjects<stnNodes>(obj);
  else{
    tail->next =  new listOfObjects<stnNodes>(obj);
    listOfObjects<stnNodes> *previous = tail;
    tail = tail->next;
    tail->prev = previous;
  }
  return tail;
}

//to enque journeys for printing
listOfObjects<TrainInfoPerStation*> *Enquejrny(listOfObjects<TrainInfoPerStation*> *stnInfoList, TrainInfoPerStation* jrny){

  listOfObjects<TrainInfoPerStation*> *temp = stnInfoList;
  if(temp == nullptr){
    // cout << jrny->journeyCode << endl;
    stnInfoList = new listOfObjects<TrainInfoPerStation *>(jrny);
  }
  else{
    while(temp->next != nullptr)
      temp = temp->next;
    temp->next = new listOfObjects<TrainInfoPerStation *>(jrny);
    temp->next->prev = temp;
  }
  // cout << stnInfoList->object->journeyCode << endl;
  return stnInfoList;
}
bool checkDayTT(TrainInfoPerStation* curr, TrainInfoPerStation* prev){
  return true;
}

listOfObjects<TrainInfoPerStation*> *Dequeuejrny(listOfObjects<TrainInfoPerStation*> *stnInfoList){
  listOfObjects<TrainInfoPerStation*> *temp = stnInfoList;
  if(temp == nullptr || temp->next == nullptr)
    return nullptr;
  else{
    while(temp->next != nullptr){
      temp = temp->next;
    }
    listOfObjects<TrainInfoPerStation*> *del = temp;
    temp = temp->prev;
    temp->next = nullptr;
    delete del;
    return stnInfoList;
  }
}


//to dequque names from the list
listOfObjects<int> *DequeueName(listOfObjects<int> *indexes){
  listOfObjects<int> *temp = indexes;
  if(temp == nullptr || temp->next == nullptr)
    return nullptr;
  else{
    while(temp->next != nullptr){
      temp = temp->next;
    }
    listOfObjects<int> *del = temp;
    temp = temp->prev;
    temp->next = nullptr;
    delete del;
    return indexes;
  }
}

void printStnInfo(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<int> *nameIndex, Dictionary<int> stnNameToIndex, int dest)
{
  listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  // Expanding information in stnInfoList to get a list of train info
  // in which each element of the list refers to a single day of the
  // week.  This is the list that has to be finally sorted using
  // quicksort.

  currList = stnInfoList;
  while(currList->next != nullptr)
    currList = currList->next;
  expandedList = nullptr;
  int listLength = 0;
  while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
      // Make as many copies of currInfo as the total count of days in the week
      // when this train runs from/to this station
      int jCode = currInfo->journeyCode;
      int stSeq = currInfo->stopSeq;
      int arrTime = currInfo->arrTime;
      int depTime = currInfo->depTime;
    
      for (int i=0; i < 7; i++) {
	if (currInfo->daysOfWeek[i]) {
	  TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
	  if (newExpandedElement == nullptr) {
	    cerr << "Memory allocation failure." << endl;
	    continue;
	  }
	  newExpandedElement->setDayOfWeek(i);

	  listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
	  if (newExpandedListElement == nullptr) {
	    cerr << "Memory allocation failure." << endl;
	    continue;
	  }

	  if (expandedList == nullptr) {
	    expandedList = newExpandedListElement;
	  }
	  else {
	    newExpandedListElement->next = expandedList;
	    expandedList->prev = newExpandedListElement;
	    expandedList = newExpandedListElement;
	  }
	  listLength++;
	}
      }
    }
    currList = currList->prev;
  }

  int prevjrnyCode = 0;

  currList = expandedList;
  cout << "Journey" << endl;
  while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
      if(prevjrnyCode != currInfo->journeyCode){
        cout << "From: " << stnNameToIndex.getKeyAtIndex(nameIndex->object) << " To: " << stnNameToIndex.getKeyAtIndex(nameIndex->next->object) << endl;
        if(nameIndex->next->object == dest){
          // cout << "Testing" << endl;
          nameIndex = nameIndex->next->next;
        }
        else
          nameIndex = nameIndex->next;
        prevjrnyCode = currInfo->journeyCode;
      }
      cout << GREEN << "Day(s): " << RESET;
      for (int i=0; i<7; i++) {
	if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1) {
	cout << "Starts";
      }
      else {
	cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1) {
	cout << "Ends";
      }
      else {
	cout << currInfo->depTime;
      }
      cout << endl;
    }
    currList = currList->next;
  }
  cout << endl;
}

void dfs(listOfObjects<StationConnectionInfo *> *curr, TrainInfoPerStation* prevjrny,int src, int dest, listOfObjects<TrainInfoPerStation *> *stnInfoList, int maxSO, int maxTT, StationAdjacencyList* adjacency, listOfObjects<TrainInfoPerStation *> **stationInfo, Dictionary<int> stnNameToIndex){
  static int count = 0;
  static listOfObjects<int> *nameIndex = new listOfObjects<int>(src);
  // if(count < maxSO){
  while(curr != nullptr){
    listOfObjects<TrainInfoPerStation*> *trains = curr->object->trains;
    while(trains != nullptr){
      if(curr->object->adjacentStnIndex == dest){
        //check for checkDayTT
        while(trains != nullptr){
          listOfObjects<TrainInfoPerStation *> *stnInfo = stationInfo[curr->object->adjacentStnIndex];
          while(stnInfo != nullptr){
            if(stnInfo->object->journeyCode == trains->object->journeyCode)
              stnInfoList = Enquejrny(stnInfoList, stnInfo->object);
            
            stnInfo = stnInfo->next;
          }
          listOfObjects<int> *temp = nameIndex;
          if(temp == nullptr)
            nameIndex = new listOfObjects<int>(src);
          temp = nameIndex;
          while(temp->next != nullptr)
            temp = temp->next;
          temp->next = new listOfObjects<int>(curr->object->adjacentStnIndex);
          temp->next->prev = temp;
          temp = temp->next;
          temp->next = new listOfObjects<int>(src);
          temp->next->prev = temp;
          trains = trains->next;
        }
        printStnInfo(stnInfoList, nameIndex, stnNameToIndex, dest);
        nameIndex = DequeueName(nameIndex);
        nameIndex = DequeueName(nameIndex);
        // nameIndex = DequeueName(nameIndex);
        // while(nameIndex != nullptr)
        //   nameIndex = DequeueName(nameIndex);
        break;
      }
      // first recursion
      else if(prevjrny == nullptr){

        if(nameIndex == nullptr)
            nameIndex = new listOfObjects<int>(src);

        listOfObjects<TrainInfoPerStation *> *stnInfo = stationInfo[src];
        while(stnInfo != nullptr){
          if(stnInfo->object->journeyCode == trains->object->journeyCode){
            stnInfoList = Enquejrny(stnInfoList, stnInfo->object);
          }
          
          stnInfo = stnInfo->next;
        }

        stnInfo = stationInfo[curr->object->adjacentStnIndex];
        while(stnInfo != nullptr){
          if(stnInfo->object->journeyCode == trains->object->journeyCode){
            stnInfoList = Enquejrny(stnInfoList, stnInfo->object);
          }
          
          stnInfo = stnInfo->next;
        }
        // stnInfoList = Enquejrny(stnInfoList, trains->object);

        listOfObjects<int> *temp = nameIndex;
        while(temp->next != nullptr)
          temp = temp->next;
        temp->next = new listOfObjects<int>(curr->object->adjacentStnIndex);
        temp->next->prev = temp;

        dfs(adjacency[curr->object->adjacentStnIndex].toStations, trains->object,src,  dest,stnInfoList, maxSO, maxTT, adjacency,stationInfo, stnNameToIndex);
        stnInfoList = Dequeuejrny(stnInfoList);
        // nameIndex = DequeueName(nameIndex);
      }
      else if(count < maxSO){
        if(prevjrny->journeyCode == trains->object->journeyCode){
          listOfObjects<TrainInfoPerStation *> *stnInfo = stationInfo[curr->object->adjacentStnIndex];
        while(stnInfo != nullptr){
          if(stnInfo->object->journeyCode == trains->object->journeyCode){
              stnInfoList = Enquejrny(stnInfoList, stnInfo->object);
          }
          
          stnInfo = stnInfo->next;
        }
          // stnInfoList = Enquejrny(stnInfoList, trains->object);
          dfs(adjacency[curr->object->adjacentStnIndex].toStations, trains->object, src, dest,stnInfoList, maxSO, maxTT, adjacency,stationInfo, stnNameToIndex);
          stnInfoList = Dequeuejrny(stnInfoList);
          // nameIndex = DequeueName(nameIndex);
        }
        else{
          if(checkDayTT(trains->object, prevjrny)){
            listOfObjects<TrainInfoPerStation *> *stnInfo = stationInfo[curr->object->adjacentStnIndex];
            while(stnInfo != nullptr){
              if(stnInfo->object->journeyCode == trains->object->journeyCode){
                stnInfoList = Enquejrny(stnInfoList, stnInfo->object);
              }
              stnInfo = stnInfo->next;
            }
            // stnInfoList = Enquejrny(stnInfoList, trains->object);
            count++;

            listOfObjects<int> *temp = nameIndex;
            if(temp == nullptr)
              nameIndex = new listOfObjects<int>(src);
            temp = nameIndex;
            while(temp->next != nullptr)
              temp = temp->next;
            temp->next = new listOfObjects<int>(curr->object->adjacentStnIndex);
            temp->next->prev = temp;
        

            dfs(adjacency[curr->object->adjacentStnIndex].toStations, trains->object, src, dest,stnInfoList, maxSO, maxTT, adjacency, stationInfo ,stnNameToIndex);
            count--;
            stnInfoList = Dequeuejrny(stnInfoList);
            // nameIndex = DequeueName(nameIndex);
          }
        }
      }
      trains = trains->next;
    }
    curr = curr->next;
  }
  // }
  // cout << "Count value = " << count << endl;
  return;
}


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  int src = stnNameToIndex.hashValue(srcStnName), dest = stnNameToIndex.hashValue(destStnName);
  listOfObjects<TrainInfoPerStation *> *stnInfoList = nullptr, *ptr = nullptr;
  listOfObjects<stnNodes> *head = nullptr, *tail = nullptr, *start = nullptr;

  listOfObjects<stnNodes *> *visited = nullptr;
  listOfObjects<int> *jCodes = nullptr;
  stnNodes sourceInfo(src, -1);
  head = Enque(head, sourceInfo);
  tail = head;
  start = head;

  listOfObjects<StationConnectionInfo *> *curr = adjacency[head->object.index].toStations;
  dfs(curr, nullptr, src, dest, nullptr, maxStopOvers, maxTransitTime, adjacency, stationInfo,stnNameToIndex);

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
