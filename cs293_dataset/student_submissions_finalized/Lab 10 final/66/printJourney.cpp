#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <queue>

using namespace std;
struct triplet{
 string A;
 string B;
 int j;
 void print(){
   cout << A<<"->"<<B <<":"<<j<<endl;
 }
};

struct list_of_journey{
  
  queue<triplet> q;
  
  void add(string a,string b,int j){
    triplet t; t.A=a;t.B = b;t.j = j;
    q.push(t);
  }
  void print(){
    
    while(!q.empty()){
    (q.front()).print();
    q.pop();
    
    }
    cout << "Journey information ends";
  }
};

struct list{
   
   queue<list_of_journey> q;
   
   void add(list_of_journey l){q.push(l);}
   void print(){
        int  i =1;
       cout << "Following are the journeys of between source and destination "<<endl;
      while(!q.empty()){
         cout << i<<". "<< "Journey information: "<<endl;
         (q.front()).print();
         q.pop();
         i++;
      }
      
   }
};

list lsd;

StationAdjacencyList* adjacency ;Dictionary<int> stnNameToIndex;

void sal(StationAdjacencyList* a,Dictionary<int> s){
    adjacency = a;
    stnNameToIndex = s;
}

TrainInfoPerStation* f1(int jc,string source,string s){
   TrainInfoPerStation* R; int x=stnNameToIndex.get(s)->value,y=stnNameToIndex.get(source)->value;
   
   listOfObjects<TrainInfoPerStation *> *tl; StationAdjacencyList l = adjacency[y]; 
   listOfObjects<StationConnectionInfo *> *fl = l.fromStations; StationConnectionInfo* sci;
   
   while(fl!=nullptr){
     
     sci = fl->object;
     if(sci->adjacentStnIndex==x){
         tl = sci->trains;
         while(tl!=nullptr){
            R = tl->object;
            if(R->journeyCode=jc){return R;}
            tl=tl->next;
         }
     }
     
     fl = fl->next;
   }
}

bool f2(TrainInfoPerStation* t,TrainInfoPerStation* R,int mt){
     int tg = t->depTime - R->arrTime;
     
     if(tg<0){tg = 2400 + tg;}
     if(tg<=mt){return true;}
     else {return false;}
}

bool f3(int j,string source,string destination){
    bool k = false;
    bool visited[512];
    
    for(int i=0;i<512;i++){visited[i]=false;}
    int x = stnNameToIndex.get(source)->value,y=stnNameToIndex.get(destination)->value;
    
    StationAdjacencyList l ;queue<int> q;q.push(x);
    listOfObjects<StationConnectionInfo *> *ts ;
    StationConnectionInfo* sci; listOfObjects<TrainInfoPerStation *> *tl; TrainInfoPerStation *t;
        								 
    while(!q.empty()){
        int first = q.front();q.pop();
        l = adjacency[first];
        ts = l.toStations;
        
        while(ts!=nullptr){
           sci = ts->object;
           tl = sci->trains;bool yes = false;
           if(sci->adjacentStnIndex==y){k=true;return true;}
           else{
              if(visited[sci->adjacentStnIndex]==false){
              while(tl!=nullptr){
                if(tl->object->journeyCode==j) yes = true;
                if(tl->object->journeyCode==j) break;
                tl = tl->next;
              }
              
              if(yes){
                   q.push(sci->adjacentStnIndex);
              }
              visited[sci->adjacentStnIndex]=true;}
           }
           
           ts = ts->next;
        }
    } 
    
    return k; 								 
}

void F(int jrcode,string source,string destination,int k,int mt,list_of_journey li,string s){
 if(k!=0){   
    bool y = f3(jrcode,source,destination);
    
    if(y){ li.add(s,destination,jrcode);
         lsd.add(li);
     }
    
    TrainInfoPerStation* R = f1(jrcode,source,s);
    int i = stnNameToIndex.get(source)->value; string adjacent_station;
    
    StationAdjacencyList l = adjacency[i];
    
    listOfObjects<StationConnectionInfo *> *ts = l.toStations;
    StationConnectionInfo* sci; listOfObjects<TrainInfoPerStation *> *tl; TrainInfoPerStation *t;
    
    while(ts!=nullptr){
      sci = ts->object;tl = sci->trains;
      
      while(tl!=nullptr){
          t = tl->object;
          
          if(f2(t,R,mt)){
              adjacent_station = stnNameToIndex.getKeyAtIndex(sci->adjacentStnIndex);
              
              if(t->journeyCode!=jrcode){
              list_of_journey *l1 = new list_of_journey;
              *l1 = li;
              l1->add(s,source,jrcode);
              F(t->journeyCode,adjacent_station,destination,k-1,mt,*l1,source);}
              else { 
               list_of_journey *l1 = new list_of_journey;
              *l1 = li;
               
                 F(t->journeyCode,adjacent_station,destination,k,mt,*l1,s);
               }												
          }
          
          tl = tl->next;
      } 
         
      ts=ts->next;
    }
  }  
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  sal(adjacency,stnNameToIndex);
  
  int i = stnNameToIndex.get(srcStnName)->value;
  StationAdjacencyList l = adjacency[i];
  listOfObjects<StationConnectionInfo *> *ts = l.toStations;
    StationConnectionInfo* sci; listOfObjects<TrainInfoPerStation *> *tl; TrainInfoPerStation *t;
    
   while(ts!=nullptr){
      sci = ts->object;tl = sci->trains;
    
    while(tl!=nullptr){
          t = tl->object;
          list_of_journey *li = new list_of_journey;
      F(tl->object->journeyCode,stnNameToIndex.getKeyAtIndex(sci->adjacentStnIndex),destStnName,maxStopOvers,maxTransitTime,*li,srcStnName);
    
       tl = tl->next;
    }
    ts=ts->next;  
   }     
  
  lsd.print();
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
