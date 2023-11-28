#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


string day(int i){
  if(i==0)return "SUN";
  if(i==1)return "MON";
  if(i==2)return "TUE";
  if(i==3)return "WED";
  if(i==4)return "THU";
  if(i==5)return "FRI";
  if(i==6)return "SAT";
}

class train{
  public:
    int train_num;
    string start_station;
    int start_time;
    int end_time;
    int endday;
    train* next;
    int start_day;
    int wait=-1;

    train(int train, string st,int dp_time,int day)
    {
      
      train_num = train;
      start_station = st;
      start_time=dp_time;
      start_day=day;
      next = nullptr;
    }

};
class train_path{
  
  public:
    int curr_station;
    int stops_left=0;
    int curr_day;
    int curr_dep;
    train* current_train=nullptr;
    train_path*next;
    train_path(int current_station,int stops,train* tr){
      curr_station=current_station;
      next=NULL;
      stops_left=stops;
      current_train=tr;
    }
    train_path(){}
};
void print(train* tp){
  if(tp->next==NULL){
      cout<<tp->start_station<<"  Journey code: "<<tp->train_num<<" DepTimeFromStation: "<<day(tp->start_day)<<", "<<tp->start_time<<endl;
      return;
  }
  print(tp->next);
  cout<<" Transit : "<<tp->wait<<endl;
  cout<<tp->start_station<<" ArrTime: "<<day(tp->endday)<<" , "<<tp->end_time<<"  Journey code: "<<tp->train_num<<" DepTimeFromStation: "<<day(tp->start_day)<<" , "<<tp->start_time<<endl;

}



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




