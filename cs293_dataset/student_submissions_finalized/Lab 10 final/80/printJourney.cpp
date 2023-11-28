#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif
using namespace std;



void printStationInfo(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  // Expanding information in stnInfoList to get a list of train info
  // in which each element of the list refers to a single day of the
  // week.  This is the list that has to be finally sorted using
  // quicksort.

  currList = stnInfoList;
  expandedList = nullptr;
  int listLength = 0;
  while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
      // Make as many copies of currInfo as the total count of days in the week
      // when this train runs from/to this station
      int jCode = currInfo->journeyCode;
      int stSeq = currInfo->stopSeq;
      int arrTime = currInfo->arrTime;
      int depTime = currInfo->depTime;
    
      for (int i=0; i < 7; i++) {
	if (currInfo->daysOfWeek[i]) {
	  TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
	  // if (newExpandedElement == nullptr) {
	  //   logFile << "Memory allocation failure." << endl;
	  //   cerr << "Memory allocation failure." << endl;
	  //   continue;
	  // }
	  newExpandedElement->setDayOfWeek(i);

	  listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
	  // if (newExpandedListElement == nullptr) {
	  //   logFile << "Memory allocation failure." << endl;
	  //   cerr << "Memory allocation failure." << endl;
	  //   continue;
	  // }

	  if (expandedList == nullptr) {
	    expandedList = newExpandedListElement;
	  }
	  else {
	    newExpandedListElement->next = expandedList;
	    expandedList->prev = newExpandedListElement;
	    expandedList = newExpandedListElement;
	  }
	  listLength++;
	}
      }
    }
    currList = currList->next;
  }

  //Quicksort(expandedList);
  // QuicksortSimple(expandedList, 0, listLength-1);
  
  currList = expandedList;
  while (currList != nullptr) {
    currInfo = currList->object;
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
}






// int week_shift_check(int* w1, bool* w2){
//   int off = 0;
//   bool found = true;
//   while (true){
//     found = true;
//     for(int i =0; i<7; i++){
//       if((w1[i]==0 && w2[w1[i]-1]==0) || ( w1[i]!=0 && w2[w1[i]-1]==1)){
//         continue;
//       }
//       else{
//         //there is an offset
//         for(int j =0; j<7; j++){
//           w1[j]++;
//         }
//         off++;
//         found = false;
//         break;
//       }
//     }
//     if(found==true){
//       break;
//     }
//   }
//   return off;

// }


int next_day(int curr){
  if(curr<6){
    return curr+1;
  }
  else{
    return 0;
  }
}

class printable{
  public:
  listOfObjects<TrainInfoPerStation*>* trains;
  listOfObjects<int>* stations;
  Dictionary<int> St_Name_To_Index;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  int n_stops = -2;

  printable(listOfObjects<TrainInfoPerStation*>* data, listOfObjects<int>* Station_data, Dictionary<int> stNameToIndex){
    St_Name_To_Index = stNameToIndex;
    listOfObjects<TrainInfoPerStation*>* train_marker;
    listOfObjects<int>* station_marker;
    while(data!=nullptr){
      if(data->prev==nullptr){
        listOfObjects<TrainInfoPerStation*>* t = new listOfObjects<TrainInfoPerStation*>(data->object);
        trains = t;
        train_marker = trains;
        train_marker->next=nullptr;
        train_marker->prev=nullptr;

        listOfObjects<int> *s = new listOfObjects<int>(Station_data->object);
        stations = s;
        station_marker = stations;
      }
      else if(data->next==nullptr){
        listOfObjects<TrainInfoPerStation*>* t = new listOfObjects<TrainInfoPerStation*>(data->object);
        train_marker->next = t;
        t->prev = train_marker;
        train_marker = train_marker->next;
        train_marker->object->depTime=-1;
        train_marker->next=nullptr;

        listOfObjects<int> *s = new listOfObjects<int>(Station_data->object);
        station_marker->next = s;
        station_marker = station_marker->next;
      }
      else{
        if(data->next->object->journeyCode!=data->object->journeyCode){
          listOfObjects<TrainInfoPerStation*>* t = new listOfObjects<TrainInfoPerStation*>(data->object);
          train_marker->next = t;
          t->prev=train_marker;
          train_marker = train_marker->next;
          train_marker->next=nullptr;

          listOfObjects<int> *s = new listOfObjects<int>(Station_data->object);
          station_marker->next = s;
          station_marker = station_marker->next;
        }
      }
      data=data->next;
      Station_data = Station_data->next;
    }
  }

