#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
class tostnandtrain{
public:
  TrainInfoPerStation* train;
  int index;

  tostnandtrain(TrainInfoPerStation* train, int index) {
    this->train=train;
    this->index=index;
  }
};
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  int srcStnindex=stnNameToIndex.get(srcStnName)->value, destStnindex=stnNameToIndex.get(destStnName)->value;
  
  listOfObjects<TrainInfoPerStation *> *final=nullptr;
  listOfObjects<TrainInfoPerStation *> *startfinal=nullptr;
  listOfObjects<tostnandtrain *> *head,*tail;
  tostnandtrain *init=new tostnandtrain(nullptr,srcStnindex);
  tail=new listOfObjects<tostnandtrain *>(init);
  head=tail;

  while (head!=nullptr) {
    int index=head->object->index;
    TrainInfoPerStation *trainid=head->object->train;
    StationAdjacencyList stn=adjacency[index];
    listOfObjects<StationConnectionInfo *> *adjstns=adjacency[index].toStations;
    while(adjstns!=nullptr) {
      int adjindex=adjstns->object->adjacentStnIndex;
      listOfObjects<TrainInfoPerStation *> *trains=adjstns->object->trains;
      while (trains!=nullptr) {
        if (trainid==nullptr || trainid->journeyCode==trains->object->journeyCode) {
          tostnandtrain *new_=new tostnandtrain(trains->object,adjindex);
          tail->next=new listOfObjects<tostnandtrain *>(new_);
          if (adjindex==destStnindex) {
            if (final==nullptr) {
              final=new listOfObjects<TrainInfoPerStation *>(trains->object);
              startfinal=final;
            }
            else {
              final->next=new listOfObjects<TrainInfoPerStation *>(trains->object);
              final=final->next;
            }
          }
          tail=tail->next;
        }
        trains=trains->next;
      }
      adjstns=adjstns->next;
    }

    head=head->next;
  }

  if (startfinal==nullptr) {
    cout<<"No direct journeys available\n";
  }
  printStationInfo(startfinal);
  return;
}
