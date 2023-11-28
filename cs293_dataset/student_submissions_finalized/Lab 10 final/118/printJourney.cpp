#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class Station_train_info{
  public :
  int station_code;
  TrainInfoPerStation *train_code;

  Station_train_info(){
    station_code=-1;
    train_code=nullptr;
  }
};
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){
  
  static int source,destination,check=0,iteration=-1;
  static Station_train_info *train_seq;
  static StationConnectionInfo* STN=nullptr;

  iteration++;

  if(iteration==0){
    train_seq=new Station_train_info[1+maxStopOvers];
    Entry<int> *temp;

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

    train_seq[0].station_code=source;
    //To store the stations which have to be traversed
    listOfObjects<StationConnectionInfo *> *stn=adjacency[source].toStations;
    source=0;
    //cout<<stn<<source<<adjacency[source].toStations<<"Hello"<<endl;

    while(stn!=nullptr){
      //To store the trains that can be traversed from this station
      listOfObjects<TrainInfoPerStation *> *trains=stn->object->trains;

      STN=stn->object;
      //printStationInfo(trains);

      //while loop to cycle through all the trains
      while(trains!=nullptr){

        train_seq[0].train_code=new TrainInfoPerStation(trains->object->journeyCode,0,trains->object->arrTime,trains->object->depTime);
        copy(trains->object->daysOfWeek,trains->object->daysOfWeek+7,train_seq[0].train_code->daysOfWeek);

        printPlanJourneys(srcStnName,destStnName,maxStopOvers,maxTransitTime*60);

        delete train_seq[0].train_code;
        trains=trains->next;
      }
      stn=stn->next;
    }


    if(check==0){
      cout<<"No Jounrey available"<<endl;
    }

    delete train_seq;
  }
//----------------------------------------------------------------------------------------
  else{//cout<<"On "<<stnNameToIndex.getKeyAtIndex(STN->adjacentStnIndex)<<endl;
    StationConnectionInfo* STN_mem=STN;
    //------------------------------------------------------------------------------------
    //To update the arrTime
    int arrTime=-2;
    listOfObjects<StationConnectionInfo *> *stn=adjacency[STN->adjacentStnIndex].fromStations;
    //cout<<stnNameToIndex.getKeyAtIndex(STN->adjacentStnIndex)<<endl;
    while(stn!=nullptr){
        //cout<<"Checking "<<stnNameToIndex.getKeyAtIndex(stn->object->adjacentStnIndex)<<endl;
      
      listOfObjects<TrainInfoPerStation *> *trains=stn->object->trains;
      while(trains!=nullptr){
        if(trains->object->journeyCode==train_seq[source].train_code->journeyCode){
          arrTime=trains->object->arrTime;
          //cout<<stnNameToIndex.getKeyAtIndex(stn->object->adjacentStnIndex)<<arrTime<<endl;
          break;
        }
        trains=trains->next;
      }
      if(arrTime!=-2)
        break;
      stn=stn->next;
    }
    train_seq[source].train_code->arrTime=arrTime;

    //To check whether this is the destination station or not
    if(STN->adjacentStnIndex==destination){
      /*bool days[source+1][7];
      for(int j=0;j<7;j++){
        days[0][j]=train_seq[0].train_code->daysOfWeek[i];
      }
      for(int i=1;i<=source;i++){

      }*/

      check++;
      cout<<"\033[35m"<<"****************************"<<RESET<<endl;
      for(int i=0;i<=source;i++){
        cout<<"\033[35;1m"<<stnNameToIndex.getKeyAtIndex(train_seq[i].station_code)<<"(via train - "<<train_seq[i].train_code->journeyCode<<") to "<<RESET;
      }
      cout<<"\033[35;1m"<<stnNameToIndex.getKeyAtIndex(destination)<<RESET<<endl;
      listOfObjects<TrainInfoPerStation *> *printer=new listOfObjects<TrainInfoPerStation *>(train_seq[0].train_code);

      for(int i=0;i<source;i++){
        cout<<stnNameToIndex.getKeyAtIndex(train_seq[i].station_code)<<" to "<<stnNameToIndex.getKeyAtIndex(train_seq[i+1].station_code)<<endl;
        printStationInfo(printer);
        int transit=(train_seq[i+1].train_code->depTime-40*(train_seq[i+1].train_code->depTime/100)-train_seq[i].train_code->arrTime+40*(train_seq[i].train_code->arrTime/100)+1440)%1440;
        cout<<"Transit Time - "<<transit/60<<" Hours "<<transit%60<<" Minutes"<<endl;
        printer->object=train_seq[i+1].train_code;
      }
      cout<<stnNameToIndex.getKeyAtIndex(train_seq[source].station_code)<<" to "<<stnNameToIndex.getKeyAtIndex(destination)<<endl;
      printStationInfo(printer);

      delete printer;
      cout<<"\033[35m"<<"****************************"<<RESET<<endl;

    }
    //------------------------------------------------------------------------------------
    else{
      //----------------------------------------------------------------------------------
      //To perform a modified DFS
      stn=adjacency[STN->adjacentStnIndex].toStations;
      while(stn!=nullptr){
        listOfObjects<TrainInfoPerStation *> *trains=stn->object->trains;
        if(source<maxStopOvers){
          train_seq[source+1].station_code=STN->adjacentStnIndex;
        }

        while(trains!=nullptr){

          if(trains->object->journeyCode==train_seq[source].train_code->journeyCode){
            STN=stn->object;
            printPlanJourneys(srcStnName,destStnName,maxStopOvers,maxTransitTime);
            train_seq[source].train_code->arrTime=arrTime;
          }
          else if(source<maxStopOvers){

            if(train_seq[source].train_code->arrTime>trains->object->depTime){
              if(trains->object->depTime-40*(trains->object->depTime/100)-train_seq[source].train_code->arrTime+40*(train_seq[source].train_code->arrTime/100)<=maxTransitTime-1440){
                source++;
                train_seq[source].station_code=STN_mem->adjacentStnIndex;
                train_seq[source].train_code=new TrainInfoPerStation(trains->object->journeyCode,0,trains->object->arrTime,trains->object->depTime);
                for (int i=0;i<7;i++){
                  train_seq[source].train_code->daysOfWeek[i]=trains->object->daysOfWeek[i];
                }
                STN=stn->object;
                printPlanJourneys(srcStnName,destStnName,maxStopOvers,maxTransitTime);
                delete train_seq[source].train_code;
                train_seq[source].train_code=nullptr;
                source--;
              }
            }
            else if(trains->object->depTime-40*(trains->object->depTime/100)-train_seq[source].train_code->arrTime+40*(train_seq[source].train_code->arrTime/100)<=maxTransitTime){
              source++;
                train_seq[source].station_code=STN_mem->adjacentStnIndex;
              train_seq[source].train_code=new TrainInfoPerStation(trains->object->journeyCode,0,trains->object->arrTime,trains->object->depTime);
              for (int i=0;i<7;i++){
                train_seq[source].train_code->daysOfWeek[i]=trains->object->daysOfWeek[i];
              }
              STN=stn->object;
              printPlanJourneys(srcStnName,destStnName,maxStopOvers,maxTransitTime);
              delete train_seq[source].train_code;
              train_seq[source].train_code=nullptr;
              source--;
            }
          }
          trains=trains->next;
        }
        stn=stn->next;
      }
      //----------------------------------------------------------------------------------
    }
    STN=STN_mem;
    //cout<<"Off "<<stnNameToIndex.getKeyAtIndex(STN->adjacentStnIndex)<<endl;
  }

  iteration--;
}

#endif
