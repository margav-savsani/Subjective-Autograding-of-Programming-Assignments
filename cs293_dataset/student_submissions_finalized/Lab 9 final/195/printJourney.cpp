#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
//the below function is used to find where the end station is present and store the train codes those are directly connecting the start and destination.
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
    else{
      int g=k->object->adjacentStnIndex;
      listOfObjects<TrainInfoPerStation*>* y=o->object->trains;
      int z;
      while(y!=nullptr){//This loop helps to go through all the trains to given adjacent station of the given source station
        if(check==0){
          z=y->object->journeyCode;
        }
        else{
          z=check;
        }//Here if check is zero then z takes the journey code value of that object or else check itself acts as the journey code that should be assigned to z.
        listOfObjects<StationConnectionInfo*>*t=adjacency[g].toStations;
        while(t!=nullptr){//This loop helps to go through all the trains between the adjacent station to starting station and their adjacent stations.
          listOfObjects<TrainInfoPerStation*>* j=t->object->trains;
          while(j!=nullptr){
            if(j->object->journeyCode==z){
              break;
            }
            j=j->next;
          }
          if(j!=nullptr){
            find(t,a,d,z,o,adjacency);
          }
          t=t->next;
        }
        // check=0;
        if(check==0){
        y=y->next;}
        else break;
      }
    }
    k=k->next;
    if(check==0){
      o=o->next;
    }
  }//I have done this function recursively to traverse through all the stations and find the all possible direct journeys from given start to end.
  return;
}
void Planner::printDirectJourneys(string srcStnName, string destStnName)
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
  
  

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
