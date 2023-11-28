#include "dictionary.cpp"
#include "planner.h"

Planner::Planner(){
    N=1024;
    journey=new Journey[N];
    for(int i=0;i<N;i++){
      journey[i].from.name="NILL";
    }
  };

int Planner::hashValue(string key){
    long long int sum=0;
    int power=0,value;
    double x=37,a=(sqrt(5)-1)/2;
    for (int i=0;(int)key[i]!=0;i++)
    {
        sum+=((int)key[i])*(pow(x,power));
    }
    value=(int)(N*((sum*a)-(int)(sum*a)));
    return value;
};

int Planner::findFreeIndex(string key){
    int hvalue=hashValue( key);
    for(int i=0;i<N;i++)
    {
        if(journey[(hvalue+i)%N].from.name!="NILL")continue;
        else return((i+hvalue)%N);
    }
    return -1;
  };

  bool Planner::addJourney(Journey newJourney){
    int pos=findFreeIndex(newJourney.from.name);
    if(pos>=0)
    {
        journey[pos]=newJourney;
        return true;
    }
    else return false;
};

void Planner::printList(Station station){
    int hvalue=hashValue(station.name);
    int count=0;
    for (int i = 0; i < N; i++)
    {
      if(journey[(hvalue+i)%N].from.name=="NILL" && count==0){
        cout<<"Error"<<endl;
        return;
      }  
      if(journey[(hvalue+i)%N].from.name=="NILL")return;
      if(journey[(hvalue+i)%N].from.name==station.name && journey[(hvalue+i)%N].from.time>=station.time){
        count++;
        cout<<journey[(hvalue+i)%N].from.time<<" "<<journey[(hvalue+i)%N].to.name<<endl;
      }
    }
};

float Planner::foundJourney(string station1,string station2){
    int hvalue=hashValue(station1);
    for (int i = 0; i < N; i++)
    {
      if(journey[(hvalue+i)%N].from.name=="NILL")
        return -1;
      if(journey[(hvalue+i)%N].from.name==station1 && journey[(hvalue+i)%N].to.name==station2)
        return journey[(hvalue+i)%N].from.time;
    }
    return -1;
};

void Planner::findJourney(Station station1 , string station2){
    int hvalue=hashValue(station1.name);
    float inter_start_time=2500,start_time=2500;string inter_station="NILL";
    for (int i = 0; i < N; i++)
    {
      if(journey[(hvalue+i)%N].from.name==station1.name){
        if(journey[(hvalue+i)%N].to.name==station2){
          if(journey[(hvalue+i)%N].from.time>=station1.time && journey[(hvalue+i)%N].from.time<=start_time){
            start_time=journey[(hvalue+i)%N].from.time;
            inter_station=station2;
          }
        }
        else{
          float injtime=foundJourney(journey[(hvalue+i)%N].to.name,station2);
          float dummytime=journey[(hvalue+i)%N].from.time;
          if(dummytime>=station1.time && dummytime<=start_time && injtime>=0 && injtime<inter_start_time){
            start_time=dummytime;
            inter_start_time=injtime;
            inter_station=journey[(hvalue+i)%N].to.name;
          }
        }
      }
      if(journey[(hvalue+i)%N].from.name=="NILL")break;

    }   
    if(inter_station=="NILL")cout<<"Error"<<endl;
    else{
      if(inter_station==station2)cout<<start_time<<endl;
      else cout<<start_time<<" "<<inter_station<<" "<<inter_start_time<<endl;
    }
};

