#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class Station_train_info{
  public :
  int station_code;
  int train_code;
  Station_train_info *prev;
  Station_train_info *next;

  Station_train_info(){
    station_code=-1;
    train_code=-1;
    next=nullptr;
    prev=nullptr;
  }

  Station_train_info(int sc,int tc){
    station_code=sc;
    train_code=tc;
    next=nullptr;
    prev=nullptr;
  }
};
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){
  Entry<int> *temp;
  int source,destination,check=0;
  listOfObjects<Station_train_info *> *station_train_info=nullptr;

  //cout<<"Inside"<<endl;

//----------------------------------------------------------------------------------------
  //To check whether the source and the station are valid
  temp=stnNameToIndex.get(srcStnName);
  if(temp==nullptr){
    //cout<<"Invalid Source Station"<<endl;
    return;
  }
  source=temp->value;
  temp=stnNameToIndex.get(destStnName);
  if(temp==nullptr){
    //cout<<"Invalid Destination Station"<<endl;
    return;
  }
  destination=temp->value;
//----------------------------------------------------------------------------------------

//cout<<"Soure and destination are valid"<<endl;

  //To store the stations which have to be traversed
  listOfObjects<StationConnectionInfo *> *stn=adjacency[source].toStations;

  while(stn!=nullptr){
    //To store the trains that can be traversed from this station
    listOfObjects<TrainInfoPerStation *> *trains=stn->object->trains;

    //while loop to cycle through all the trains
    while(trains!=nullptr){
      int jc=trains->object->journeyCode;
      Station_train_info *this_train=new Station_train_info(source,jc);
      bool train_check=false;

      //The search


      if(train_check){
        if(station_train_info==nullptr){
          station_train_info=new listOfObjects<Station_train_info*>(this_train);
        }
        else{
          station_train_info->prev=new listOfObjects<Station_train_info*>(this_train);
          station_train_info->prev->next=station_train_info->next;
          station_train_info->next=station_train_info->prev;
        }
      }
      else{
        Station_train_info *this_train_deleter;
        while(this_train!=nullptr){
          this_train_deleter=this_train->next;
          delete this_train;
          this_train=this_train_deleter;
        }
      }
    }
  }

  if(check==0){
    cout<<"No Jounrey available"<<endl;
  }
  else{
    //while loop to assign the dep time, arr time and the days of week to the list of stations
    listOfObjects<TrainInfoPerStation *> *station_info_dup=station_info;
    while(station_info_dup!=nullptr){
      listOfObjects<TrainInfoPerStation *> *station_info_temp=stationInfo[source];
      while(station_info_temp!=nullptr){
        if(station_info_temp->object->journeyCode==station_info_dup->object->journeyCode){
          *(station_info_dup->object)=*(station_info_temp->object);
          break;
        }
        station_info_temp=station_info_temp->next;
      }
      station_info_dup=station_info_dup->next;
    }

    //To print the stations
    //printStationInfo(station_info);

    //To delete the list to free up space
    while(station_info!=nullptr){
      station_info_dup=station_info->next;
      delete station_info;
      station_info=station_info_dup;
    }
  }
}

#endif
