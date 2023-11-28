#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

//Implementation for a node of the Queue
template<class T>
struct ListNode{
  
  T object;
  listOfObjects<TrainInfoPerStation *> prevJrnys = listOfObjects<TrainInfoPerStation *> (nullptr);
  int numJrnys;
  listOfObjects<string> changeStations = listOfObjects<string>("");
  ListNode<T> * next;
  ListNode<T> * prev;
  //int prevJrnyCode;

  
  //Constructor for a queue
  ListNode(){
    this->next = this->prev = nullptr;

  }
  //Constructor for a queue
  ListNode(T obj, listOfObjects<TrainInfoPerStation *> &prevJrnyst){

    this->prevJrnys.object = prevJrnyst.object;
    this->prevJrnys.next = prevJrnyst.next;
    this->prevJrnys.prev = prevJrnyst.prev;
    
    this->object = obj;
    this->next = this->prev = nullptr;
    this->numJrnys = 0;

  }

};

template<class T>
//Implementation of a queue.
class Queue{
  
  
  public:
    int size; //size of the queue
    ListNode<T> * head; //head of the queue.
    ListNode<T> * tail; //tail of the queue.

    //Constructor
    Queue(){
      this->size = 0;
      this->head = this->tail = nullptr;

    }

    //Adding an element to the queue
    void push(T obj, listOfObjects<TrainInfoPerStation *> prevJrnys){
      ListNode<T>* newNode = new ListNode<T>(obj, prevJrnys);

      if(tail == nullptr){
         head = tail =  newNode;

      } else {
        tail->next = newNode;
        newNode->prev = tail;
        
        tail = tail->next;
      }

      this->size++;

    }
    //Deleting the element of the queue
    ListNode<T>* pop(){

      if (head == nullptr) {
        return NULL;
      } else if (this->size == 1){
        ListNode<T>* toDelete = head;
        size--;
        head = tail = nullptr;
        return toDelete;
      } else {

        ListNode<T>* toDelete = head;
        head = head->next;
        head->prev = nullptr;
        this->size--;
        return toDelete;
      }
    }

    
};




  
void Planner :: printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp



    //List to store all the journeys.
  listOfObjects<listOfObjects<TrainInfoPerStation *>*>* journeys = nullptr;
  listOfObjects<listOfObjects<string>*>* changeOvers = nullptr;
  
  

  //Hash values of the source and destination station.
  int srcHash = stnNameToIndex.hashValue(srcStnName);
  int destHash = stnNameToIndex.hashValue(destStnName);


  
  //currptr of the adjacency list.
  listOfObjects<StationConnectionInfo *> *  currptr = adjacency[srcHash].toStations;

  Queue<StationConnectionInfo*>* bfsList = new Queue<StationConnectionInfo*>();
  
  //Add all the journeys from the source into the queue.
  while (currptr) {
    //for each station in adjacency list.
    listOfObjects<TrainInfoPerStation *> * currInfo = currptr->object->trains;
    while (currInfo != nullptr){
      //add each journey to each adjacent station.
      bfsList->push(currptr->object, currInfo->object);
      currInfo = currInfo->next;
    }
    currptr = currptr->next;
  }
  //Process all the elements of the queue.
  while(bfsList->size != 0){
    //if adjacent station is the destination, print the journey corresponding with the source.
    if (bfsList->head->object->adjacentStnIndex == destHash){
      listOfObjects<TrainInfoPerStation *> * currInfo = bfsList->head->object->trains;
      while(currInfo != nullptr){
        if (currInfo->object->journeyCode == bfsList->head->prevJrnys.object->journeyCode ){
          //add journeys into the listOfObjects.
          if (!journeys){
            //if list of Objects is empty then define a new one.
            journeys = new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(&bfsList->head->prevJrnys);

          } else {
            //add the elements in the list of Journeys.
            listOfObjects<listOfObjects<TrainInfoPerStation*>*>* newNode = new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(&(bfsList->head->prevJrnys));
            newNode->next = journeys;
            journeys->prev = newNode;

            journeys = newNode;
            
          }

          if(!changeOvers){
            changeOvers = new listOfObjects<listOfObjects<string>*>(&bfsList->head->changeStations);
          } else {
            listOfObjects<listOfObjects<string>*>* newChange = new listOfObjects<listOfObjects<string>*>(&bfsList->head->changeStations);

            newChange->next = changeOvers;
            changeOvers->prev = newChange;
            changeOvers = newChange;

          }
        }
        currInfo = currInfo->next;
      }
      //pop the first element.
      bfsList->pop();


    } else {
      //if the destination doesnt match, advance to the next node corresponding to the journey which took you to the currentNode.
      listOfObjects<StationConnectionInfo*>* currptr = adjacency[bfsList->head->object->adjacentStnIndex].toStations;
      //find all the matching stations.
      while(currptr){
        listOfObjects<TrainInfoPerStation *> * currInfo = currptr->object->trains;
        while (currInfo){
          if (currInfo->object->journeyCode == bfsList->head->prevJrnys.object->journeyCode){
            bfsList->push(currptr->object, bfsList->head->prevJrnys);
            bfsList->tail->prevJrnys.object = currInfo->object;
            bfsList->tail->changeStations.object = bfsList->head->changeStations.object;
            bfsList->tail->changeStations.next = bfsList->head->changeStations.next;
            bfsList->tail->changeStations.prev = bfsList->head->changeStations.prev;

          } else if(bfsList->head->numJrnys < maxStopOvers){

            listOfObjects<TrainInfoPerStation *>* prevCurrInfo = stationInfo[bfsList->head->object->adjacentStnIndex];

            while(prevCurrInfo){
              if (prevCurrInfo->object->journeyCode == bfsList->head->prevJrnys.object->journeyCode){
                break;
              } 

              prevCurrInfo = prevCurrInfo->next; 
            }

            

            float newarrTime  = prevCurrInfo->object->arrTime / 100
                                +  (prevCurrInfo->object->arrTime % 100) * 1.0 / 60
                                ;
            
            float newdepTime  = currInfo->object->arrTime / 100
                                +(currInfo->object->arrTime % 100) * 1.0/ 60
                                ;

            if (newdepTime - newarrTime >= 0 && newdepTime - newarrTime <= maxTransitTime){

              bfsList->push(currptr->object, bfsList->head->prevJrnys);
              listOfObjects<TrainInfoPerStation *> * newJrny = new listOfObjects<TrainInfoPerStation *>(bfsList->tail->prevJrnys);
              newJrny->next = bfsList->tail->prevJrnys.next;
              if(bfsList->tail->prevJrnys.next)
                bfsList->tail->prevJrnys.next->prev = newJrny;
              newJrny->prev = &bfsList->tail->prevJrnys;
              bfsList->tail->prevJrnys.object = currInfo->object;
              bfsList->tail->prevJrnys.next = newJrny;
              bfsList->tail->numJrnys++;



              bfsList->tail->changeStations.object = bfsList->head->changeStations.object;
              bfsList->tail->changeStations.next = bfsList->head->changeStations.next;
              bfsList->tail->changeStations.prev = bfsList->head->changeStations.prev;

              listOfObjects<string> * newName = new listOfObjects<string>(bfsList->head->changeStations.object);
              newName->next = bfsList->tail->changeStations.next;
              newName->prev = &bfsList->tail->changeStations;
              if(bfsList->tail->changeStations.next)
                bfsList->tail->changeStations.next->prev = newName;
              bfsList->tail->changeStations.object = stnNameToIndex.getKeyAtIndex(bfsList->head->object->adjacentStnIndex);
              
              
            }
          }
          currInfo = currInfo->next;
        }
        currptr = currptr->next;
      }
      //pop the first elemnt of the queue.
      bfsList->pop();


    }
    //print all the journeys.
    
  }
  

  if(journeys){
      int jrnyNum = 1;
      while(journeys){
          
          bool comdaysofWeek[] = {true, true, true, true, true, true, true};
          listOfObjects<TrainInfoPerStation *> * currNode  = journeys->object;
          while(currNode){
           for (int i  = 0; i < 7; i++){
              comdaysofWeek[i] = comdaysofWeek[i] && currNode->object->daysOfWeek[i];
           } 

           currNode = currNode->next;
          }

          
          cout << "Journeys available on : ";
          string days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

          for(int i = 0; i < 7; i++){
            if (comdaysofWeek[i]) cout << days[i] << " ";
          }

          

          currNode = journeys->object;
          while(currNode->next){
            currNode = currNode->next;
          }
          listOfObjects<string> * currName = changeOvers->object;
          while(currName->next){
            currName = currName->next;
          }

          
          cout << "\n";
          cout << "****************JOURNEY " << jrnyNum << "*************\n";
          int count = 0;
          while(currNode){
            
            if (count == 0){
              cout << "JourneyCode: \t" << currNode->object->journeyCode << endl;
              cout << "ArrTime: \t" << currNode->object->arrTime << endl;
              cout << "DeptTime: \t" << currNode->object->depTime << endl; 
              cout << endl;

            } else {
              cout << "TRAIN CHANGE AT:" << (currName->object) <<endl << endl;
              cout << "JourneyCode: \t" << currNode->object->journeyCode << endl;
              cout << "ArrTime: \t" << currNode->object->arrTime << endl;
              cout << "DeptTime: \t" << currNode->object->depTime << endl; 
              cout << endl;
              currName = currName->prev;
            }
            currNode = currNode->prev;

            count++;
          }

          jrnyNum++;
          journeys = journeys->next;
          changeOvers = changeOvers->next;
      }
    } else { 
        cout << "No journeys available" << endl;
    }
  

  return;
  
  
  
}

#endif
