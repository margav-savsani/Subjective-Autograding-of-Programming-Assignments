#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void printjourney(listOfObjects<TrainInfoPerStation*>* station_list){                        //printjourney function ..copied from planner.cpp required for "recursive_find"
  listOfObjects<TrainInfoPerStation*>* currList = station_list;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  while (currList != nullptr) {
    TrainInfoPerStation* currInfo = currList->object;
    if (currInfo != nullptr) {
      cout << GREEN << "Day(s): " << RESET;
      for (int i=0; i<7; i++) {
	if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1) {
	cout << "Starts";
      }
      else {
	cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1) {
	cout << "Ends";
      }
      else {
	cout << currInfo->depTime;
      }
      cout << endl;
    }
    currList = currList->next;
  }
  cout << endl;
  cout << "====================================================================" << endl;
}

//suppose a train with journey code  c starts from station A and goes to station B ..given the journey_info at sttion A and list of trains coming to station B
//this function gives journey info at B ..if such journey do not exist return nullptr

TrainInfoPerStation* train_here(TrainInfoPerStation* a,listOfObjects<TrainInfoPerStation*>* trains){
  while(trains != nullptr){
    if(trains->object->journeyCode == a->journeyCode){
      TrainInfoPerStation* new_train = new TrainInfoPerStation(trains->object->journeyCode,trains->object->stopSeq,trains->object->arrTime,trains->object->depTime);
      for(int i=0 ; i < 7;i++){
        if(a->daysOfWeek[i]){
          if(new_train->arrTime > a->depTime){
            new_train->setDayOfWeek(i);
          }
          else{
            new_train->setDayOfWeek((i+1)%7);
          }
          return new_train;
        }
      }
    }
    trains = trains->next;
  }
  return nullptr;
}

//given two train info check if the given two journeys follows the given constraints
//if given two journeys have same journey code max_transit _time will be set to 24 hrs{ as told by prof}
//else we'll add transit time to arrival time of first and check if the 2nd train departs before the limit time
bool follows_transit_time(TrainInfoPerStation* a , TrainInfoPerStation * b , int time){
  
  if(a->journeyCode == b->journeyCode){
    time = 2400;
  }
  if(b->depTime < 0){
    return false;
  }
  if(time >= 2400*7){                                  //if transit time is 7 days ..other train can always be taken 
    return true;
  }
  int a_day = 0;
  int b_day = 0;
  int dept_time = 0;
  int hrs = 0;
  int min = 0;
  int a_time = a->arrTime;
  int b_time = b->depTime;
  for(int i = 0; i < 7; i++){
    if(a->daysOfWeek[i]){
      a_day = i;
    }
    if(b->daysOfWeek[i]){
      b_day = i;
    }
  }
  if(b_day < a_day){
    b_day += 7;
  }
  else if(b_day == a_day){
    if(a_time > b_time){
      b_day += 7;
    }
  }
  int dept_day = a_day + time/2400;
  time = time%2400;
  
  hrs = a->arrTime/100 + time/100;
  min = a->arrTime%100 + time%100;
  if(min >= 60){
    hrs++;
    min -= 60;
  }
  dept_time = hrs*100 + min;
  if(dept_time >= 2400){
    dept_time -= 2400;
    dept_day++;
  }
  if(dept_day > b_day)return true;
  if(dept_day == b_day){
    if(dept_time >= b_time)return true;
  }
  return false;

}


