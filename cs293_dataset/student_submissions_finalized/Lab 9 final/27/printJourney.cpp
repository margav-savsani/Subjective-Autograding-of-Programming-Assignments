#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;



class train_path{
  public:
    int train_num;
    int station_num;
    train_path* next;

    train_path(int train, int station)
    {
      train_num = train;
      station_num = station;
      next = nullptr;
    }

};

class queue{
  public:
    train_path* head;
    train_path* tail;
    int N;
    queue()
    {
      head = nullptr;
      tail = nullptr;
      N = 0;
    }
    
    void Enqueue(train_path* node)
    {
      if(N == 0)
      {
        head = node;
        tail = node;
      }
      else
      {
        tail->next = node;
        tail = node;
      }
      N++;
    }
    void Dequeue()
    {
      if(N == 0)
        return;
      else if (N == 1)
      {
        tail = nullptr;
        head = nullptr;
      }
      else{
        train_path* del=head;
        head = head->next;
      }
      N--;
    }
    int get_num(){
      return N;
    }
};


void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int source=(stnNameToIndex.get(srcStnName))->value;
  int des=(stnNameToIndex.get(destStnName))->value;
  listOfObjects<TrainInfoPerStation*> *ans=NULL;
  queue q;
  listOfObjects<StationConnectionInfo *> *stnlist=adjacency[source].toStations;
  while(stnlist!=NULL){
    listOfObjects<TrainInfoPerStation *> *trains=stnlist->object->trains;
    while(trains!=NULL){
      if(stnlist->object->adjacentStnIndex==des){
            listOfObjects<TrainInfoPerStation *> * temp= new listOfObjects<TrainInfoPerStation *>(trains->object);
            temp->next=ans;
            ans=temp;
            trains=trains->next;
            continue;
      }
      train_path* jrn=new train_path(trains->object->journeyCode,stnlist->object->adjacentStnIndex);
      q.Enqueue(jrn);
      trains=trains->next;
    }
    stnlist=stnlist->next;
  }




  while(q.N!=0){
    int train_num=(q.head->train_num);
    int stn=q.head->station_num;
    listOfObjects<StationConnectionInfo *> *stnlist=adjacency[stn].toStations;
    while(stnlist!=NULL){
      listOfObjects<TrainInfoPerStation *> *trains=stnlist->object->trains;
      
      bool found=false;
      while(trains!=NULL){
        if(trains->object->journeyCode==train_num){
          if(stnlist->object->adjacentStnIndex==des){
            listOfObjects<TrainInfoPerStation *> * temp= new listOfObjects<TrainInfoPerStation *>(trains->object);
            temp->next=ans;
            ans=temp;
            found=true;
            break;
          }
          train_path* jrn=new train_path(trains->object->journeyCode,stnlist->object->adjacentStnIndex);
          q.Enqueue(jrn);
          found=true;
          break;
        }
        if(found)break;
        trains=trains->next;
      }
    stnlist=stnlist->next;
    }
    q.Dequeue();
  }
  if(ans==NULL)cout<<"No direct journeys available"<<endl;
  else printStationInfo(ans);

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
