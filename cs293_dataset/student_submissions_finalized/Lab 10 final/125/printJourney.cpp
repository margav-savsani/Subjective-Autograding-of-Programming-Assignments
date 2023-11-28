#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct queueNode{
  //node for the queue to be used for implementing BFS
  int val;
  int stop;
  listOfObjects<TrainInfoPerStation *>* journeys;
  listOfObjects<string>* stationNames;
  queueNode *next;
  queueNode *prev;
  queueNode(int val){
    stop = 0;
    this->val = val;
    next = prev = NULL;
  }
};
struct queue{
  //queue to be used for implementing BFS
  queueNode* head;
  queueNode* tail;
  bool isEmpty;

  queue(){
    //default constructor
    head = tail = NULL;
    isEmpty = true;
  }

  void insert(int x, TrainInfoPerStation * jrny, TrainInfoPerStation * o_jrny, int change){
    //Insert an element in the queue
    queueNode *new_node = new queueNode(x);

    listOfObjects<TrainInfoPerStation *> * jrn = head->journeys;
    while(jrn->prev!=NULL){
      jrn = jrn->prev;
    }
    if(jrn->next==NULL){
      new_node->journeys = new listOfObjects<TrainInfoPerStation *>(o_jrny);
      new_node->journeys->next = new listOfObjects<TrainInfoPerStation *>(jrny);
      new_node->journeys->next->prev = new_node->journeys;
      new_node->journeys = new_node->journeys->next;
      new_node->journeys->next = NULL;
      new_node->stop = change;
    }
    else{
      new_node->journeys = new listOfObjects<TrainInfoPerStation *>(jrn->object);
      jrn = jrn->next;
      while(jrn->next!=NULL){
        new_node->journeys->next = new listOfObjects<TrainInfoPerStation *>(jrn->object);
        new_node->journeys->next->prev = new_node->journeys;
        new_node->journeys = new_node->journeys->next;
        jrn = jrn->next;
      }
      new_node->journeys->next = new listOfObjects<TrainInfoPerStation *>(o_jrny);
      new_node->journeys->next->prev = new_node->journeys;
      new_node->journeys = new_node->journeys->next;
      new_node->journeys->next = new listOfObjects<TrainInfoPerStation *>(jrny);
      new_node->journeys->next->prev = new_node->journeys;
      new_node->journeys = new_node->journeys->next;
      new_node->journeys->next = NULL;
      new_node->stop = change;
    }

    tail->next = new_node;
    tail->next->prev = tail;
    tail = tail->next;
  }

  void insert1(int x, TrainInfoPerStation * jrny){
    //Insert an element in the queue
    if(isEmpty){
      queueNode *new_node = new queueNode(x);
      new_node->journeys = new listOfObjects<TrainInfoPerStation *>(jrny);
      head = tail = new_node;
      isEmpty = false;
      return;
    }
    queueNode *new_node = new queueNode(x);
    new_node->journeys = new listOfObjects<TrainInfoPerStation *>(jrny);
    tail->next = new_node;
    tail->next->prev = tail;
    tail = tail->next;
  }

  void pop(){
    //delete an element from the queue
    if(isEmpty) return;
    if(head->next==NULL){
      head = tail = NULL;
      isEmpty = true;
      return;
    }
    head = head->next;
  }
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  // insert your code here
  int start_index = stnNameToIndex.get(srcStnName)->value;
  listOfObjects<listOfObjects<TrainInfoPerStation *> *> *journeys = NULL;
  listOfObjects<StationConnectionInfo *> *next_stations = adjacency[start_index].toStations;
  queue q;

  while(next_stations!=NULL){
    //adding all the initial journeys from the source
    listOfObjects<TrainInfoPerStation* >* trains = next_stations->object->trains;
    while(trains!=NULL){
      q.insert1(next_stations->object->adjacentStnIndex,trains->object);
      trains = trains->next;
    }
    next_stations = next_stations->next;
  }

