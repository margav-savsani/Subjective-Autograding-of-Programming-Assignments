#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif
#include <vector>
#include <queue>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class station{
    public:
    int index;
    listOfObjects<TrainInfoPerStation*>* trains;
    station( int i, listOfObjects<TrainInfoPerStation*>* tra){
        index = i;
        trains = tra;

    }
    //one member func
    bool present(int jc){
        listOfObjects<TrainInfoPerStation * > *temp = trains;
        while(temp){
            if(temp->object->journeyCode==jc) return true;
            temp = temp->next;
        }
        return false;
    }

};

void Planner::printDirectJourneys(string srcStnName, string destStnName){

  int srcIndex=stnNameToIndex.get(srcStnName)->value;
  int destIndex=stnNameToIndex.get(destStnName)->value;

  listOfObjects<StationConnectionInfo *> *src_neighbours=adjacency[srcIndex].toStations;

  station *st = new station(0, nullptr);
  listOfObjects<station*> *q = new listOfObjects<station*>( st );

  listOfObjects<TrainInfoPerStation *> *directjourneys=nullptr;
  listOfObjects<TrainInfoPerStation *> *directjourneys_dummy=nullptr;

  while(src_neighbours!=nullptr){
    station *st = new station(src_neighbours->object->adjacentStnIndex, src_neighbours->object->trains);

    if(src_neighbours->object->adjacentStnIndex==destIndex){

        listOfObjects<TrainInfoPerStation *> *tempto = src_neighbours->object->trains;
        listOfObjects<TrainInfoPerStation*>* tempfrom = adjacency[destIndex].fromStations->object->trains;
        listOfObjects<TrainInfoPerStation *> *tosave = new listOfObjects<TrainInfoPerStation *>(*src_neighbours->object->trains);
        listOfObjects<TrainInfoPerStation *> *tosaveitr = tosave;
        int i=0;

        while(tempto && tempfrom){

            tempfrom = adjacency[destIndex].fromStations->object->trains;

            while(tempfrom){
                if(tempfrom->object->journeyCode == tempto->object->journeyCode){
                    TrainInfoPerStation *tr = new TrainInfoPerStation(*tempfrom->object);
                    if(i==0)
                        tosaveitr = new listOfObjects<TrainInfoPerStation *>(tr);
                    else{
                        tosaveitr = new listOfObjects<TrainInfoPerStation *>(tr);
                        tosaveitr = tosaveitr->next;
                    }
                }
                tempfrom = tempfrom->next;
            }
            tempto = tempto->next;

        }
        directjourneys = new listOfObjects<TrainInfoPerStation *>(*tosave);
        // directjourneys_dummy->next = valid_trains;
        directjourneys_dummy = directjourneys;

    }
    q->next = new listOfObjects<station *>(st);
    src_neighbours=src_neighbours->next;

  }

  while(q){

    station* curr_station = q->object;
    //will pop later
    listOfObjects<StationConnectionInfo *>* curr_neigh = adjacency[curr_station->index].toStations;
    listOfObjects<TrainInfoPerStation *>* trainsTocurrent = curr_station->trains;

    while (curr_neigh!=NULL)
    {

        int neighIndex = curr_neigh->object->adjacentStnIndex;
        listOfObjects<TrainInfoPerStation *> *trainsOfNeigh = curr_neigh->object->trains;
        listOfObjects<TrainInfoPerStation*>* valid_trains = nullptr;

        while(trainsOfNeigh){

            if(curr_station->present(trainsOfNeigh->object->journeyCode)){
                if(valid_trains==NULL)
                    valid_trains = new listOfObjects<TrainInfoPerStation *>(trainsOfNeigh->object);
                else{
                    valid_trains->next = new listOfObjects<TrainInfoPerStation *>(trainsOfNeigh->object);
                    valid_trains = valid_trains->next;
                }
            }
            trainsOfNeigh = trainsOfNeigh->next;

        }

        if(valid_trains){

            if(neighIndex == destIndex){
                if(directjourneys==NULL){
                    directjourneys = valid_trains;
                    directjourneys_dummy = directjourneys;
                }
                else{
                    directjourneys_dummy->next = valid_trains;
                    directjourneys_dummy = directjourneys_dummy->next;
                }
            }
            station *stn = new station(neighIndex, valid_trains);
            listOfObjects<station*>*a = q;
            while(a->next){
                a = a->next;
            }
            q->next = new listOfObjects<station*> (stn);

        }
        curr_neigh = curr_neigh->next;

    }
    q = q->next;

  }

  if(directjourneys==NULL){
    cout<<"No Journeys Available"<<endl;
  }
  else{
      //while(directjourneys!=nullptr){
      printStationInfo(directjourneys);
      //cout<<endl;
      //directjourneys=directjourneys->next;
    }
}
    


#endif
