#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <stdlib.h>
#include <vector>
using namespace std;
int diffbtwdays(TrainInfoPerStation a, TrainInfoPerStation b)
{
  int i = 0, j = 0;
  for (i = 0; i < 7; i++)
  {
    if (a.daysOfWeek[i])
      break;
  }
  for (j = 0; j < 7; j++)
  {
    if (b.daysOfWeek[j])
      break;
  }
  if(i<j){
    return (j-i)*24;
  }
  if(i==j){
    return 0;
  }
  if(i>j){
    return (7+j-i)*24;
  }
}
bool canadd(TrainInfoPerStation a, TrainInfoPerStation b,int time){
  int dt=diffbtwdays(a,b);
  int art=b.arrTime;
  int drt=a.depTime;
  int total=0;
  total=total+dt*60;
  time=time*60;
  art=(art/100)*60+art%100;
  total=total-art;
  drt=(drt/100)*60+drt%100;
  total=total+drt;
  if(total<0){
    return false;
  }
  else{
    return (total<=time);
  }
}
struct ajourney
{
  vector<TrainInfoPerStation>alltrains;
  vector<string>fromstation;
  vector<string>tostation;
  void add(TrainInfoPerStation nexttrain,string fromstationindex,string tostationindex){
    alltrains.push_back(nexttrain);
    fromstation.push_back(fromstationindex);
    tostation.push_back(tostationindex);
  }
  void deletelast(){
    alltrains.pop_back();
    fromstation.pop_back();
    tostation.pop_back();
  }
  TrainInfoPerStation lastjourney(){
    return alltrains[alltrains.size()-1];
  }
  void print(){
    for(int i=0;i<alltrains.size();i++){
      cout<<"....................START SUB JOURNEY........................."<<endl;
      cout<<"FROM STATION:"<<fromstation[i]<<endl;
      const char* day[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
      int j=0;
      for(j=0;j<7;j++){
        if(alltrains[i].daysOfWeek[j]) break;
      }
      cout << GREEN << "Day(s): " << RESET;
      cout<<day[j]<<endl;
      cout << BLUE << "JourneyCode: " << alltrains[i].journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      cout << alltrains[i].arrTime;
      cout << RED << " Dep: " << RESET;
      cout<<alltrains[i].depTime<<endl;
      cout<<"TO STATION:"<<tostation[i]<<endl;
      cout<<".........................END................................."<<endl;
    }
    return;
  }
};
TrainInfoPerStation findtrain(int index,TrainInfoPerStation a,StationAdjacencyList *adjacency){
  listOfObjects<StationConnectionInfo *> *dummy = adjacency[index].fromStations;
  while (dummy != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *toadd = dummy->object->trains;
    while (toadd != nullptr)
    {                                                                       
      if (a.journeyCode == toadd->object->journeyCode)
      {                                                                                       
        if(a.depTime < toadd->object->arrTime){
          int i=0,j=0;
          for (i = 0; i < 7; i++)
          {
            if (a.daysOfWeek[i])
              break;
          }
          for (j = 0; j < 7; j++)
          {
            if (toadd->object->daysOfWeek[j])
              break;
          }
          if(i==j){
            return *(toadd->object);
          }
        }
        if(a.depTime >= toadd->object->arrTime){
          int i=0,j=0;
          for (i = 0; i < 7; i++)
          {
            if (a.daysOfWeek[i])
              break;
          }
          for (j = 0; j < 7; j++)
          {
            if (toadd->object->daysOfWeek[j])
              break;
          }
          if((j-i)==1 || (j==6 && i==0)){
            return *(toadd->object);
          }
        }
      }                                                
      toadd = toadd->next;
    }
    dummy = dummy->next;
  }
}
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  static int recursionlevel = -1;
  static vector<ajourney> finallist;
  static ajourney ojourney;
  if (recursionlevel == -1)
  {
    finallist.clear();
    ojourney.alltrains.clear();
    ojourney.fromstation.clear();
    ojourney.tostation.clear();
  }
  recursionlevel++;
  if(maxStopOvers < 0){
    recursionlevel--;
    return;
  }
  int src = stnNameToIndex.get(srcStnName)->value;
  int dest = stnNameToIndex.get(destStnName)->value;
  if(src == dest){
    ajourney completejourney;
    completejourney.alltrains=ojourney.alltrains;
    completejourney.fromstation=ojourney.fromstation;
    completejourney.tostation=ojourney.tostation;
    finallist.push_back(completejourney);
  }
  else{
    listOfObjects<StationConnectionInfo *> *dummy = adjacency[src].toStations;
    while (dummy != nullptr)
    {
      listOfObjects<TrainInfoPerStation *> *toadd = dummy->object->trains;
      while (toadd != nullptr)
      {
        if(recursionlevel == 0){
          string temp=stnNameToIndex.getKeyAtIndex(dummy->object->adjacentStnIndex);
          ojourney.add(*(toadd->object),srcStnName,temp);
          printPlanJourneys(temp,destStnName,maxStopOvers-1,maxTransitTime);
          ojourney.deletelast();
        }
        else{
          TrainInfoPerStation b=ojourney.lastjourney();
          TrainInfoPerStation a=findtrain(dummy->object->adjacentStnIndex,b,adjacency);
          if(canadd(a,*(toadd->object),maxTransitTime)){
            string temp=stnNameToIndex.getKeyAtIndex(dummy->object->adjacentStnIndex);
            ojourney.add(*(toadd->object),srcStnName,temp);
            printPlanJourneys(temp,destStnName,maxStopOvers-1,maxTransitTime);
            ojourney.deletelast();
          }
        }
        toadd = toadd->next;
      }
      dummy = dummy->next;
    }
  }
  if (recursionlevel == 0)
  {
    for(int i=0;i<finallist.size();i++){
      cout<<"===================ALL JOURNEYS========================="<<endl;
      finallist[i].print();
      cout<<"=======================END=============================="<<endl;
    }
  }
  recursionlevel--;
  return;
}

#endif
