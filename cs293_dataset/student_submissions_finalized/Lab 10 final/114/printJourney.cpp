#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


// Queue for storing adjacent vertices into list and pop first element and add its adjacent vertices to the end of the list
class Queue{

  listOfObjects<StationConnectionInfo*>** adjancencyFiltered;

  // Track of index to insert next element
  int nextIndex;

  public:

  Queue() {


    adjancencyFiltered = new listOfObjects<StationConnectionInfo* >* [DICT_SIZE];

    for (int i = 0; i < DICT_SIZE; i++) {
      StationConnectionInfo* header = new StationConnectionInfo();
      adjancencyFiltered[i] = new listOfObjects<StationConnectionInfo* > (header);
    }

    nextIndex = 0;
  }

  void insert(listOfObjects<StationConnectionInfo* >* next) {
    adjancencyFiltered[nextIndex] = next;
    nextIndex++;
  }

  // Returns first element and removes it from the list
  listOfObjects<StationConnectionInfo* >* pop() {

    listOfObjects<StationConnectionInfo* >* temp = adjancencyFiltered[0];
    for (int i = 0; i < nextIndex; i++) {
      adjancencyFiltered[i] = adjancencyFiltered[i+1];
    }
    nextIndex--;

    return temp;
  }

  // Checks if Queue is empty or not
  bool isEmpty() {
    return nextIndex == 0;
  }

  // void traverse() {
  //   for (int i = 0; i < nextIndex; i++) {
      
  //     listOfObjects<StationConnectionInfo* >* save = adjancencyFiltered[i];
  //     listOfObjects<StationConnectionInfo* >* tempp = adjancencyFiltered[i];
  //     cout << "start" << endl;
  //     while (tempp != nullptr) {
  //       cout << tempp->object << endl;
  //       cout << tempp->object->adjacentStnIndex << endl;
  //       tempp = tempp->next;
  //     }
  //     adjancencyFiltered[i] = save;
  //   }
  // }

};

string days(int count) {
  if (count == 0) {
    return "Sunday";
  } else if (count == 1) {
    return "Monday";
  } else if (count == 2) {
    return "Tuesday";
  } else if (count == 3) {
    return "Wednesday";
  } else if (count == 4) {
    return "Thursday";
  } else if (count == 5) {
    return "Friday";
  } else if (count == 6) {
    return "Saturday";
  }
}

// void startRecurs(TrainInfoPerStation* Train, int nextIndex, StationAdjacencyList* adjacency, int stopCount, int stopOvers, int maxTransitTime, listOfObjects<StationConnectionInfo *> * tempnotchange) {

//   int jCde = Train->journeyCode;
//   StationConnectionInfo* trainsinfo = tempnotchange->object;
//   listOfObjects<TrainInfoPerStation *> * trains = trainsinfo->trains;
//   tempnotchange = tempnotchange->next;


//   while (trains != nullptr) {
//     if (trains->object->journeyCode == jCde) {
//       startRecurs(temptrains->object, nextIndex, lastTrain, index2, adjacency, stopCount + 1, stopOvers, maxTransitTime);
//     } else {
//       int arr = Train->arrTime;
//     }
//     trains = trains->next;
//   }

//   for (int i = 0; i < 7; i++) {
//     if (Train->daysOfWeek[i]) {

//     }
//   }  

// }

// void printRecurs(int index1, listOfObjects<StationConnectionInfo *> * tempnotchange, TrainInfoPerStation* lastTrain , int index2, StationAdjacencyList* adjacency, int stopOvers, int maxTransitTime) {
//   StationConnectionInfo* firstnext = tempnotchange->object;
//   StationAdjacencyList temp = adjacency[index1];
//   listOfObjects<StationConnectionInfo *> *to = temp.toStations;

//   while(to != nullptr){

//     listOfObjects<TrainInfoPerStation *> *temptrains = to->object->trains;
//     // listOfObjects<TrainInfoPerStation *> *tempsafe = to->object->trains;
    
//     // Station index of adjacent vertex
//     int nextindex = to->object->adjacentStnIndex;

