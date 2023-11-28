#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "planner.h"

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
// insert your code here

  //result pointer will point to the trains which run direct between source
  //and destination station.
  listOfObjects<TrainInfoPerStation *> *result = nullptr;

  //this will be true if atleast one journey is found between the stations
  bool FoundJourney = false;

  //index of source and destination stations
  int srcStnIndex = stnNameToIndex.get(srcStnName)->value;
  int destStnIndex = stnNameToIndex.get(destStnName)->value;

  if(srcStnIndex == destStnIndex){
    cout<<"BOTH SOURCE AND DESTINATION STATIONS ARE SAME."<<endl;
    return;
  }
  //Pointer to all the trains starting from the source station
  listOfObjects<TrainInfoPerStation *> *trainFromSrc = stationInfo[srcStnIndex];

  //Iterate over all the trains from the source station and
  //do BFS to find if a trian is direct or not
  while(trainFromSrc!=nullptr){
    //Journey code of this trian
    int JC = trainFromSrc->object->journeyCode;
    int numOfSteps = 0;
    //this queue is same as the queue which is used is BFS
    listOfObjects<int>* queue = new listOfObjects<int>(srcStnIndex);

    //path has all the station indices which are in path
    //from the source to destination station including both
    listOfObjects<int>* path = new listOfObjects<int>(srcStnIndex);

    //array to keep track if a station is visited as in BFS
    bool visited[DICT_SIZE];

    //Initializing the visited for all entries to false
    for(int i=0; i<DICT_SIZE; i++){
      visited[i]=0;
    }

    //The source station is visited
    visited[srcStnIndex] = true;

    //Iterate while the queue is not empty as in BFS
    while(queue!=nullptr){

      //front element of the queue which is front station
      int s = queue->object;

      //list containing the adjacent stations of the front station
      listOfObjects<StationConnectionInfo *>* adj  = adjacency[s].toStations;

      //popping the front station from the queue
      queue = queue->next;

      //this will be true if the train is found if the trains of the adjacent station
      bool found = false;

      //iterating over all the adjacent stations of the front station
      while(adj!=nullptr){

        //If we have reached the destination station then we don't need to go further,
        //we update the path list and break off the loop
        if(adj->object->adjacentStnIndex==destStnIndex && numOfSteps == maxStopOvers){

          //updating the path list
          listOfObjects<int>* tempPath1 = path;
          while(path->next!=nullptr){
            path=path->next;
          }
          path->next=new listOfObjects<int>(destStnIndex);
          path = tempPath1;
          break;
        }

        //if the adjacent station is not visited yet we check for that station
        //otherwise we leave it as is
        if(!visited[adj->object->adjacentStnIndex]){
          //visiting the station
          visited[adj->object->adjacentStnIndex]=true;
          //list that contains all the trains from this adjacent station
          listOfObjects<TrainInfoPerStation *> *trainsStn = adj->object->trains;

          //iterating over all the trains from this station
          while(trainsStn!=nullptr){
            //if journey code of this train matches with this train then we
            //update the path list and queue then break off the loops and go to next station in the queue
            if(trainsStn->object->journeyCode==JC){
              numOfSteps++;
              //updating the path list
              listOfObjects<int>* tempPath2 = path;
              while(path->next!=nullptr){
                path=path->next;
              }
              path->next=new listOfObjects<int>(adj->object->adjacentStnIndex);
              path = tempPath2;

              //updating the queue
              if(queue==nullptr){
                queue=new listOfObjects<int>(adj->object->adjacentStnIndex);
              }else{
                listOfObjects<int>* tempQueue = queue;
                while(queue->next!=nullptr){
                  queue=queue->next;
                }
                queue->next=new listOfObjects<int>(adj->object->adjacentStnIndex);
                queue = tempQueue;
              }
              
              //we have found the train
              found = true;
              break;
            }
            trainsStn=trainsStn->next;
          }
          if(found){
            break;
          }
        }
        adj = adj->next;
      }
    }

    //checking if the last station in the path list if destination station or not
    //if it is the destination station then we have found the direct path
    //between source and destination station 
    listOfObjects<int>* tempPath3 = path;
    while(tempPath3->next!=nullptr){
      tempPath3=tempPath3->next;
    }

    //if direct path then updating the result list
    if(tempPath3->object==destStnIndex){
      //updating the result list
      if(result==nullptr){
        result = new listOfObjects<TrainInfoPerStation *>(trainFromSrc->object);
      }else{
        listOfObjects<TrainInfoPerStation *>* resultTemp = result;
        while(result->next!=nullptr){
          result=result->next;
        }
        result->next = new listOfObjects<TrainInfoPerStation *>(trainFromSrc->object);
        result = resultTemp;
      }
      FoundJourney = true;
    }
    trainFromSrc = trainFromSrc->next;
  }
  //if no direct journey found
  if(!FoundJourney){
    cout<<"NO DIRECT JOURNEY AVAILABLE"<<endl;
  }else{
    //else print the direct list
    printStationInfo(result);
  }
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  return;
}

#endif
