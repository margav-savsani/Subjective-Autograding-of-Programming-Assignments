#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <set>
using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  Entry <int>* stnEntry = stnNameToIndex.get(srcStnName);  //get the entry corresponding to string in dictionary
  int stnIndex = stnEntry->value; // get dict index of source station
 
  Entry <int>*deststnEntry = stnNameToIndex.get(destStnName);  //get the entry corresponding to string in dictionary
  int  deststnIndex = deststnEntry->value; // get dict index of dest station
  
  bool visited[100000]={false}; // array storing if station is visited
  int num=0; // total number of incoming routes to dest station
  int count=0; // number of routes to dest station traversed
  int rec=0; // level number of station in any call
  bool found = false; // if we have found a successful path 
  StationConnectionInfo ** pred = new StationConnectionInfo* [100000] ; // to store predessors/parent encountered in BFS

  listOfObjects<StationConnectionInfo *> *toList = adjacency[stnIndex].toStations; // base case
  if (toList==nullptr) 
  { cout<<"NO DIRECT JOURNEYS"; // if the source station has no outgoing routes
    return ;                      
  }
  
  listOfObjects<StationConnectionInfo *> *fromList = adjacency[deststnIndex].fromStations;
  while(fromList != nullptr){          // to find how many incoming routes does dest station have
    num ++;                            // done this by traversing the from list of the dest station
    fromList=fromList->next;
  }

  StationConnectionInfo * parent =nullptr;   // station that has just been removed from queue
                                             // that is we are currently storing its neighbours
  listOfObjects<TrainInfoPerStation *> *final=nullptr;  // final list that has to be printed out
  listOfObjects<StationConnectionInfo *> *queue = new listOfObjects<StationConnectionInfo *>(toList->object)  ;
  // queue of the standard BFS for storing and removing stations

    while(queue != nullptr )  // chack if the queue is empty
    { 
      if (rec !=0){  // otherwise case where we are checking neighbours of source station
          toList = adjacency[queue->object->adjacentStnIndex].toStations;  
          parent =queue->object;  // dequeue the queue from front and store the station in parent 
          queue =queue ->next;}
        
      while(toList!=nullptr )
      {    // just to store that we are done with the first neighbour of the source station
          rec ++; // because we have already queue with it
          if (!visited[toList->object->adjacentStnIndex])  // check if station not already visited
          {   visited[toList->object->adjacentStnIndex] = true;   // change value of visited to true
              pred[toList->object->adjacentStnIndex] = parent;  // update the predecessor value of the station

              if (toList->object->adjacentStnIndex == deststnIndex){ // we got the destination station 
                  visited[toList->object->adjacentStnIndex] = false; // because there can be multiple routes so we want to check it again
                  count ++;
                  if( pred[toList->object->adjacentStnIndex]!=nullptr){
                      listOfObjects<TrainInfoPerStation *> *train2 = toList->object->trains;  // linked list of the trains through that station
                      listOfObjects<TrainInfoPerStation *> *train1 = pred[toList->object->adjacentStnIndex]->trains;
                      StationConnectionInfo* predecessor = pred[toList->object->adjacentStnIndex];
                      set<int> s1;   // initialise sets to store common journey codes of our station in path
                      set<int> s2;
                      set<TrainInfoPerStation *> s3;  // initialise sets to store our station trains in path
                    
                      while(train1 != nullptr){  // firstly traverse the dest station and its predecessor 
                          while(train2!=nullptr){//to find common jouney codes
                      
                              if (train1->object->journeyCode == train2->object->journeyCode)
                              {
                                  s1.insert (train2->object->journeyCode); // if common found add that to set1 
                                  s3.insert (train1->object);
                                  s3.insert (train2->object);} // add corresponding station trains in set3
                              train2 = train2->next;
                          }
                      train2 =toList->object->trains; // regular traversal updation
                      train1 = train1->next;
                    }

                    predecessor= pred[predecessor->adjacentStnIndex]; // now we have a set of journey codes from where 
                    while(predecessor!=nullptr){             // we can find if direct path possible 
                        train1= predecessor->trains;        // check for the common journey codes with the predecessor stations
                        while(train1 !=nullptr){
                          if (s1.count(train1->object->journeyCode))
                              {s2.insert(train1->object->journeyCode); // decrementent the size of the set 
                              s3.insert (train1->object);}              // by storing in new set2 
                          train1=train1->next;                          // and then reassigning set 1 with set2
                        }
                        s1=s2;
                        s2.clear();
                        predecessor= pred[predecessor->adjacentStnIndex];
                    }
                
                    train1=stationInfo[stnIndex];           // defined in dictionary.h
                    while(train1 !=nullptr){                // for the source station we have to do it differently 
                        if (s1.count(train1->object->journeyCode))  // as we can not access the trains going out from it 
                            {s2.insert(train1->object->journeyCode); // using the adjacency list                          
                            s3.insert (train1->object);}
                        train1=train1->next;
                    }
                    s1=s2;
                      
                    if (!s1.empty()){     // if set is not empty 
                      found =true;        // then we have definately found a direct path from source to dest
                      for (auto it = s1.begin(); it!= s1.end();++it){  // there can be multiple direct paths
                          for (auto lit = s3.begin(); lit!= s3.end();++lit){
                                
                              if ((*lit)->journeyCode == *it){   // store the valid station trains in the final liNked list
                                    listOfObjects<TrainInfoPerStation *> *temp = new listOfObjects<TrainInfoPerStation *>(*lit);
                                    temp->object= *lit;
                                    temp ->next = final;
                                    final= temp;
                              }
                          }    
                          printStationInfo(final);  // print the linked list as mentioned in the problem statement
                          final= nullptr;  // updation done for any next iteration
                      }
                    }
                    
                    if(count == num)  //if all incoming networks are discovered then break out fro the while loop
                      {break;}
                }
                else {found= true;   
                    listOfObjects<TrainInfoPerStation *> *train2 = stationInfo[stnIndex];  // linked list of the trains through that station
                    listOfObjects<TrainInfoPerStation *> *train1 =stationInfo[deststnIndex] ;
                    while(train1 != nullptr){  // firstly traverse the dest station and its predecessor 
                          while(train2!=nullptr){//to find common jouney codes
                              if (train1->object->journeyCode == train2->object->journeyCode)
                              {
                                  listOfObjects<TrainInfoPerStation *> *temp1 = new listOfObjects<TrainInfoPerStation *>(train1->object);
                                    temp1->object= train1->object;
                                    temp1 ->next = final;
                                    final= temp1;       // store the valid station trains in the final liNked list
                                   listOfObjects<TrainInfoPerStation *> *temp2 = new listOfObjects<TrainInfoPerStation *>(train2->object);
                                    temp2->object= train2->object;
                                    temp2 ->next = final;
                                    final= temp2;      // store the valid station trains in the final liNked list
                                }               
                              train2 = train2->next;
                          }
                          train2 =stationInfo[stnIndex]; // regular traversal updation
                          train1 = train1->next;}
                    printStationInfo(final); // case when source and dest are just adjacent to each other
                    final = nullptr;}      // that is have no intermediate stations
              }                                                             

              if (rec!=1){                  // to update the queue with all the neighbours of a station
                  listOfObjects<StationConnectionInfo *> *add= new listOfObjects<StationConnectionInfo *>(toList->object) ;
                  if(queue!=nullptr){      // add the station at the last of the queue
                      listOfObjects<StationConnectionInfo *> *temp  = queue;
                      while (queue->next!=nullptr) 
                      {queue= queue->next;}          // will have to traverse the queue once to get to the end               
                        queue->next = add; 
                        queue = temp;}
                        else queue = add;
              }
          }
          toList= toList->next;  // traversal for all the stations in the to list of the source station
      }
      if(count == num)  //if all incoming networks are discovered then break out fro the while loop
        {break;}
    }
   if (found==false)  // if we havenot found any direct paths
    {cout<<"NO DIRECT JOURNEYS";}

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