  void print(){
    cout << endl;
    listOfObjects<TrainInfoPerStation*>* train_marker = trains;
    listOfObjects<int>* station_marker = stations;

    while(train_marker!=nullptr){
      n_stops+=1;
      int day;
      int day_dept = -1;
      int day_arr_ahead=-1;
      for(int i=0; i<7; i++){
        if(train_marker->object->daysOfWeek[i]==1){
          day = i;
        }
      }
      if(train_marker->next!=nullptr){
        for(int i =0; i<7; i++){
          if(train_marker->next->object->daysOfWeek[i]){
            day_arr_ahead=i;
            break;
          }
        }
        if(train_marker->next->object->arrTime > train_marker->object->depTime){
          day_dept=day_arr_ahead;
        }
        else{
          day_dept = day_arr_ahead-1;
          if(day_dept==-1){
            day_dept=6;
          }
        }
      }
      float transit_time;

      if(train_marker->next!=nullptr){
        float t1 = day*24.0 + (train_marker->object->arrTime)/100 + (float)((train_marker->object->arrTime)%100)/24.0;
        float t2 = day_dept*24.0 + (train_marker->object->depTime)/100 + (float)((train_marker->object->depTime)%100)/60.0;
        transit_time = 100*(int)(t2-t1) + ((t2-t1) - (int)(t2-t1))*60.0;
      }
      if(train_marker->next!=nullptr && train_marker->prev!=nullptr){
        cout << "Day: " << days[day] << endl;
        cout << "At this station: " << St_Name_To_Index.getKeyAtIndex(station_marker->object) << " arr " << train_marker->object->arrTime  << " by journey code: " << train_marker->object->journeyCode <<endl;
        cout << "Transit time: " <<  transit_time << endl;

        cout << "Day: " << days[day_dept] << endl;
        cout << "dept " << train_marker->object->depTime << " by journey code: " << train_marker->next->object->journeyCode << endl;
        cout << endl;
      }
      if(train_marker->prev==nullptr){
        cout << "Day: " << days[day] << endl;
        cout << "At this station: " << St_Name_To_Index.getKeyAtIndex(station_marker->object) << " Start journey" <<endl;
        cout << "dept " << train_marker->object->depTime << " by journey code: " << train_marker->object->journeyCode << endl;
        cout << endl;
      }
      if(train_marker->next==nullptr){
        cout << "Day: " << days[day] << endl;
        cout << "At this station: " << St_Name_To_Index.getKeyAtIndex(station_marker->object) << " End Journey" << endl;
        cout << "arr " << train_marker->object->arrTime << " by journey code: " << train_marker->object->journeyCode << endl;
        cout << endl;
      }

      train_marker = train_marker->next;
      station_marker = station_marker->next;
    }
    
    cout << "number of stops:" << n_stops<<  endl;
    cout << endl;
    cout << endl;
    cout << endl;

  }
};



  


// void add_journey(Journey* journey_yet, TrainInfoPerStation* train_further, listOfObjects<Journey*>* queue_of_journeys_marker, int maxStops, int maxTime, int next_st_index){
//   //Journey* journey_cont = new Journey();
//   if(journey_yet->j_code_curr==train_further->journeyCode){
//     Journey* journey_cont = new Journey();
//     *journey_cont = *journey_yet;
//     journey_cont->curr_stn_index = next_st_index;
//     journey_cont->curr_arr_time = train_further->arrTime;
//     journey_cont->curr_dep_time = train_further->depTime;

