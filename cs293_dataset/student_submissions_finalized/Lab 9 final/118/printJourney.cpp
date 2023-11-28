#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName){
  Entry<int> *temp;
  int source,destination,check=0;
  listOfObjects<TrainInfoPerStation *> *station_info=nullptr;

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

  //To store the jcs of trains which have been traversed
  listOfObjects<int> *trains_done=new listOfObjects<int>(-1);
  trains_done->next=trains_done;
  trains_done->prev=trains_done;

  //while loop to cycle through all the stations adjacent to the source station
  while(stn!=nullptr){//cout<<"Inside first while loop"<<endl;
    //To store the trains that can be traversed from this station
    listOfObjects<TrainInfoPerStation *> *trains=stn->object->trains;

    //To check whether the destination is adjacent to the start station
    if(stn->object->adjacentStnIndex==destination){//cout<<"Station directly connected"<<endl;
      while(trains!=nullptr){
        check++;
        if(station_info==nullptr){
          station_info=new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(trains->object->journeyCode,0,-1,-1));
        }
        else{
          station_info->prev=new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(trains->object->journeyCode,0,-1,-1));
          station_info->prev->next=station_info;
          station_info=station_info->prev;
        }
        //cout<<"Journey code - "<<trains->object->journeyCode<<endl;
        trains=trains->next;
      }
    }

    //If the destination is not adjacent to the source
    else{//cout<<"Station not directly connected"<<endl;
      //while loop to cycle through all the trains going from the source station to the adjacent stations
      while(trains!=nullptr){
        //cout<<"Cycling trains"<<endl;
        //To store the jc of the train
        int jc=trains->object->journeyCode;

        //--------------------------------------------------------------------------------
        //while loop to check whether the train has been traversed or not
        do{
          if(jc==trains_done->next->object){
            break;
          }
          trains_done=trains_done->next;
        }while(trains_done->object!=-1);

        if(trains_done->object!=-1){//cout<<"Train already done"<<endl;
          trains_done=trains_done->prev;
          trains=trains->next;
          continue;
        }
        else{//cout<<"Train not done"<<endl;
          listOfObjects<int> *train_on=new listOfObjects<int>(jc);
          train_on->next=trains_done->next;
          train_on->prev=trains_done;
          trains_done->next=train_on;
        }
        //--------------------------------------------------------------------------------

        //Creating a circular lists to store the indices of the stations visited
        listOfObjects<int> *stn_ind_visited=new listOfObjects<int>(-1);
        stn_ind_visited->next=stn_ind_visited;
        stn_ind_visited->prev=stn_ind_visited;

        //Creating a list to store the stations to be visited
        listOfObjects<StationConnectionInfo *> *stn_at=new listOfObjects<StationConnectionInfo *>(stn->object);
        listOfObjects<StationConnectionInfo *> *stn_temp=stn->next;
        listOfObjects<StationConnectionInfo *> *stn_at_end=stn_at;

        //While loop to store the stations to be visited in the list created above
        while(stn_temp!=nullptr){//cout<<"Forming initial list"<<endl;
          listOfObjects<TrainInfoPerStation *> *train_checker=stn_temp->object->trains;
          while(train_checker!=nullptr){
            if(train_checker->object->journeyCode==jc){
              break;
            }
            train_checker=train_checker->next;
          }
          if(train_checker!=nullptr){
            stn_at_end->next=new listOfObjects<StationConnectionInfo *>(stn_temp->object);
            stn_at_end=stn_at_end->next;
          }
          stn_temp=stn_temp->next;
        }

        //--------------------------------------------------------------------------------
        while(stn_at!=nullptr){//cout<<"Finally checking stations"<<endl;
          //To check whether this station is the destination
          if(stn_at->object->adjacentStnIndex==destination){
            check++;
            if(station_info==nullptr){
              station_info=new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(trains->object->journeyCode,0,-1,-1));
            }
            else{
              station_info->prev=new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(trains->object->journeyCode,0,-1,-1));
              station_info->prev->next=station_info;
              station_info=station_info->prev;
            }
            //cout<<"Journey code - "<<jc<<endl;
            break;
          }

          //while loop to append the stations which can be traversed to the end of the list created earlier
          stn_temp=adjacency[stn_at->object->adjacentStnIndex].toStations;
          while(stn_temp!=nullptr){

            //To check if our train goes to this station or not
            listOfObjects<TrainInfoPerStation *> *train_checker=stn_temp->object->trains;
            while(train_checker!=nullptr){
              if(train_checker->object->journeyCode==jc){
                break;
              }
              train_checker=train_checker->next;
            }
            if(train_checker==nullptr){
              stn_temp=stn_temp->next;
              continue;
            }

            //do while to check whether this station has already been traversed
            do{
              if(stn_temp->object->adjacentStnIndex==stn_ind_visited->object){
                break;
              }
            }while(stn_ind_visited->object!=-1);

            //if else to store the station information in the list if not visited earlier
            if(stn_ind_visited->object==-1){
              stn_at_end->next=new listOfObjects<StationConnectionInfo*>(stn_temp->object);
              stn_at_end=stn_at_end->next;
              listOfObjects<int> *stn_ind_visited_temp=new listOfObjects<int>(stn_at_end->object->adjacentStnIndex);
              stn_ind_visited_temp->next=stn_ind_visited->next;
              stn_ind_visited_temp->prev=stn_ind_visited;
              stn_ind_visited->next=stn_ind_visited_temp;
            }
            else{
              stn_ind_visited=stn_ind_visited->prev;
            }

            stn_temp=stn_temp->next;
          }

          stn_temp=stn_at->next;
          delete stn_at;
          stn_at=stn_temp;
        }
        stn_ind_visited->prev=stn_ind_visited->next;
        stn_ind_visited->next=nullptr;
        stn_ind_visited=stn_ind_visited->prev;

        //To delete the list
        listOfObjects<int> *stn_ind_visited_deleter;
        while(stn_ind_visited!=nullptr){
          stn_ind_visited_deleter=stn_ind_visited->next;
          delete stn_ind_visited;
          stn_ind_visited=stn_ind_visited_deleter;
        }
        
        //--------------------------------------------------------------------------------
        
        trains=trains->next;
      }
    }
    stn=stn->next;
  }

  //To delete the list
  trains_done->prev=trains_done->next;
  trains_done->next=nullptr;
  trains_done=trains_done->prev;
  listOfObjects<int> *trains_done_deleter;
  while(trains_done!=nullptr){
    trains_done_deleter=trains_done->next;
    delete trains_done;
    trains_done=trains_done_deleter;
  }

  if(check==0)
    cout<<"No direct journeys available"<<endl;
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
    printStationInfo(station_info);

    //To delete the list to free up space
    while(station_info!=nullptr){
      station_info_dup=station_info->next;
      delete station_info;
      station_info=station_info_dup;
    }
  }
}