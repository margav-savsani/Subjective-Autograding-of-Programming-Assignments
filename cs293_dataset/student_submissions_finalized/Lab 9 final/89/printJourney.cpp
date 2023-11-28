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
                   // creating new list of objects of type StationConnectionInfo*, an object will be added to this list only when 
                   // there is atleast one journey from current station(Q) to next-station(Q1) whose journey code matches with 
                   // one of the journeycode of journeys from prev-station to current station(Q) 
     listOfObjects<StationConnectionInfo *>* Qnew1=new listOfObjects<StationConnectionInfo *>(T1);  
     while(Q!=NULL){                                                                                
       if(Q->object->adjacentStnIndex==dstn)
        {                        // if the current station is the destination station we will add the list of trains to list Journey
          listOfObjects<TrainInfoPerStation *>* Journey = Journey1;                                        
          while(Journey->next!=NULL)
              Journey = Journey->next;
          Journey->next = Q->object->trains; 
          Q = Q->next;   
          continue;
        } 
       listOfObjects<StationConnectionInfo *>* Q1;   //Q1 is the list of StationConnectionInfo pointers of next-stations of current station(Q)
       Q1 = adjacency[Q->object->adjacentStnIndex].toStations;  
       while(Q1!=NULL){
          TrainInfoPerStation* T2=new TrainInfoPerStation(0,0,0,0); 
              // New1 is the new list of objects of type TrainInfoPerStation *, we add an object into this list each time we find the journey 
              // from current station(Q) to the next-station(Q1) whose journeycode matches with one of the journeycode of journeys from  
              // prev-station to current station(Q) 
          listOfObjects<TrainInfoPerStation *>* New1=new listOfObjects<TrainInfoPerStation *> (T2);
          listOfObjects<TrainInfoPerStation *>* to=Q1->object->trains;
          listOfObjects<TrainInfoPerStation *>* from;
          int a = 0;
          while(to!=NULL){
             from=Q->object->trains;
             while(from!=NULL){
                if(to->object->journeyCode==from->object->journeyCode)
                   {
                     if(a==0) a=1;
                     listOfObjects<TrainInfoPerStation *>* New=New1;
                     while(New->next!=NULL)
                        New = New->next;	
                     New->next = new listOfObjects<TrainInfoPerStation *> (from->object);
                     break;       
                   }
                 from=from->next;
               }
             to=to->next;
            }
          if(a==1)
           { 
              // this part of the code executes only when New1->Next not equal to NULL
              StationConnectionInfo * S;  // creating new instance S of class StationConnectionInfo with list of trains equal to list New1
                                          // and index equal to Q1->object->adjacentStnIndex  
              S = new StationConnectionInfo(Q1->object->adjacentStnIndex);
              S->trains = New1->next;
              listOfObjects<StationConnectionInfo *>* Qnew=Qnew1;
              while(Qnew->next!=NULL)
                  Qnew = Qnew->next;
              Qnew->next = new listOfObjects<StationConnectionInfo *> (S); // adding S to the Qnew list
             }
           Q1=Q1->next;
       }
      Q=Q->next;
     } 
   Q = Qnew1->next; //assigning new list to Q
  }
  
  //cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  if(Journey1->next==NULL)   // if Journey1-next is null it means there are no direct journeys from source to station  
    {
      cout<<"No direct journeys available"<<endl;
      return;
     } 
  printStationInfo(Journey1->next);
  return;
}


#endif
