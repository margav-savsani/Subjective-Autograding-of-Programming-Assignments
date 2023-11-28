#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include "codes.h"
using namespace std;

int recursionlevel=0;
int arrivaltime=2500;
TrainInfoPerStation* prevtrain=nullptr;
int arrday=8;
int i=1;
int prevcode=-1;
// calculates difference b/w 2 times
float diff(int day1,int time1,int day2,int time2)
{
  int m1=time1%100;
  int m2=time2%100;
  int h1 = time1/100;
  int h2 = time2/100;
  float f1=float(m1)/60;
  float f2=float(m2)/60;
  float t1=24*day1 + h1 + f1;
  float t2=24*day2 + h2 + f2;
  
  float t3;
  if(t2-t1>=0){
    t3=t2-t1;
  }
  else{
    t3=168+t2-t1;
  }
  return t3;
}

class A {
  public:
  string src;
  string des;
  TrainInfoPerStation* trn;
  int srcday;
  int arrtime;
  int desday;
  A(string src,string des, TrainInfoPerStation* trn, int srcday, int arrtime, int desday){
    this->src=src;
    this->des=des;
    this->trn=trn;
    this->srcday=srcday;
    this->arrtime=arrtime;
    this->desday=desday;
  }
};
// prints a journey
void print(string src, string des, TrainInfoPerStation* trn, int srcday, int arrtime, int desday)
{
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  
  cout<<BLUE<<src<<RESET<<endl;
  cout<<"|"<<GREEN<<"JourneyCode:"<<trn->journeyCode<<" "<<RED<<"Departs: "<<days[srcday]<<", "<<trn->depTime<<"\t"<<"Arrives: "<<days[desday]<<", "<<arrtime<<endl;
  cout<<BLUE<<des<<RESET<<endl;
}
// prints elemnts of linked list
void printlist(listOfObjects<A*>* lst){

  if(lst==nullptr){return;}

  listOfObjects<A*>* prevlst = lst->prev;
  while(lst->prev!=nullptr){
    lst=lst->prev;
  }
  
  while(lst!=nullptr){
    A* tmpobj=lst->object;

    print(tmpobj->src,tmpobj->des,tmpobj->trn,tmpobj->srcday,tmpobj->arrtime,tmpobj->desday);
    lst=lst->next;
  }
  lst=prevlst;
  // lst->next=nullptr;
}
//return time at which train arrives at adj stn
int gettime(TrainInfoPerStation* traininfo,listOfObjects<TrainInfoPerStation *>* trnslst_dest)
{
  int jc=traininfo->journeyCode;
  listOfObjects<TrainInfoPerStation*>*tmp=trnslst_dest;
  while(tmp!=nullptr)
  {
    if(jc==tmp->object->journeyCode){
      return tmp->object->arrTime;
    }
    tmp=tmp->next;
  }
  return -1;
}
// returns day at which train arrives at adj stn
int getdays(int day,TrainInfoPerStation* traininfo,listOfObjects<TrainInfoPerStation *>* trnslst_dest)
{
  int jc=traininfo->journeyCode;
  listOfObjects<TrainInfoPerStation*>*tmp=trnslst_dest;
  while(tmp!=nullptr)
  {
    if(jc==tmp->object->journeyCode){
      bool* lst = tmp->object->daysOfWeek;
      int j=day;
      while(true){
        if(lst[j]){return j;}
        else{j=(j+1)%7;if(j==day){return -1;}}
      }
    }
    tmp=tmp->next;
  }
  return -1;
}



