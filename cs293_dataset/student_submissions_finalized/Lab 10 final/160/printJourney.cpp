#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;
#ifndef PLANNER_H
#include "planner.h"
#endif
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

class trainobject{
public:
  int stop_overs;
  int transit_time;
  listOfObjects<int*> *indexes;
  listOfObjects<TrainInfoPerStation*> *reqtrains;
  listOfObjects<int*> *indexes_end;
  listOfObjects<TrainInfoPerStation*> *reqtrains_end;
  trainobject(){
    stop_overs = 0;
    transit_time=-1;
    reqtrains = nullptr;
    reqtrains_end = nullptr;
    indexes = nullptr;
    indexes_end = nullptr;
  }
};

class trainnode{
public:
  int station_index;
  listOfObjects<trainobject *> *ttrain;
  listOfObjects<trainobject *> *ttrain_end;
  trainnode(int index){
    station_index = index;
    ttrain = nullptr;
    ttrain_end = nullptr;
  }
};
// Class made to use as the nodes in a queue used for listings
// Contains information about the index of the station and the reqtrains leaving from the station which also departed from the source station
// Has a doubly linked list of TrainInfoPerStation

listOfObjects<TrainInfoPerStation*> *find(listOfObjects<TrainInfoPerStation *> *train, listOfObjects<TrainInfoPerStation *> *reqtrains){
  while (reqtrains != nullptr){
    if (train->object->journeyCode == reqtrains->object->journeyCode){
      return (new listOfObjects<TrainInfoPerStation *>(reqtrains->object));
    }
    reqtrains = reqtrains->next;
  }
  return nullptr;
}

