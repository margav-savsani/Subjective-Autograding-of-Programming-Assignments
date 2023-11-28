#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <queue>

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){
  
  cout << "Each block seperated by blank lines represent a journey from source to destination" << endl;
  cout << "Each block contains an odd number of lines(day,detail included as one line)" << endl;
  cout << "The first line gives the day and details of train to board on the sourcec station" << endl;
  cout << "The other even lines ask the user to get out of that train on that day at the given arrival time" << endl;
  cout << "The other odd lines ask the user to get into that train on that day at the departure time" << endl;
  listOfObjects<TrainInfoPerStation*> *finaltrains =nullptr;
  deque<TrainInfoPerStation *> final;
  
  int scrindex = this->stnNameToIndex.get(srcStnName)->value;
  int destindex = this->stnNameToIndex.get(destStnName)->value;
  deque<int> q_stn;
  deque<TrainInfoPerStation *> q_train;
  deque<int> q_changed;
  deque<listOfObjects<TrainInfoPerStation*> *> q_changedfrom;
  q_stn.push_back(scrindex);
  q_train.push_back(nullptr);
  q_changed.push_back(0);
  q_changedfrom.push_back(nullptr);
  while(q_stn.size() > 0){

    int recent_stn = q_stn.front();
    q_stn.pop_front();
    TrainInfoPerStation * recent_train = q_train.front();
    q_train.pop_front();
    int recent_changed = q_changed.front();
    q_changed.pop_front();
    listOfObjects<TrainInfoPerStation*> * recent_trainchanged = q_changedfrom.front();
    q_changedfrom.pop_front();

    listOfObjects<StationConnectionInfo *> *temp_stnptr =  this->adjacency[recent_stn].toStations; 
    if(recent_stn == destindex){
          printStationInfo(recent_trainchanged);
    }
    while(temp_stnptr != nullptr){
      listOfObjects<TrainInfoPerStation*> *temp_trainptr = temp_stnptr->object->trains;
      while(temp_trainptr != nullptr){

        //adding all trains from the source
        if (recent_train == nullptr){
          for (int i=0; i<7; i++){
            if (temp_trainptr->object->daysOfWeek[i]==1){
              TrainInfoPerStation* daytrain = new TrainInfoPerStation(temp_trainptr->object->journeyCode, temp_trainptr->object->stopSeq,temp_trainptr->object->arrTime, temp_trainptr->object->depTime);
              daytrain->daysOfWeek[i]=1;
              q_stn.push_back(temp_stnptr->object->adjacentStnIndex);
              q_train.push_back(daytrain);
              q_changed.push_back(0);
              listOfObjects<TrainInfoPerStation*> *tl = new listOfObjects<TrainInfoPerStation*>(daytrain);
              q_changedfrom.push_back(tl);
            }
          }
        }
        else{
          // continuting in the same train
          if (temp_trainptr->object->journeyCode == recent_train->journeyCode){
            for (int i=0; i<7; i++){
            if (temp_trainptr->object->daysOfWeek[i]==1 && recent_train->daysOfWeek[i]==1 && recent_train->depTime < temp_trainptr->object->arrTime){
            
            TrainInfoPerStation* daytrain = new TrainInfoPerStation(temp_trainptr->object->journeyCode, temp_trainptr->object->stopSeq,temp_trainptr->object->arrTime, temp_trainptr->object->depTime);
            daytrain->daysOfWeek[i]=1;
            q_stn.push_back(temp_stnptr->object->adjacentStnIndex);
            q_train.push_back(daytrain);
            q_changed.push_back(recent_changed);
            
            q_changedfrom.push_back(recent_trainchanged);
            }
            else if (temp_trainptr->object->daysOfWeek[(i+1)%7]==1 && recent_train->daysOfWeek[i]==1 && recent_train->depTime > temp_trainptr->object->arrTime){
            
            TrainInfoPerStation* daytrain = new TrainInfoPerStation(temp_trainptr->object->journeyCode, temp_trainptr->object->stopSeq,temp_trainptr->object->arrTime, temp_trainptr->object->depTime);
            daytrain->daysOfWeek[i]=1;
            q_stn.push_back(temp_stnptr->object->adjacentStnIndex);
            q_train.push_back(daytrain);
            q_changed.push_back(recent_changed);
            
            q_changedfrom.push_back(recent_trainchanged);
            }
            }
          }
          // switching train
          else if (recent_changed <= maxStopOvers ){
            for (int i=0; i<7; i++){
            if (temp_trainptr->object->daysOfWeek[i]==1){
            listOfObjects<StationConnectionInfo *> *ts = this->adjacency[recent_stn].fromStations;
            while(ts!= nullptr){
              listOfObjects<TrainInfoPerStation*>* t = ts->object->trains;
              while(t != nullptr){
                if (t->object->journeyCode == recent_train->journeyCode){
                  for (int j=0; j<7;j++){
                  if(t->object->daysOfWeek[j]==1){
                    float waittime = (i-j)*24 + float((int(-1*t->object->arrTime/100) + int(temp_trainptr->object->depTime/100))) + float((-1*t->object->arrTime%100 + temp_trainptr->object->depTime%100)/60);
                    if(waittime <= maxTransitTime && waittime >= 0){
                      for(int k=0; k<7; k++){
                        if(recent_train->daysOfWeek[k]==1 && recent_train->depTime < t->object->arrTime){
                           if(k==j){
                            TrainInfoPerStation* cdt = new TrainInfoPerStation(t->object->journeyCode, t->object->stopSeq,t->object->arrTime, t->object->depTime);
                            cdt->daysOfWeek[j]=1;
                            listOfObjects<TrainInfoPerStation*> *tl = new listOfObjects<TrainInfoPerStation*>(cdt);
                            TrainInfoPerStation* daytrain = new TrainInfoPerStation(temp_trainptr->object->journeyCode, temp_trainptr->object->stopSeq,temp_trainptr->object->arrTime, temp_trainptr->object->depTime);
                            daytrain->daysOfWeek[i]=1;
                            listOfObjects<TrainInfoPerStation*> *tl1 = new listOfObjects<TrainInfoPerStation*>(daytrain);
                            tl->next = recent_trainchanged;
                            tl1->next = tl;
                            q_changedfrom.push_back(tl1);
                            q_stn.push_back(temp_stnptr->object->adjacentStnIndex);
                            q_train.push_back(temp_trainptr->object);
                            q_changed.push_back(recent_changed+1);

                           }
                        }
                        else if(recent_train->daysOfWeek[k]==1 && recent_train->depTime > t->object->arrTime){
                           if((k+1)%7==j){
                            TrainInfoPerStation* cdt = new TrainInfoPerStation(t->object->journeyCode, t->object->stopSeq,t->object->arrTime, t->object->depTime);
                            cdt->daysOfWeek[j]=1;
                            listOfObjects<TrainInfoPerStation*> *tl = new listOfObjects<TrainInfoPerStation*>(cdt);
                            TrainInfoPerStation* daytrain = new TrainInfoPerStation(temp_trainptr->object->journeyCode, temp_trainptr->object->stopSeq,temp_trainptr->object->arrTime, temp_trainptr->object->depTime);
                            daytrain->daysOfWeek[i]=1;
                            listOfObjects<TrainInfoPerStation*> *tl1 = new listOfObjects<TrainInfoPerStation*>(daytrain);
                            tl->next = recent_trainchanged;
                            tl1->next = tl;
                            q_changedfrom.push_back(tl1);
                            q_stn.push_back(temp_stnptr->object->adjacentStnIndex);
                            q_train.push_back(temp_trainptr->object);
                            q_changed.push_back(recent_changed+1);

                           }
                        }
                      }
                    } 
                  }
                  }
                }
                t = t->next;
              }
              ts = ts->next;           
            }
          }
          }
          }
        }
        temp_trainptr = temp_trainptr->next;
      }
      temp_stnptr = temp_stnptr->next;
    }
  
}
}
#endif