//     // for(int i = 0; i<7; i++){
//     //   if(journey_cont->daysOfWeek_curr[i]!=->object->daysOfWeek[i]){
//     //     j->daysOfWeek_curr[i] = trains->object->daysOfWeek[i];
//     //     j->day_offset+=1;
//     //   }    //journey_cont->
//     // }
//   }
// }


int max_stops;
int max_transit;
listOfObjects<TrainInfoPerStation*>* Stack_of_journeys_start=nullptr;
listOfObjects<TrainInfoPerStation*>* Stack_of_journeys_end=nullptr;

listOfObjects<int>* Station_numbers_start;
listOfObjects<int>* Station_numbers_end;


void DFS(TrainInfoPerStation* train_to_station, int st_index, int destination_index, listOfObjects<TrainInfoPerStation*>** StationInfo, StationAdjacencyList* adjacency, int n_stops, Dictionary<int> stnNameToIndex ){
  //passed one train, running on only 1 day
  listOfObjects<TrainInfoPerStation*>* trains_leaving_station = StationInfo[st_index];

  if(st_index==destination_index){
    //cout << "Found it" << endl;

    //printStationInfo(Stack_of_journeys_start);
    printable* p = new printable(Stack_of_journeys_start, Station_numbers_start, stnNameToIndex);
    p->print();

    if(Stack_of_journeys_end->prev!=nullptr){
      //cout << "previous is not null pointer, Found station so I will backtrack" << endl;

      Stack_of_journeys_end = Stack_of_journeys_end->prev;
      Stack_of_journeys_end->next = nullptr;
    }

    if(Station_numbers_end->prev!=nullptr){
      //cout << "previous is not null pointer, Found station so I will backtrack" << endl;

      Station_numbers_end = Station_numbers_end->prev;
      Station_numbers_end->next = nullptr;
    }
    return;
  }

  int day_arr;
  for(int i=0;i<7;i++){
    if(train_to_station->daysOfWeek[i]==1){
      day_arr = i;
      break;
    }
  }

  while(trains_leaving_station!=nullptr){
    TrainInfoPerStation* leaving_train = trains_leaving_station->object;
    if(leaving_train->depTime==-1){
      trains_leaving_station = trains_leaving_station->next;
      continue;
    }
    bool pass = false;
    bool day_leave[7];
    int n_offset = 0;
    for(int i = 0; i<7; i++){
      day_leave[i]=false;
    }
    bool train_change;
    if(leaving_train->journeyCode==train_to_station->journeyCode){
      //cout << "Found same train number train" << endl;
      train_change = false;
      pass = true;
      if(leaving_train->depTime > train_to_station->arrTime){
        day_leave[day_arr] = true;
      }
      else{
        day_leave[next_day(day_arr)] = true;
      }

    }
    else{
      train_change  = true;
      //cout << "Found different train number here" << endl;
      if(n_stops==max_stops){
        trains_leaving_station = trains_leaving_station->next;
        continue;
      }
      bool train_depart_possible_days[7];
      if(leaving_train->depTime > leaving_train->arrTime){
        for(int i=0; i<7; i++){
          train_depart_possible_days[i] = leaving_train->daysOfWeek[i];
        }
      }
      else{
        for(int i=0; i<7; i++){
          train_depart_possible_days[next_day(i)] = leaving_train->daysOfWeek[i];
        }      
      }

      for(int i=0; i<7; i++){
        if(train_depart_possible_days[i]){
          //cout << "day number" << i << endl;
          //cout << "arrival day number" << day_arr<<endl;
          float t1 = day_arr*100 + (float)((float)(train_to_station->arrTime%100)/60.0 + ((int)train_to_station->arrTime/100))*100.0/24.0;
          //cout << "t1 " << t1 << endl;
          float t2 = i*100 + (float)((float)(leaving_train->depTime%100)/60.0 + ((int)leaving_train->depTime/100))*100.0/24.0;
          //cout << "t2 " << t2 << endl;
          float transit = (float)((float)(max_transit%100)/60.0 + ((int)max_transit/100))*100.0/24.0;
          if(t2-t1>0 && t2-t1<(float)transit || t2+700-t1<(float)transit){
            //cout << "got in time" << endl;
            n_offset = 1;
            pass = true;
            day_leave[i] = true;
          }
        }
      }
    }

    if(!pass){
      trains_leaving_station = trains_leaving_station->next;
      continue;
    }
    else{
      //cout << "will pass to new trains" << endl;
      TrainInfoPerStation* leaving_train_arrival;
      int further_station =-1;
      listOfObjects<StationConnectionInfo*>* to_st= adjacency[st_index].toStations;
      bool found = false;
      while(to_st!=nullptr){
        listOfObjects<TrainInfoPerStation*>* my_trains = to_st->object->trains;
        while(my_trains!=nullptr){
          if(my_trains->object->journeyCode==leaving_train->journeyCode){
            leaving_train_arrival = my_trains->object;
            further_station = to_st->object->adjacentStnIndex;
            found = true;
            break;
          }
          my_trains = my_trains->next;
        }
        if(found){
          break;
        }
        to_st = to_st->next;
      }

      listOfObjects<TrainInfoPerStation*>* a_train = StationInfo[further_station];
      while(a_train->object->journeyCode!=leaving_train_arrival->journeyCode){
        a_train = a_train->next;
      }
      leaving_train_arrival = a_train->object;

      for(int i =0; i<7; i++){

        if(day_leave[i]){

          TrainInfoPerStation* next_station_arrival = new TrainInfoPerStation(0,0,0,0);
          *next_station_arrival = *leaving_train_arrival;
          
          // TrainInfoPerStation* taken_train = new TrainInfoPerStation(0,0,0,0);
          // *taken_train = *leaving_train;

          for(int j =0; j<7; j++){
            if(next_station_arrival->arrTime > leaving_train->depTime){
              if(j==i){
                next_station_arrival->daysOfWeek[j]=1;
              }
              else{
                next_station_arrival->daysOfWeek[j]=0;
              }
            }
            else{
              if(j==next_day(i)){
                next_station_arrival->daysOfWeek[j]=1;
              }
              else{
                next_station_arrival->daysOfWeek[j]=0;
              }            
            }
          }

          if(train_change){
            Stack_of_journeys_end->object->depTime = leaving_train->depTime;
          }
          //if(train_change){
          listOfObjects<TrainInfoPerStation*>* adding_to_stack = new listOfObjects<TrainInfoPerStation*>(next_station_arrival);
          adding_to_stack->prev = Stack_of_journeys_end;
          adding_to_stack->next = nullptr;
          Stack_of_journeys_end->next = adding_to_stack;
          Stack_of_journeys_end = Stack_of_journeys_end->next;

          listOfObjects<int>* stat_no_to_add = new listOfObjects<int>(to_st->object->adjacentStnIndex);
          stat_no_to_add->prev = Station_numbers_end;
          stat_no_to_add->next=nullptr;
          Station_numbers_end->next = stat_no_to_add;
          Station_numbers_end = Station_numbers_end->next;

          //}

          DFS(next_station_arrival, further_station, destination_index, StationInfo, adjacency, n_stops+n_offset, stnNameToIndex);
        }
      }
    trains_leaving_station = trains_leaving_station->next;
    }
  }
  Stack_of_journeys_end = Stack_of_journeys_end->prev;
  Stack_of_journeys_end->next = nullptr;
  Station_numbers_end = Station_numbers_end->prev;
  Station_numbers_end->next = nullptr;
}