// // The recursive function which performs listings and returns a list of TrainInfoPerStation with direct ttrain
void listings(listOfObjects<TrainInfoPerStation *> **stationInfo, listOfObjects<trainnode *> *list, listOfObjects<trainnode *> *end, StationAdjacencyList *adjacency, listOfObjects<trainobject *> **journeys_available, listOfObjects<trainobject *> **journeys_available_tail,int transit_time, int stop_overs, int source_index, int dest_index){
  if (list != nullptr){ // Continues while list is not empty
    int index = list->object->station_index;
    listOfObjects<StationConnectionInfo *> *adjtrainlists = adjacency[index].toStations;
    while (adjtrainlists != nullptr){
      if (adjtrainlists->object->adjacentStnIndex == dest_index){ // If destination found add to trains_available list
        if (list->object->station_index == source_index && list->object->ttrain->object->reqtrains->next == nullptr){
          listOfObjects<trainobject *> *point = list->object->ttrain;
          while (point != nullptr){
            listOfObjects<trainobject *> *new_object = new listOfObjects<trainobject *>(point->object);
            listOfObjects<TrainInfoPerStation *> *reqtrains = adjtrainlists->object->trains;
            while (reqtrains != nullptr){
              if (reqtrains->object->journeyCode == new_object->object->reqtrains_end->object->journeyCode){
                if (new_object->object->stop_overs <= stop_overs && new_object->object->transit_time <= transit_time){
                  if (*journeys_available == nullptr){
                    *journeys_available = new_object;
                    *journeys_available_tail = new_object;
                  }
                  else{
                    (*journeys_available_tail)->next = new_object;
                    *journeys_available_tail = (*journeys_available_tail)->next;
                  }
                }
              }
              reqtrains = reqtrains->next;
            }
            point = point->next;
          }
        }
        else{
          listOfObjects<trainobject *> *point = list->object->ttrain;
          while (point != nullptr){
            listOfObjects<TrainInfoPerStation *> *reqtrains = adjtrainlists->object->trains;
            while (reqtrains != nullptr){
              trainobject *new_obj = new trainobject();
              listOfObjects<TrainInfoPerStation *> *t = point->object->reqtrains;
              while (t != nullptr){
                if (new_obj->reqtrains == nullptr){
                  listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                  new_obj->reqtrains = tr;
                  new_obj->reqtrains_end = tr;
                }
                else{
                  listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                  new_obj->reqtrains_end->next = tr;
                  new_obj->reqtrains_end = new_obj->reqtrains_end->next;
                }
                t = t->next;
              }
              listOfObjects<int *> *i = point->object->indexes;
              while (i != nullptr){
                if (new_obj->indexes == nullptr){
                  listOfObjects<int *> *ij = new listOfObjects<int *>(i->object);
                  new_obj->indexes = ij;
                  new_obj->indexes_end = ij;
                }
                else{
                  listOfObjects<int *> *ij = new listOfObjects<int *>(i->object);
                  new_obj->indexes_end->next = ij;
                  new_obj->indexes_end = new_obj->indexes_end->next;
                }
                i = i->next;
              }
              new_obj->stop_overs = point->object->stop_overs;
              new_obj->transit_time=point->object->transit_time;
              listOfObjects<trainobject *> *new_object = new listOfObjects<trainobject *>(new_obj);
              if (reqtrains->object->journeyCode != new_object->object->reqtrains_end->object->journeyCode){
                if (new_object->object->stop_overs < stop_overs && new_object->object->transit_time <= transit_time){
                  listOfObjects<TrainInfoPerStation *> *train = find(reqtrains, stationInfo[index]);
                  bool allowed = true;
                  if (train->object->depTime - new_object->object->reqtrains_end->object->arrTime > transit_time){
                    allowed = false;
                  }
                  listOfObjects<TrainInfoPerStation *> *new_train = new listOfObjects<TrainInfoPerStation *>(reqtrains->object);
                  int t=new_object->object->reqtrains_end->object->depTime;
                  new_object->object->reqtrains_end->next = new_train;
                  new_train->prev = new_object->object->reqtrains_end;
                  new_object->object->reqtrains_end = new_object->object->reqtrains_end->next;
                  int *num = new int(list->object->station_index);
                  listOfObjects<int *> *new_int = new listOfObjects<int *>(num);
                  new_object->object->indexes_end->next = new_int;
                  new_int->prev = new_object->object->indexes_end;
                  new_object->object->indexes_end = new_object->object->indexes_end->next;
                  new_object->object->stop_overs++;
                  new_object->object->transit_time+=(new_train->object->arrTime-t);
                  if (allowed){
                    if (*journeys_available == nullptr){
                      *journeys_available = new_object;
                      *journeys_available_tail = new_object;
                    }
                    else{
                      (*journeys_available_tail)->next = new_object;
                      *journeys_available_tail = (*journeys_available_tail)->next;
                    }
                  }
                }
              }
              else{
                if (new_object->object->stop_overs <= stop_overs && new_object->object->transit_time <= transit_time){
                  if (*journeys_available == nullptr){
                    *journeys_available = new_object;
                    *journeys_available_tail = new_object;
                  }
                  else{
                    (*journeys_available_tail)->next = new_object;
                    *journeys_available_tail = (*journeys_available_tail)->next;
                  }
                }
              }
              reqtrains = reqtrains->next;
            }
            point = point->next;
          }
        }
      }
      else{
        trainnode *new_node = new trainnode(adjtrainlists->object->adjacentStnIndex);
        if (list->object->station_index == source_index && list->object->ttrain->object->reqtrains->next == nullptr){
          listOfObjects<trainobject *> *point = list->object->ttrain;
          while (point != nullptr){
            listOfObjects<TrainInfoPerStation *> *reqtrains = adjtrainlists->object->trains;
            while (reqtrains != nullptr){
              trainobject *new_obj = new trainobject();
              listOfObjects<TrainInfoPerStation *> *t = point->object->reqtrains;
              while (t != nullptr){
                if (new_obj->reqtrains == nullptr){
                  listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                  new_obj->reqtrains = tr;
                  new_obj->reqtrains_end = tr;
                }
                else{
                  listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                  new_obj->reqtrains_end->next = tr;
                  new_obj->reqtrains_end = new_obj->reqtrains_end->next;
                }
                t = t->next;
              }
              listOfObjects<int *> *i = point->object->indexes;
              while (i != nullptr){
                if (new_obj->indexes == nullptr){
                  listOfObjects<int *> *ij = new listOfObjects<int *>(i->object);
                  new_obj->indexes = ij;
                  new_obj->indexes_end = ij;
                }
                else{
                  listOfObjects<int *> *ij = new listOfObjects<int *>(i->object);
                  new_obj->indexes_end->next = ij;
                  new_obj->indexes_end = new_obj->indexes_end->next;
                }
                i = i->next;
              }
              listOfObjects<trainobject *> *new_object = new listOfObjects<trainobject *>(new_obj);
              if (reqtrains->object->journeyCode == new_object->object->reqtrains_end->object->journeyCode){
                if (new_node->ttrain == nullptr){
                  new_node->ttrain = new_object;
                  new_node->ttrain_end = new_object;
                }
                else{
                  new_node->ttrain_end->next = new_object;
                  new_node->ttrain_end = new_node->ttrain_end->next;
                }
              }
              reqtrains = reqtrains->next;
            }
            point = point->next;
          }
        }
        else{
          listOfObjects<trainobject *> *point = list->object->ttrain;
          while (point != nullptr){
            listOfObjects<TrainInfoPerStation *> *reqtrains = adjtrainlists->object->trains;
            while (reqtrains != nullptr){
              trainobject *new_obj = new trainobject();
              listOfObjects<TrainInfoPerStation *> *t = point->object->reqtrains;
              while (t != nullptr){
                if (new_obj->reqtrains == nullptr){
                  listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                  new_obj->reqtrains = tr;
                  new_obj->reqtrains_end = tr;
                }
                else{
                  listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                  new_obj->reqtrains_end->next = tr;
                  new_obj->reqtrains_end = new_obj->reqtrains_end->next;
                }
                t = t->next;
              }
              listOfObjects<int *> *i = point->object->indexes;
              while (i != nullptr){
                if (new_obj->indexes == nullptr){
                  listOfObjects<int *> *ij = new listOfObjects<int *>(i->object);
                  new_obj->indexes = ij;
                  new_obj->indexes_end = ij;
                }
                else{
                  listOfObjects<int *> *ij = new listOfObjects<int *>(i->object);
                  new_obj->indexes_end->next = ij;
                  new_obj->indexes_end = new_obj->indexes_end->next;
                }
                i = i->next;
              }
              new_obj->stop_overs = point->object->stop_overs;
              new_obj->transit_time=point->object->transit_time;
              listOfObjects<trainobject *> *new_object = new listOfObjects<trainobject *>(new_obj);
              if (reqtrains->object->journeyCode == new_object->object->reqtrains_end->object->journeyCode){
                if (new_object->object->stop_overs <= stop_overs && new_object->object->transit_time <= transit_time){
                  if (new_node->ttrain == nullptr){
                    new_node->ttrain = new_object;
                    new_node->ttrain_end = new_object;
                  }
                  else{
                    new_node->ttrain_end->next = new_object;
                    new_node->ttrain_end = new_node->ttrain_end->next;
                  }
                }
              }
              else{
                listOfObjects<TrainInfoPerStation *> *train = find(reqtrains, stationInfo[index]);
                listOfObjects<TrainInfoPerStation *> *new_train = new listOfObjects<TrainInfoPerStation *>(reqtrains->object);
                bool allowed = true;
                if (train->object->depTime - new_object->object->reqtrains_end->object->arrTime > transit_time){
                  allowed = false;
                }
                new_object->object->reqtrains_end->next = new_train;
                new_train->prev = new_object->object->reqtrains_end;
                int t=new_object->object->reqtrains_end->object->depTime;
                new_object->object->reqtrains_end = new_object->object->reqtrains_end->next;
                int *num = new int(list->object->station_index);
                listOfObjects<int *> *new_int = new listOfObjects<int *>(num);
                new_object->object->indexes_end->next = new_int;
                new_int->prev = new_object->object->indexes_end;
                new_object->object->indexes_end = new_int;
                new_object->object->stop_overs++;
                  new_object->object->transit_time+=(new_train->object->arrTime-t);
                if (new_object->object->stop_overs <= stop_overs && new_object->object->transit_time <= transit_time){
                  if (allowed){
                    if (new_node->ttrain == nullptr){
                      new_node->ttrain = new_object;
                      new_node->ttrain_end = new_object;
                    }
                    else{
                      new_node->ttrain_end->next = new_object;
                      new_node->ttrain_end = new_node->ttrain_end->next;
                    }
                  }
                }
              }
              reqtrains = reqtrains->next;
            }
            point = point->next;
          }
        }
        listOfObjects<trainnode *> *node = new listOfObjects<trainnode *>(new_node);
        if (node->object->ttrain != nullptr){
          end->next = node;
          end = node;
        }
      }
      adjtrainlists = adjtrainlists->next;
    }
    list = list->next;
    listings( stationInfo, list, end, adjacency, journeys_available, journeys_available_tail,transit_time, stop_overs, source_index, dest_index); // The recursive call
  }
  return;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){
  // insert your code here
  int source_index=(stnNameToIndex.get(srcStnName))->value;
  int dest_index=(stnNameToIndex.get(destStnName))->value;

  listOfObjects<trainobject *> *journeys_available = nullptr;
  listOfObjects<trainobject *> *journeys_available_tail = nullptr;
  
  trainnode *new_node = new trainnode(source_index);
  listOfObjects<trainnode *> *list = new listOfObjects<trainnode *>(new_node);
  listOfObjects<StationConnectionInfo *> *adjtrainlists = adjacency[source_index].toStations;
  listOfObjects<TrainInfoPerStation *> *source_trains = stationInfo[source_index];
  while (adjtrainlists != nullptr){ // Population the trainnode of the source station with reqtrains leaving from the source station
    listOfObjects<TrainInfoPerStation *> *reqtrains = adjtrainlists->object->trains;
    while (reqtrains != nullptr){
      listOfObjects<TrainInfoPerStation *> *train = find(reqtrains, source_trains);
      if (list->object->ttrain == nullptr){
        trainobject *new_obj = new trainobject();
        listOfObjects<TrainInfoPerStation *> *new_train = new listOfObjects<TrainInfoPerStation *>(train->object);
        int *num = new int(source_index);
        listOfObjects<int *> *new_index = new listOfObjects<int *>(num);
        new_obj->indexes = new_index;
        new_obj->indexes_end = new_index;
        new_obj->reqtrains = new_train;
        new_obj->reqtrains_end = new_train;
        listOfObjects<trainobject *> *new_object = new listOfObjects<trainobject *>(new_obj);
        list->object->ttrain = new_object;
        list->object->ttrain_end = new_object;
      }
      else{
        trainobject *new_obj = new trainobject();
        listOfObjects<TrainInfoPerStation *> *new_train = new listOfObjects<TrainInfoPerStation *>(train->object);
        int *num = new int(source_index);
        listOfObjects<int *> *new_index = new listOfObjects<int *>(num);
        new_obj->indexes = new_index;
        new_obj->indexes_end = new_index;
        new_obj->reqtrains = new_train;
        new_obj->reqtrains_end = new_train;
        listOfObjects<trainobject *> *new_object = new listOfObjects<trainobject *>(new_obj);
        new_object->next = list->object->ttrain;
        list->object->ttrain->prev = new_object;
        list->object->ttrain = new_object;
      }
      reqtrains = reqtrains->next;
    }
    adjtrainlists = adjtrainlists->next;
  }
  listOfObjects<trainnode *> *end;
  end = list;
  listings( stationInfo, list, end, adjacency, &journeys_available, &journeys_available_tail,maxTransitTime, maxStopOvers,source_index, dest_index); // Calling listings from the source station



  listOfObjects<trainobject *> *point = journeys_available;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  if (journeys_available == nullptr){
    cout << "NO JOURNIES" << endl;
  }
  else{
    while (point != nullptr){
      cout << "STOPS " << point->object->stop_overs << endl;
      cout << BLUE << "STARTS AT : " << RESET << endl;
      listOfObjects<int *> *stn_ptr= point->object->indexes;
      listOfObjects<TrainInfoPerStation *> *train = point->object->reqtrains;
      int i = 0;
      while (stn_ptr != nullptr){
        if (i != 0){
          cout << BLUE << "TRANSIT AT" << RESET << endl;
        }
        cout << stnNameToIndex.getKeyAtIndex(*stn_ptr->object) << endl;
        cout << RED << "Journey code: "  << RESET << train->object->journeyCode << " ";
        cout << RED << "Arrival Time: " << RESET;
        if (train->object->arrTime == -1){
          cout << "Starts";
        }
        else{
          cout << train->object->arrTime;
        }
        cout << RED << " Departure Time: " << RESET;
        if (train->object->depTime == -1){
          cout << "Ends";
        }
        else{
          cout << train->object->depTime;
        }
        cout << endl;
        stn_ptr = stn_ptr->next;
        train = train->next;
        i++;
      }
      train = point->object->reqtrains_end;
      cout << RED << "Day(s): " << " " <<RESET;
      for (int i = 0; i < 7; i++){
        if (train->object->daysOfWeek[i]){
          cout << days[i] << "  ";
        }
      }
      cout<<endl;
      cout << BLUE << "ENDS AT : " << RESET << endl;
      cout << stnNameToIndex.getKeyAtIndex(dest_index) << endl;
      point=point->next;
    }
  }
  return;
}

#endif