  while(!q.isEmpty){
    listOfObjects<StationConnectionInfo* > *next_station = adjacency[q.head->val].toStations;
    if(stnNameToIndex.getKeyAtIndex(q.head->val)==destStnName){
      //adding the journey if it ends at the destination and continuing
      if(journeys==NULL) journeys = new listOfObjects<listOfObjects<TrainInfoPerStation *> *> (q.head->journeys);
      else{
        journeys->next = new listOfObjects<listOfObjects<TrainInfoPerStation *> *> (q.head->journeys);
        journeys->next->prev = journeys;
        journeys = journeys->next;
      }
      q.pop();
      continue;
    }
    while(next_station!=NULL){
      listOfObjects<TrainInfoPerStation* >* trains = next_station->object->trains;
      bool arr_days[7];
      int arr_time;
      listOfObjects<TrainInfoPerStation* >* time_finder = next_station->object->trains;
      while(time_finder!=NULL){
        if(time_finder->object->journeyCode == q.head->journeys->object->journeyCode){
          for(int i = 0; i<7; i++){
            arr_days[i] = time_finder->object->daysOfWeek[i];
          }
          arr_time = time_finder->object->arrTime;
        }
        time_finder = time_finder->next;
      }
      while(trains!=NULL){
        //Adding the journey if same journeyCode
        if(q.head->journeys->object->journeyCode==trains->object->journeyCode){
          if(trains->object->arrTime<=trains->object->depTime){
            for(int i = 0; i < 7; i++){
              if(!arr_days[i]) continue;
              TrainInfoPerStation *new_train = new TrainInfoPerStation(trains->object->journeyCode,trains->object->stopSeq,trains->object->arrTime,trains->object->depTime);
              TrainInfoPerStation *old_train = new TrainInfoPerStation(q.head->journeys->object->journeyCode,q.head->journeys->object->stopSeq,q.head->journeys->object->arrTime,q.head->journeys->object->depTime);
              for(int k = 0; k < 7; k++){
                new_train->daysOfWeek[k] = false;
              }
              new_train->daysOfWeek[i] = true;
              for(int k = 0; k < 7; k++){
                old_train->daysOfWeek[k] = false;
              }
              old_train->daysOfWeek[i] = true;
              q.insert(next_station->object->adjacentStnIndex,new_train,old_train,q.head->stop);
              if(q.tail->journeys->prev->prev!=NULL) break;
            }
          }
          else{
            for(int i = 0; i < 7; i++){
              if(!arr_days[i]) continue;
              TrainInfoPerStation *new_train = new TrainInfoPerStation(trains->object->journeyCode,trains->object->stopSeq,trains->object->arrTime,trains->object->depTime);
              TrainInfoPerStation *old_train = new TrainInfoPerStation(q.head->journeys->object->journeyCode,q.head->journeys->object->stopSeq,q.head->journeys->object->arrTime,q.head->journeys->object->depTime);
              for(int k = 0; k < 7; k++){
                new_train->daysOfWeek[k] = false;
              }
              new_train->daysOfWeek[i] = true;
              for(int k = 0; k < 7; k++){
                old_train->daysOfWeek[k] = false;
              }
              old_train->daysOfWeek[i] = true;
              q.insert(next_station->object->adjacentStnIndex,new_train,old_train,q.head->stop);
              if(q.tail->journeys->prev->prev!=NULL) break;
            }
          }
        }
        //Adding the journey if number of stop overs doesn't exceed the limit
        else if(q.head->stop<maxStopOvers){
          for(int i = 0; i < 7; i++){
            if(!arr_days[i]) continue;
            for(int j = 0; j < 7; j++){
              if(!trains->object->daysOfWeek[j]) continue;
              if((2400*(j-i)+ trains->object->depTime - arr_time + 7*2400)%(2400*7) <= maxTransitTime*100){
                TrainInfoPerStation *new_train = new TrainInfoPerStation(trains->object->journeyCode,trains->object->stopSeq,trains->object->arrTime,trains->object->depTime);
                TrainInfoPerStation *old_train = new TrainInfoPerStation(q.head->journeys->object->journeyCode,q.head->journeys->object->stopSeq,q.head->journeys->object->arrTime,q.head->journeys->object->depTime);
                for(int k = 0; k < 7; k++){
                  new_train->daysOfWeek[k] = false;
                }
                new_train->daysOfWeek[j] = true;
                for(int k = 0; k < 7; k++){
                  old_train->daysOfWeek[k] = false;
                }
                old_train->daysOfWeek[i] = true;
                q.insert(next_station->object->adjacentStnIndex,new_train,old_train,q.head->stop+1);
              }
            }
          }
        }
        trains = trains->next;
      }
      next_station = next_station->next;
    }
    q.pop();
  }

  //printing the journeys:
  if(journeys==NULL){
    cout << "No Journeys Available" << endl;
    return;
  }

  int index = 1;
  while(journeys!=NULL){
    listOfObjects<TrainInfoPerStation *> *x = journeys->object;
    cout << RED << "Journey " << index << '\n' << '\n';
    while(x->prev!=NULL){
      x = x->prev;
    }
    int stop = 1;
    while(x!=NULL){
      cout << GREEN << "Station "<< stop << ": " <<'\n';
      cout << "Journey Code: " << x->object->journeyCode;
      cout << '\n';
      if(x->object->daysOfWeek[0]) cout << "Day: Sunday\n";
      if(x->object->daysOfWeek[1]) cout << "Day: Monday\n";
      if(x->object->daysOfWeek[2]) cout << "Day: Tuesday\n";
      if(x->object->daysOfWeek[3]) cout << "Day: Wednesday\n";
      if(x->object->daysOfWeek[4]) cout << "Day: Thursday\n";
      if(x->object->daysOfWeek[5]) cout << "Day: Friday\n";
      if(x->object->daysOfWeek[6]) cout << "Day: Saturday\n";
      cout << BLUE;
      if(x->object->arrTime==-1) cout << "Train starts from here and leaves the station at: " << x->object->depTime;
      else cout << "Train arrives at the station at: " << x->object->arrTime <<  ", and leaves the station at: " << x->object->depTime;
      if(x->object->arrTime>x->object->depTime) cout << "(next day)";
      cout << "\n\n";
      stop++;
      x = x->next;
    }
    journeys = journeys->prev;
    cout << "---------" << endl << endl;
    index++;
  }
  cout << RESET;

  return;
}

#endif