//     if (nextindex == firstnext->adjacentStnIndex) {
//       while (temptrains != nullptr){
//         startRecurs(temptrains->object, nextIndex, lastTrain, index2, adjacency, 0, stopOvers, maxTransitTime, tempnotchange);
//         temptrains = temptrains->next;
//       }
//       break;
//     }
  
//   }

// }

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  // Stationindex of source
  int index1 = stnNameToIndex.get(srcStnName)->value;

  // Stationindex of destination
  int index2 = stnNameToIndex.get(destStnName)->value;

  // To track if printList variable has been created or not
  bool made = false;
  listOfObjects<TrainInfoPerStation *> * printList;

  Queue* queue = new Queue();

  // index of source
  StationAdjacencyList temp = adjacency[index1];
  // Adjacent vertices of source to next station rather than backwards
  listOfObjects<StationConnectionInfo *> *to = temp.toStations;

  // Traverse through all adjacent vertices
  while(to != nullptr){

    listOfObjects<TrainInfoPerStation *> *temp = to->object->trains;
    listOfObjects<TrainInfoPerStation *> *tempsafe = to->object->trains;
    
    // Station index of adjacent vertex
    int nextindex = to->object->adjacentStnIndex;

    if (nextindex == index2) {
      cout << "FOUND" << endl;
      
      // Iterating through all trains in linked list and print all trains
      while (temp != nullptr) {

        for (int i = 0; i < 7; i++) {
          if (temp->object->daysOfWeek[i] == true) {
            cout << GREEN << "Day: " << RESET << days(i) << endl;
            cout << BLUE << "JourneyCode: " << temp->object->journeyCode << RESET << " " << srcStnName << "->" << stnNameToIndex.getKeyAtIndex(index2) << endl;
            cout << GREEN << "Arr: " << RESET << temp->object->arrTime << GREEN << " Dep: " << RESET << temp->object->depTime << " " << endl << endl;
          }
        }

        temp = temp->next;
      }

      temp = tempsafe;

      while (temp != nullptr) {
        if (!made) {
          printList = new listOfObjects<TrainInfoPerStation *>(temp->object);
          made = true;
        } else {
          printList->next = new listOfObjects<TrainInfoPerStation *>(temp->object);
        }
        temp = temp->next;
      }
    } else {
      
      // If station not found, then we will add it to the queue
      listOfObjects<StationConnectionInfo* >* ins = new listOfObjects<StationConnectionInfo* >(to->object);
      queue->insert(ins);
    }

    to = to->next;
  }

  // First while loop is for looping through all adjacent vertices of source
  // Based on the first loop, we have added necessary vertices to the queue
  // Second while loop is for looping through all vertices in the queue
  // Only intersection of trains based on same JourneyCode will be added to "newInsert" and inserted to queue


  while (!queue->isEmpty()) {

      
      listOfObjects<StationConnectionInfo* >* temp = queue->pop();
      listOfObjects<StationConnectionInfo* >* tempnotchange = new listOfObjects<StationConnectionInfo* >(temp->object);
      listOfObjects<StationConnectionInfo* >* tempnotchangecopy = tempnotchange;
      listOfObjects<StationConnectionInfo* >* tempnotchange2 = new listOfObjects<StationConnectionInfo* >(temp->object);
      listOfObjects<StationConnectionInfo* >* tempnotchange2copy = tempnotchange2;

      // Iterate through all stations and get the last one in linkedlist
      StationConnectionInfo* tempcurrent = temp->object;

      temp = temp->next;

      while (temp != nullptr) {
        tempcurrent = temp->object;
        tempnotchange->next = new listOfObjects<StationConnectionInfo* >(temp->object);
        tempnotchange = tempnotchange->next;
        tempnotchange2->next = new listOfObjects<StationConnectionInfo* >(temp->object);
        tempnotchange2 = tempnotchange2->next;
        temp = temp->next;
      }

      tempnotchange = tempnotchangecopy;
      tempnotchange2 = tempnotchange2copy;


      //Adjacent
      // StationAdjacencyList temp3 = adjacency[temp->adjacentStnIndex];
      StationAdjacencyList temp3 = adjacency[tempcurrent->adjacentStnIndex];
      listOfObjects<StationConnectionInfo *> *to2 = temp3.toStations;

      StationConnectionInfo* trainstoadd = new StationConnectionInfo();

      while(to2 != nullptr){

        bool added = false;

      listOfObjects<TrainInfoPerStation *>* temp2 = tempcurrent->trains;

        // Trains of current station
        while (temp2 != nullptr) {

        listOfObjects<TrainInfoPerStation *> *temp4 = to2->object->trains;


          // temp4 => Trains of next station
          while(temp4 != nullptr) {

              int nextindex = to2->object->adjacentStnIndex;

              if (nextindex == index2) {
                cout << "FOUND" << endl;
                cout << index1 << " " << stnNameToIndex.getKeyAtIndex(index1) << endl;
                listOfObjects<StationConnectionInfo *> * joker = tempnotchange;
                while (joker != nullptr) {
                  cout << joker->object->adjacentStnIndex << " " << stnNameToIndex.getKeyAtIndex(joker->object->adjacentStnIndex) << endl;
                  joker = joker->next;
                }
                cout << index2 << " " << stnNameToIndex.getKeyAtIndex(index2) << endl;

                // printRecurs(index1, tempnotchange, temp4->object, index2, int maxTransitTime);

                if (!made) {
                  printList = new listOfObjects<TrainInfoPerStation *>(temp4->object);
                  made = true;
                } else {
                  printList->next = new listOfObjects<TrainInfoPerStation *>(temp4->object);
                }
                temp4 = temp4->next;
                continue;
              }

              listOfObjects<TrainInfoPerStation *> *temp5 = trainstoadd->trains;
              listOfObjects<TrainInfoPerStation *> *parenttemp5 = nullptr;

              while (temp5 != nullptr) {
                parenttemp5 = temp5;
                temp5 = temp5->next;
              }

              listOfObjects<TrainInfoPerStation *> * duplicatetemp = new listOfObjects<TrainInfoPerStation *>(temp2->object);

              if(parenttemp5 == nullptr) {
                trainstoadd->trains = duplicatetemp;
              } else {
                parenttemp5->next = duplicatetemp;
              }

              added = true;

            temp4 = temp4->next;
          }

          temp2 = temp2->next;
      }

        if(added) {

          listOfObjects<StationConnectionInfo *> * t = new listOfObjects<StationConnectionInfo *>(tempnotchange->object);
          trainstoadd->adjacentStnIndex = to2->object->adjacentStnIndex;

          listOfObjects<StationConnectionInfo *> * oldt = t;

          tempnotchange = tempnotchange->next;
          while (tempnotchange != nullptr){
            t->next = new listOfObjects<StationConnectionInfo *>(tempnotchange->object);
            tempnotchange = tempnotchange->next;
            t = t->next;
          }

          t->next = new listOfObjects<StationConnectionInfo *>(trainstoadd);

          t = oldt;

          queue->insert(t);

          // Updating tempnotchange and tempnotchange2
          tempnotchange = new listOfObjects<StationConnectionInfo *>(tempnotchange2->object);
          listOfObjects<StationConnectionInfo *>* saveback = tempnotchange;
          listOfObjects<StationConnectionInfo *>* saveback2 = tempnotchange2;
          
          tempnotchange2 = tempnotchange2->next;
          while (tempnotchange2 != nullptr) {
            tempnotchange->next = new listOfObjects<StationConnectionInfo *>(tempnotchange2->object);
            tempnotchange = tempnotchange->next;
            tempnotchange2 = tempnotchange2->next;
          }
          tempnotchange = saveback;
          tempnotchange2 = saveback2;


          trainstoadd = new StationConnectionInfo();
        }

        to2 = to2->next;
      }

  }

  if (!made) {
    cout << "No direct journeys available" << endl;
  } else {
    printStationInfo(printList);
  }

  
  return;
}

#endif