void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  int source=(stnNameToIndex.get(srcStnName))->value;
  int des=(stnNameToIndex.get(destStnName))->value;
  train_path *ans=NULL;
  queue q;


  listOfObjects<StationConnectionInfo *> *stnlist=adjacency[source].toStations;
  while(stnlist!=NULL){
    
    listOfObjects<TrainInfoPerStation *> *trains=stnlist->object->trains;
    while(trains!=NULL){
      
      if(stnlist->object->adjacentStnIndex==des){
            for(int x=0;x<7;x++){
              if(trains->object->daysOfWeek[x]==1){
                int day=x;
                if(trains->object->depTime<trains->object->arrTime)day++;
                day=day%7;
                train* tr=new train(trains->object->journeyCode,stnNameToIndex.getKeyAtIndex(source),trains->object->depTime,day);
                train_path* tp= new train_path(des,maxStopOvers,tr);
                tp->next=ans;
                ans=tp;
              }
              
            }
      }
      else{
        for(int x=0;x<7;x++){
        if(trains->object->daysOfWeek[x]==1){
          int day=x;
          if(trains->object->depTime<trains->object->arrTime)day++;
          day=day%7;
          train* tr=new train(trains->object->journeyCode,stnNameToIndex.getKeyAtIndex(source),trains->object->depTime,day);
          train_path* tp= new train_path(stnlist->object->adjacentStnIndex,maxStopOvers,tr);
          tp->curr_day=day;
          tp->curr_dep=trains->object->depTime;
          //print(tr);
          q.Enqueue(tp);
        }
              
        }
      }
      trains=trains->next;
    }
    stnlist=stnlist->next;
  }




  while(q.N!=0){
    
    int train_num=q.head->current_train->train_num;
    int stn=q.head->curr_station;
    int arrTime=0;
    listOfObjects<StationConnectionInfo *> *arr_list=adjacency[stn].fromStations;
    
    
    
    while(arr_list!=NULL){
     
      listOfObjects<TrainInfoPerStation *> *trains=arr_list->object->trains;
      bool found=false;
      while(trains!=NULL){
        if(trains->object->journeyCode==train_num){
          arrTime=trains->object->arrTime;
          found=true;
          break;
        }
        trains=trains->next;
      }

      if(found)break;
      arr_list=arr_list->next;
    }
    
    if(arrTime<q.head->curr_dep)q.head->curr_day++;


    listOfObjects<StationConnectionInfo *> *stnlist=adjacency[stn].toStations;
    while(stnlist!=NULL){
      
      listOfObjects<TrainInfoPerStation *> *trains=stnlist->object->trains;
      while(trains!=NULL){
        if(trains->object->journeyCode==train_num){
          if(stnlist->object->adjacentStnIndex==des){
            train_path* temp=new train_path();
            *temp=*q.head;
            temp->curr_station=des;
            temp->next=ans;
            ans=temp;
            
          }
          else{
            train_path* temp=new train_path();
            *temp=*q.head;
            temp->curr_station=stnlist->object->adjacentStnIndex;
            temp->curr_dep=trains->object->depTime;
            if(trains->object->depTime<arrTime)temp->curr_day++;
            temp->curr_day=temp->curr_day%7;
            q.Enqueue(temp); 
          }  
          
          
        }
        else if(q.head->stops_left>0){
          if(stnlist->object->adjacentStnIndex==des){
              if(trains->object->depTime>arrTime){
                if((trains->object->depTime-arrTime<=maxTransitTime*100) && trains->object->daysOfWeek[q.head->curr_day]){
                  train* tr=new train(trains->object->journeyCode,stnNameToIndex.getKeyAtIndex(stn),trains->object->depTime,q.head->curr_day);
                  tr->wait=trains->object->depTime-arrTime;
                  tr->end_time=arrTime;
                  tr->endday=q.head->curr_day;
                  train_path* temp=new train_path();
                  *temp=*q.head;
                  tr->next=temp->current_train;
                  temp->current_train=tr;
                  temp->curr_station=stnlist->object->adjacentStnIndex;
                  temp->curr_dep=trains->object->depTime;
                  temp->stops_left--;
                  temp->next=ans;
                  ans=temp;
                }
            }
            else{
              if((2400-arrTime+trains->object->depTime<=maxTransitTime*100) && trains->object->daysOfWeek[(q.head->curr_day+1)%7]){
                train* tr=new train(trains->object->journeyCode,stnNameToIndex.getKeyAtIndex(stn),trains->object->depTime,(q.head->curr_day+1)%7);
                tr->wait=2400-arrTime+trains->object->depTime;
                tr->end_time=arrTime;
                tr->endday=q.head->curr_day;
                train_path* temp=new train_path();
                *temp=*q.head;
                tr->next=temp->current_train;
                temp->current_train=tr;
                temp->curr_day++;
                temp->curr_station=stnlist->object->adjacentStnIndex;
                temp->curr_dep=trains->object->depTime;
                temp->stops_left--;
                temp->next=ans;
                ans=temp;
              }
            }
          }
          else{
            if(trains->object->depTime>arrTime){
              if((trains->object->depTime-arrTime<=maxTransitTime*100) && trains->object->daysOfWeek[q.head->curr_day]){
                train* tr=new train(trains->object->journeyCode,stnNameToIndex.getKeyAtIndex(stn),trains->object->depTime,q.head->curr_day);
                tr->wait=trains->object->depTime-arrTime;
                tr->end_time=arrTime;
                tr->endday=q.head->curr_day;
                train_path* temp=new train_path();
                *temp=*q.head;
                tr->next=temp->current_train;
                temp->current_train=tr;
                temp->curr_station=stnlist->object->adjacentStnIndex;
                temp->curr_dep=trains->object->depTime;
                temp->stops_left--;
                q.Enqueue(temp);
              }
            }
            else{
              if((2400-arrTime+trains->object->depTime<=maxTransitTime*100) && trains->object->daysOfWeek[(q.head->curr_day+1)%7]){
                train* tr=new train(trains->object->journeyCode,stnNameToIndex.getKeyAtIndex(stn),trains->object->depTime,(q.head->curr_day+1)%7);
                tr->wait=2400-arrTime+trains->object->depTime;
                tr->end_time=arrTime;
                tr->endday=q.head->curr_day;
                train_path* temp=new train_path();
                *temp=*q.head;
                tr->next=temp->current_train;
                temp->current_train=tr;
                temp->curr_day++;
                temp->curr_station=stnlist->object->adjacentStnIndex;
                temp->curr_dep=trains->object->depTime;
                temp->stops_left--;
                q.Enqueue(temp);
              }
            }
          } 
        }
        trains=trains->next;
      }
      stnlist=stnlist->next;
    }
    q.Dequeue();
  }
  if(ans==NULL)cout<<"No journeys available"<<endl;
  else {
    int x=1;
    while(ans!=NULL){






      train* tp=ans->current_train;
      cout<<"Option "<<x<<endl;
      print(ans->current_train);
      x++;
      ans=ans->next;
    }
  }



  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
