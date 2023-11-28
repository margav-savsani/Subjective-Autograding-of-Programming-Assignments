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

void Planner::printDirectJourneys(string srcStnName, string destStnName) {
  int source = stnNameToIndex.get(srcStnName)->value;
  int destination = stnNameToIndex.get(destStnName)->value;
  bool directTrains = 0;
  listOfObjects<TrainInfoPerStation *> *finalDirectTrains = NULL;

  listOfObjects<int> *currentOutTrains = NULL;

  listOfObjects<int>* x = NULL;
  listOfObjects<StationConnectionInfo*>* y = adjacency[source].toStations;
  while (y != NULL) {
      listOfObjects<TrainInfoPerStation*>* z = y->object->trains;
      while (z != NULL) {
          if (currentOutTrains == NULL) {
              currentOutTrains = x = new listOfObjects<int>(z->object->journeyCode);
          }
          else {
              x->next = new listOfObjects<int>(z->object->journeyCode);
              x = x->next;
          }
          z = z->next;
      }
      y = y->next;
  }

  while (currentOutTrains != NULL) {
        int train = currentOutTrains->object;         // journeyCode, not index
        queue<int> BFSqueue;
        BFSqueue.push(source);

        while (BFSqueue.size() != 0) {
            int mainNode = BFSqueue.front();
            listOfObjects<StationConnectionInfo*>* listOutTrainsIterator = adjacency[mainNode].toStations;

            while (listOutTrainsIterator != NULL) {
                int adjacentStation = listOutTrainsIterator->object->adjacentStnIndex; 
                listOfObjects<TrainInfoPerStation*>* listOutTrains = listOutTrainsIterator->object->trains;

                while (listOutTrains != NULL) {
                    if (listOutTrains->object->journeyCode == train) {
                        if (adjacentStation == destination) {
                            if (!directTrains){
                              listOfObjects<TrainInfoPerStation *> *trainsFromSource = stationInfo[source];
                              while(trainsFromSource != NULL){
                                if (trainsFromSource->object->journeyCode == train){
                                  finalDirectTrains = new listOfObjects<TrainInfoPerStation *>(trainsFromSource->object);
                                  break;
                                }
                                trainsFromSource = trainsFromSource->next;
                              }
                              directTrains = true;
                            }
                            else {
                              listOfObjects<TrainInfoPerStation *> *trainsFromSource = stationInfo[source];
                              while(trainsFromSource != NULL){
                                if (trainsFromSource->object->journeyCode == train){
                                  finalDirectTrains->next = new listOfObjects<TrainInfoPerStation *>(trainsFromSource->object);
                                  break;
                                }
                                trainsFromSource = trainsFromSource->next;
                              }
                            }
                        }
                        else {
                            BFSqueue.push(adjacentStation);
                        }
                        break;
                    }
                    listOutTrains = listOutTrains->next;
                }
                listOutTrainsIterator = listOutTrainsIterator->next;
            }
            BFSqueue.pop();
        }
        currentOutTrains = currentOutTrains->next;
    }

  if (directTrains){
    listOfObjects<TrainInfoPerStation *> *x = finalDirectTrains;
    while(x!=NULL){
      printStationInfo(x);
    }
  }
  else {
    cout << "No direct journeys available\n";
  }
}

#endif