void recursive_find(StationAdjacencyList adjacency[],listOfObjects<TrainInfoPerStation *> *stationInfo[],TrainInfoPerStation* train ,int curr_stn_index , int count, int max_time , int dest_stn_ind,listOfObjects< TrainInfoPerStation*>* answer_tail,listOfObjects< TrainInfoPerStation*>* answer_head, int prev_stn_index){
  if(count == -1){           //if max srtop overs are finished ..return
    return;
  }

  listOfObjects<StationConnectionInfo*>* prev_stn = adjacency[curr_stn_index].fromStations;         //check all journeys info at the curr station
  while(prev_stn != nullptr){                                                                       //find the station from which train has come here
    if(prev_stn->object->adjacentStnIndex == prev_stn_index){
      break;
    }
    prev_stn = prev_stn->next;
  }
  // cout << "prev_stn_ind " << prev_stn->object->adjacentStnIndex << endl;
  TrainInfoPerStation* info_at_this_stn = train_here(train,prev_stn->object->trains);              //find corrosponding train at this station
  // cout << "hjsh " << info_at_this_stn->arrTime<< endl;
  if(info_at_this_stn == nullptr){    //if such train do not exist it means the train don't come here so return
    return;
  }
  if(curr_stn_index == dest_stn_ind){     // if this is the destination station.. print ans and return
    printjourney(answer_head);
    return;
  }
  listOfObjects<TrainInfoPerStation *> * trains = stationInfo[curr_stn_index];
  while (trains != nullptr){                                     //now split all the trains from given station and check all adjacent station for next station
    TrainInfoPerStation* curr_train = trains->object;
    for(int i = 0; i < 7;i++){
      if(curr_train->daysOfWeek[i]){
        TrainInfoPerStation* splited_train = new TrainInfoPerStation(curr_train->journeyCode,curr_train->stopSeq,curr_train->arrTime,curr_train->depTime);
        for(int j = 0; j< 7;j++){
          if (i == j){
            splited_train->daysOfWeek[j] = true;
          }
        }
        if(splited_train->depTime == -1){
          continue;
        }
        if(!follows_transit_time(info_at_this_stn,splited_train,max_time)){          //if the train do not satisfy the given constrain check next splitted train
          continue;
        }
        answer_tail->next = new listOfObjects<TrainInfoPerStation*>(splited_train);  // if it follows constrain add this train to answer
        answer_tail->next->prev = answer_tail;
        answer_tail = answer_tail->next;

        listOfObjects<StationConnectionInfo *> * adjacent = adjacency[curr_stn_index].toStations;
        while (adjacent != nullptr){
          int adj_stn_ind = adjacent->object->adjacentStnIndex;
          if(info_at_this_stn->journeyCode == splited_train->journeyCode){             //now if at this station we got valid train check adjacent station for next journey
            //if there was no change in train then do not reduce count else reduce it by 1
            recursive_find(adjacency,stationInfo,splited_train,adj_stn_ind,count,max_time,dest_stn_ind,answer_tail,answer_head,curr_stn_index);
          }
          else{
            recursive_find(adjacency,stationInfo,splited_train,adj_stn_ind,count - 1,max_time,dest_stn_ind,answer_tail,answer_head,curr_stn_index);
          }
          adjacent = adjacent->next;
        }
        answer_tail = answer_tail->prev;
        delete(answer_tail->next);
        answer_tail->next = nullptr;
        
      }
    }
    trains = trains->next;
  } 
  
}

//same as above recursive find function but this is base condition so have to write separately
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  int src_ind = stnNameToIndex.get(srcStnName)->value;              //get dictionary index of source station
  int dest_ind = stnNameToIndex.get(destStnName)->value;              //get dictionary index of destination station
  listOfObjects<TrainInfoPerStation *> * trains = stationInfo[src_ind];  //all trains from src stations
  //listOfObjects<StationConnectionInfo *> * adjacent = adjacency[src_ind].toStations; //list of all adjacent stations
  while (trains != nullptr){
    TrainInfoPerStation* curr_train = trains->object;
    for(int i = 0; i < 7;i++){
      if(curr_train->daysOfWeek[i]){
        TrainInfoPerStation* splited_train = new TrainInfoPerStation(curr_train->journeyCode,curr_train->stopSeq,curr_train->arrTime,curr_train->depTime);
        for(int j = 0; j< 7;j++){
          if (i == j){
            splited_train->daysOfWeek[j] = true;
          }
        }
        listOfObjects< TrainInfoPerStation*>* answer_head = nullptr;
        listOfObjects< TrainInfoPerStation*>* answer_tail = nullptr;
        if(splited_train->depTime == -1){
          continue;
        }
        answer_head= new listOfObjects<TrainInfoPerStation*> (splited_train);
        answer_tail = answer_head;
        // cout << "splitter gsdh" << endl;
        // printjourney(answer_head);
        listOfObjects<StationConnectionInfo *> * adjacent = adjacency[src_ind].toStations;
        while (adjacent != nullptr){
          int adj_stn_ind = adjacent->object->adjacentStnIndex;
          recursive_find(adjacency,stationInfo,splited_train,adj_stn_ind,maxStopOvers,maxTransitTime,dest_ind,answer_tail,answer_head,src_ind);
          adjacent = adjacent->next;
        }
      }
    }
    trains = trains->next;
  } 



  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