void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){
  //cout << "im alive" << endl;
  max_stops = maxStopOvers;
  max_transit = maxTransitTime;
  int src_index = stnNameToIndex.get(srcStnName)->value;
  int dest_index = stnNameToIndex.get(destStnName)->value;
  listOfObjects<TrainInfoPerStation*>* start_journeys =  stationInfo[src_index];

  //Journey *init_journey = new Journey(start_journeys->object, start_journeys->object, src_index, src_index);
  // listOfObjects<TrainInfoPerStation*>* queue_of_journeys_start = new listOfObjects<TrainInfoPerStation*>(start_journeys->object);
  // listOfObjects<TrainInfoPerStation*>* queue_of_journeys_end = queue_of_journeys_start;

  //queue_of_journeys_marker = queue_of_journeys;

  while(start_journeys!=nullptr){
    listOfObjects<StationConnectionInfo*>* to_st = adjacency[src_index].toStations;
    while(to_st!=nullptr){
      listOfObjects<TrainInfoPerStation*>* my_trains = to_st->object->trains;
      while(my_trains!=nullptr){
        if(my_trains->object->journeyCode == start_journeys->object->journeyCode){
          for(int i =0; i<7; i++){
            if(start_journeys->object->daysOfWeek[i]==1){

              TrainInfoPerStation* start_train = new TrainInfoPerStation(0,0,0,0);
              *start_train = *start_journeys->object;
              for(int j=0; j<7; j++){
                if(j==i){
                  start_train->daysOfWeek[j]=true;
                }
                else{
                  start_train->daysOfWeek[j]=false;
                }
              }
              int offset;
              // if(my_trains->object->daysOfWeek[i]==0){
              //   offset = 1;
              // }

              TrainInfoPerStation* next_train = new TrainInfoPerStation(0,0,0,0);
              listOfObjects<TrainInfoPerStation*>* a_train = stationInfo[to_st->object->adjacentStnIndex];
              while(a_train->object->journeyCode!=start_train->journeyCode){
                a_train=a_train->next;

              }
              if(a_train->object->arrTime > start_train->depTime){
                offset=0;
              }
              else{
                offset = 1;
              }
              *next_train = *a_train->object;
              
              for(int j=0; j<7; j++){
                if((j==i+offset) || ( (i +offset == 7) && (j==0))){
                  next_train->daysOfWeek[j]=true;
                }
                else{
                  next_train->daysOfWeek[j]=false;
                }
              }
              Stack_of_journeys_start = new listOfObjects<TrainInfoPerStation*>(start_train);
              Stack_of_journeys_start->prev = nullptr;
              Stack_of_journeys_start->next = nullptr;
              Stack_of_journeys_end = Stack_of_journeys_start;

              Station_numbers_start = new listOfObjects<int>(src_index);
              Station_numbers_start->next = nullptr;
              Station_numbers_start->prev = nullptr;
              Station_numbers_end = Station_numbers_start;


              listOfObjects<TrainInfoPerStation*>* to_add = new listOfObjects<TrainInfoPerStation*>(next_train);
              Stack_of_journeys_end->next = to_add;
              Stack_of_journeys_end = Stack_of_journeys_end->next;
              Stack_of_journeys_end->prev = Stack_of_journeys_start;

              listOfObjects<int>* stat_no_to_add = new listOfObjects<int>(to_st->object->adjacentStnIndex);
              Station_numbers_end->next = stat_no_to_add;
              Station_numbers_end = Station_numbers_end->next;
              Station_numbers_end->prev = Station_numbers_start;
              // if(Stack_of_journeys_end!=nullptr){
              //   cout << "not nullptr" << endl;
              // }
              //cout << "Starting search for day " << i << endl;
              DFS(next_train, to_st->object->adjacentStnIndex, dest_index, stationInfo, adjacency, 0, stnNameToIndex);
            }
          }
        }
        my_trains=my_trains->next;
      }
      to_st=to_st->next;
    }
    

    start_journeys = start_journeys->next;
  }

}

#endif
