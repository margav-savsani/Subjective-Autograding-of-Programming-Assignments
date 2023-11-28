#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<queue>
using namespace std;


struct cust{
  int stncd;
  int trnnm;
  cust(int x, int y){
    stncd = x;
    trnnm = y;
  }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  int arr[10];
  int x=stnNameToIndex.get(srcStnName)->value;
  int req=stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo*>* li = adjacency[x].toStations;
  listOfObjects<int> *ans;
  ans = new listOfObjects<int>(-1);
  listOfObjects<int> *finalans = ans;


  queue<cust> T;
  while(li!=NULL){
    int stn = li->object->adjacentStnIndex;
    listOfObjects<TrainInfoPerStation*>* tli = li->object->trains;
    while(tli!=NULL){
      cust R(stn,tli->object->journeyCode);
      //cout<<"Station "<<R.stncd<<" , Train: "<<R.trnnm<<endl;
      T.push(R);
      tli = tli->next;
    }

    li = li->next;
  } 

  while(!T.empty()){
    cust u = T.front();
    T.pop();
    //cout<<"Station "<<u.stncd<<" , Train: "<<u.trnnm<<endl;
    if(u.stncd == req){
      ans->next = new listOfObjects<int>(u.trnnm); 
      ans = ans->next;
      continue;
    }
    listOfObjects<StationConnectionInfo*>* li_in = adjacency[u.stncd].toStations;


    while(li_in!=NULL){
      int stn = li_in->object->adjacentStnIndex;
      listOfObjects<TrainInfoPerStation*>* tli_in = li_in->object->trains;
      while(tli_in!=NULL){
        if(tli_in->object->journeyCode == u.trnnm){
          cust R(stn,tli_in->object->journeyCode);
          T.push(R);
        }
        tli_in = tli_in->next;
        
      }

      li_in = li_in->next;
    } 

  }
  ans = finalans;
  if(ans->next==NULL){
    cout<<"No direct journeys available"<<endl;
  }
  else{
    cout<<"The following trains offer direct service between "<<srcStnName<<" and "<<destStnName<<endl;
    while(ans->next!=NULL){
      cout<<"Train Code : "<<ans->next->object<<endl;
      ans = ans->next;
    }
  }

  
  
  //cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
