#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  int src = stnNameToIndex.get(srcStnName)->value;
  int dstn = stnNameToIndex.get(destStnName)->value; 
  
  TrainInfoPerStation* T=new TrainInfoPerStation(0,0,0,0); 
  listOfObjects<TrainInfoPerStation *>* Journey1=new listOfObjects<TrainInfoPerStation *>(T);
  
  listOfObjects<StationConnectionInfo *>* Q;     
  Q = adjacency[src].toStations;
  
  while(Q!=NULL){
     StationConnectionInfo* T1 = new StationConnectionInfo(-10);
     listOfObjects<StationConnectionInfo *>* Qnew1=new listOfObjects<StationConnectionInfo *>(T1);  
     while(Q!=NULL){                                                                                
       if(Q->object->adjacentStnIndex==dstn)
        {                       
          listOfObjects<TrainInfoPerStation *>* Journey = Journey1;                                        
          while(Journey->next!=NULL)
              Journey = Journey->next;
          Journey->next = Q->object->trains; 
          Q = Q->next;   
          continue;
        } 
       listOfObjects<StationConnectionInfo *>* Q1;   
       Q1 = adjacency[Q->object->adjacentStnIndex].toStations;  
        if(Q1!=NULL){ 
              listOfObjects<StationConnectionInfo *>* Qnew=Qnew1; 	
              while(Qnew->next!=NULL)
                  Qnew = Qnew->next;
              Qnew->next = Q1;
             }	
      Q=Q->next;
     } 
   Q = Qnew1->next; 
  }
  
  //cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  if(Journey1->next==NULL)   
    {
      cout<<"No direct journeys available"<<endl;
      return;
     } 
  printStationInfo(Journey1->next);
  return;
}  
  
  //cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
 

#endif