listOfObjects<A*> *lst;
// func2 prints for recursion level>0, or stns b/w source and destination
void func2(string src, string des,Dictionary<int> stnNameToIndex,StationAdjacencyList adjacency[DICT_SIZE],listOfObjects<TrainInfoPerStation *> *stationInfo[DICT_SIZE],TrainInfoPerStation* prevtrn,int arrtime, int arrday,int maxTransitTime,int maxStopOvers)
{
  if(maxStopOvers<0){return;}
  int srcindex = stnNameToIndex.get(src)->value;
  int destindex = stnNameToIndex.get(des)->value;

  StationAdjacencyList srcadjlist = adjacency[srcindex];
  listOfObjects<StationConnectionInfo*>* srctostns = srcadjlist.toStations;

  if(src==des){
    printlist(lst);
    cout<<"-----------------------"<<endl;
    return;
  }

  while(srctostns!=nullptr){
    listOfObjects<TrainInfoPerStation*>* trnslst = srctostns->object->trains;
    int adjindex = srctostns->object->adjacentStnIndex;
    string adjstnname = stnNameToIndex.getKeyAtIndex(adjindex);
    listOfObjects<TrainInfoPerStation*>* trns_dest=stationInfo[adjindex];
    while(trnslst!=nullptr){
      TrainInfoPerStation* trninfo=trnslst->object;

      for(int i=0;i<7;i++){
        if(trninfo->daysOfWeek[i] and diff(arrday,arrtime,i,trninfo->depTime)<=maxTransitTime){
          if(trninfo->journeyCode!=prevtrn->journeyCode){maxStopOvers-=1;}
          listOfObjects<A*>* prev=lst;
          if(lst!=nullptr){prev=lst;lst=lst->next;}
          A* tmp = new A(src,adjstnname,prevtrn,i,gettime(trninfo,trns_dest),getdays(i,trninfo,trns_dest));
          lst=new listOfObjects<A*> (tmp);
          lst->prev=prev;

          func2(adjstnname,des,stnNameToIndex,adjacency,stationInfo,trninfo,gettime(trninfo,trns_dest),getdays(i,trninfo,trns_dest),maxTransitTime,maxStopOvers);
        }
      }
      
      
      trnslst=trnslst->next;
    }
    srctostns=srctostns->next;
  }
}

// func1 checks and prints for source to adjacent stations ,1.e recursionlevel=0;
void func1(string src, string des,Dictionary<int> stnNameToIndex,StationAdjacencyList adjacency[DICT_SIZE],listOfObjects<TrainInfoPerStation *> *stationInfo[DICT_SIZE],int maxTransitTime, int maxStopOvers){
  int srcindex = stnNameToIndex.get(src)->value;
  int destindex = stnNameToIndex.get(des)->value;
  if(maxStopOvers<0){return;}
  StationAdjacencyList srcadjlist = adjacency[srcindex];
  listOfObjects<StationConnectionInfo*>* srctostns = srcadjlist.toStations;

  while(srctostns!=nullptr){
    listOfObjects<TrainInfoPerStation*>* trnslst = srctostns->object->trains;
    int adjindex = srctostns->object->adjacentStnIndex;
    string adjstnname = stnNameToIndex.getKeyAtIndex(adjindex);
    listOfObjects<TrainInfoPerStation*>* trns_dest=stationInfo[adjindex];
    while(trnslst!=nullptr){
      TrainInfoPerStation* trninfo=trnslst->object;

      for(int i=0;i<7;i++){
        if(trninfo->daysOfWeek[i]){
          listOfObjects<A*>* prev;
          if(lst!=nullptr){prev=lst;lst=lst->next;}
          A* tmp = new A(src,adjstnname,trninfo,i,gettime(trninfo,trns_dest),getdays(i,trninfo,trns_dest));
          lst=new listOfObjects<A*> (tmp);
          lst->prev=prev;
          // listOfObjects<A*> *tmpl=lst;
          // lst=lst->next;
          // if(lst!=nullptr){lst->prev=tmpl;}
          
          func2(adjstnname,adjstnname,stnNameToIndex,adjacency,stationInfo,trninfo,gettime(trninfo,trns_dest),getdays(i,trninfo,trns_dest),maxTransitTime,maxStopOvers);
        }
      }
      

      trnslst=trnslst->next;
    }
    srctostns=srctostns->next;
  }
}


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  func1(srcStnName,destStnName,stnNameToIndex,adjacency,stationInfo,maxTransitTime,maxStopOvers);
  return;
}

#endif