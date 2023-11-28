#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
void find(listOfObjects<StationConnectionInfo*>*h,int a,listOfObjects<TrainInfoPerStation*>*u,int check,listOfObjects<StationConnectionInfo*>*e,StationAdjacencyList* adjacency){
  listOfObjects<StationConnectionInfo*>* k=h;
  listOfObjects<StationConnectionInfo*>* o=e;
  listOfObjects<TrainInfoPerStation*>* d=u;
  while(k!=NULL){
    if(k->object->adjacentStnIndex==a){
      if(check==0){
        listOfObjects<TrainInfoPerStation*>*s=o->object->trains;
        while(s!=nullptr){
            d->next=new listOfObjects<TrainInfoPerStation*>(s->object);
            d=d->next;
            s=s->next;
        }

      }//Here this condition specifies whether the destination is connected directly to the start or it is connected indirectly. If check=0 the destionation is found
      //in the adjacent list of start.
      else{
        listOfObjects<TrainInfoPerStation*>*p=k->object->trains;
        while(p!=nullptr){
          if(p->object->journeyCode==check){
            if(d->next==nullptr){
              d->next=new listOfObjects<TrainInfoPerStation*>(p->object);
             d=d->next;
             break;
            }
            else{
              while(d->next!=nullptr){
                d=d->next;
              }
            }
          }
          else{
            p=p->next;
          }
        }
        //In this part we will add only one train code to the list of direct journeys.
      }
    }
    return;
  }
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  int start=stnNameToIndex.get(srcStnName)->value;
  int end=stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo*>* tolist1=adjacency[start].toStations;
  TrainInfoPerStation*pil=new TrainInfoPerStation(0,0,0,0);
  listOfObjects<TrainInfoPerStation*>* l=new listOfObjects<TrainInfoPerStation*>(pil); //
  find(tolist1,end,l,0,tolist1,adjacency);
  if(l->next!=nullptr){
  printStationInfo(l->next);
  }
  else{
    cout<<"No Journeys"<<endl;
  }

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
