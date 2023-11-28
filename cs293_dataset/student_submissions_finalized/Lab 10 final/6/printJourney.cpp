#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

//struct to carry forward stops info
struct journey_info
{
  public:
  int no_of_stops;
  int *waiting_time;
  int *journey_code;
  int *next_stn;
  int *next_depart;
  int *departure_day;
  journey_info(int n, int wait_time, int JCode, int next_station, int next_departure_time, int day_next)
  {
    no_of_stops = 0;
    waiting_time = new int[n+1];
    journey_code = new int[n+1];
    next_stn = new int[n+1];
    next_depart = new int[n+1];
    departure_day = new int[n+1];
    waiting_time[0] = wait_time;
    journey_code[0] = JCode;
    next_stn[0] = next_station;
    next_depart[0] = next_departure_time;
    departure_day[0] = day_next;
    for(int i=1;i<n+1;i++)
    {
      waiting_time[i] = -1;
      journey_code[i] = -1;
      next_stn[i] = -1;
      next_depart[i] = -1;
      departure_day[i] = -1;
    }
  }

  journey_info(const journey_info &j)
  {
    no_of_stops = j.no_of_stops;
    int n = no_of_stops;
    waiting_time = new int[n+1];
    journey_code = new int[n+1];
    next_stn = new int[n+1];
    next_depart = new int[n+1];
    departure_day = new int[n+1];
    for(int i=0;i<n+1;i++)
    {
      waiting_time[i] = j.waiting_time[i];
      journey_code[i] = j.journey_code[i];
      next_stn[i] = j.next_stn[i];
      next_depart[i] = j.next_depart[i];
      departure_day[i] = j.departure_day[i];
    }
  }

  
	~journey_info()
  {
		delete[] waiting_time;
		delete[] journey_code;
		delete[] next_stn;
		delete[] next_depart;
		delete[] departure_day;
  }

};
// to find station name from station_index
string station_name(int station_index)
{
  string ret;
  if(station_index == 175)
    ret = "PUNE CANTONMENT";
  else if(station_index == 196)
    ret = "MUMBAI CENTRAL";
  else if(station_index == 218)
    ret = "THANE JUNCTION";
  else if(station_index == 227)
    ret = "LOKMANYA TILAK TERMINUS MUMBAI";
  else if(station_index == 239)
    ret = "ROURKELA JUNCTION";
  else if(station_index == 298)
    ret = "KALYAN JUNCTION";
  else if(station_index == 304)
    ret = "AHMEDABAD CENTRAL";
  else if(station_index == 307)
    ret = "BHILAI JUNCTION";
  else if(station_index == 339)
    ret = "HOWRAH JUNCTION";
  else if(station_index == 349)
    ret = "CHHATRAPATI SHIVAJI MAHARAJ TERMINUS MUMBAI";
  else if(station_index == 438)
    ret = "NAGPUR CENTRAL";
  else
    ret = "";
  return ret;
}
// gives properties of earlier station
int* backtrace_properties(int curr_stn, int next_stn, int dest_stn, int dep_next_train, int JCode, int day, StationAdjacencyList* adjacency)
{
  listOfObjects<StationConnectionInfo *> *find_curr_stat = adjacency[next_stn].fromStations;
  while(find_curr_stat->object->adjacentStnIndex != curr_stn)
  {
    find_curr_stat = find_curr_stat->next;
    continue;
  }
  listOfObjects<TrainInfoPerStation *> *train_found = find_curr_stat->object->trains;
  while(train_found->object->journeyCode != JCode)
  {
    train_found = train_found->next;
    continue;
  }
  int next_arrival_time = train_found->object->arrTime;
  int next_dep_time = train_found->object->depTime;
  int next_day;
  if(next_arrival_time < dep_next_train)
  {
    next_day = day + 1;
  }
  else
  {
    next_day = day;
  }
  int* ret = new int;
  ret[0] = next_day;
  ret[1] = next_dep_time;
  ret[2] = next_arrival_time;
  return ret;
}

// recursively applied function for our question
void search_for_station(int curr_stn, int dest_stn, int maxStopOvers, int maxTransitTime, int code_train, int day, int arrival_time, StationAdjacencyList* adjacency, journey_info* j)
{
  if(curr_stn == dest_stn)
  {

    cout<<BLUE<<"========Option "<<"========="<<endl;
    cout<<BLUE<<"No of Stops: "<<j->no_of_stops<<endl;
    for(int i = 0; i <= j->no_of_stops; i++)
    {
      cout<<endl;
      int time = j->waiting_time[i];
      //cout<<GREEN<<"Waiting Time: "<<RED<<time/60<<" hours "<<time%60<<" minutes "<<endl;
      cout<<GREEN<<"Journey Code: "<<RED<<j->journey_code[i]<<"     "<<GREEN<<"Current Station: "<<RED<<station_name(j->next_stn[i])<<endl;
      cout<<GREEN<<"Departing Time From Next: "<<RED<<j->next_depart[i]<<"     "<<GREEN<<"Day: "<<RED<<j->departure_day[i]<<endl;
      cout<<RESET<<endl;
    }
    return;
  }
  listOfObjects<StationConnectionInfo *> *next_station_list = adjacency[curr_stn].toStations;
  while(next_station_list != nullptr)
  {
    int next_stn = next_station_list->object->adjacentStnIndex;
    listOfObjects<TrainInfoPerStation *> *trains_avail = next_station_list->object->trains;
    while(trains_avail != nullptr)
    {
      bool *running_days = trains_avail->object->daysOfWeek;
      int dep_next_train = trains_avail->object->depTime;
      int JCode = trains_avail->object->journeyCode;
      if(code_train == -1 && day == -1 && arrival_time == -1)
      {
        for(int i = 0; i < 7; i++)
        {
          if(running_days[i])
          {
            int* back_prop = backtrace_properties(curr_stn, next_stn, dest_stn, dep_next_train, JCode, i, adjacency);
            int next_day = back_prop[0];
            int next_arrival_time = back_prop[1];
            int next_dept_time = back_prop[2];
            if(next_stn == dest_stn)
            {

              cout<<BLUE<<"========Option "<<"========="<<endl;
              cout<<BLUE<<"No of Stops: 0"<<endl;
              cout<<GREEN<<"Journey Code: "<<RED<<JCode<<"     "<<GREEN<<"Current Station: "<<RED<<station_name(curr_stn)<<endl;
              cout<<GREEN<<"Departing Time From Next: "<<RED<<dep_next_train<<"     "<<GREEN<<"Day: "<<RED<<i<<endl;
              cout<<RESET<<endl;
            }
            else
            {

              journey_info* j_ = new journey_info(maxStopOvers, 0, JCode, curr_stn, next_dept_time, next_day);
              search_for_station(next_stn, dest_stn, maxStopOvers, maxTransitTime, JCode, next_day, next_arrival_time, adjacency, j_);
            }
          }
        }
      }
      else if(next_stn == dest_stn && JCode == code_train)
      {
        cout<<BLUE<<"========Option "<<"========="<<endl;
        cout<<BLUE<<"No of Stops: "<<j->no_of_stops<<endl;
        for(int i = 0; i <= j->no_of_stops; i++)
        {
          cout<<endl;int time = j->waiting_time[i];
          //cout<<GREEN<<"Waiting Time: "<<RED<<time/60<<" hours "<<time%60<<" minutes "<<endl;
          cout<<GREEN<<"Journey Code: "<<RED<<j->journey_code[i]<<"     "<<GREEN<<"Current Station: "<<RED<<station_name(j->next_stn[i])<<endl;
          cout<<GREEN<<"Departure Time From Next: "<<RED<<j->next_depart[i]<<"     "<<GREEN<<"Day: "<<RED<<j->departure_day[i]<<endl;
          cout<<RESET<<endl;
        }
      }
      
      else if(JCode == code_train)
      {
        if(trains_avail->object->depTime == -1)
        {

        }
        else
        {
          int* back_prop = backtrace_properties(curr_stn, next_stn, dest_stn, dep_next_train, JCode, day, adjacency);
          int next_day = back_prop[0];
          int next_arrival_time = back_prop[1];
          int next_dept_time = back_prop[2];

          search_for_station(next_stn, dest_stn, maxStopOvers, maxTransitTime, code_train, next_day, next_arrival_time, adjacency, j);
        }
      }
      else if(maxStopOvers > 0)
      {
        if((dep_next_train - arrival_time ) >= 0 && (dep_next_train/100*60 + dep_next_train%60 - (arrival_time/100*60 + arrival_time%60)) <= maxTransitTime*100)
        {
          if(running_days[day])
          {
            int* back_prop = backtrace_properties(curr_stn, next_stn, dest_stn, dep_next_train, JCode, day, adjacency);
            int next_day = back_prop[0];
            int next_arrival_time = back_prop[1];
            int next_dept_time = back_prop[2];

            journey_info j1 = *j;
            journey_info* j_copy = &j1;

            (j_copy->no_of_stops)++;
            j_copy->waiting_time[j_copy->no_of_stops] = dep_next_train - arrival_time  + 2400;
            j_copy->journey_code[j_copy->no_of_stops] = JCode;
            j_copy->next_stn[j_copy->no_of_stops] = curr_stn;
            j_copy->next_depart[j_copy->no_of_stops] = next_dept_time;
            j_copy->departure_day[j_copy->no_of_stops] = next_day;

            search_for_station(next_stn, dest_stn, maxStopOvers - 1, maxTransitTime, JCode, next_day, next_arrival_time, adjacency, j_copy);
          }
        }
        else if((dep_next_train - arrival_time ) < 0 && (dep_next_train/100*60 + dep_next_train%60 - (arrival_time/100*60 + arrival_time%60)   + 24*60) <= maxTransitTime*100)
        { 
          if(running_days[(day + 1)%7])
          {
            int* back_prop = backtrace_properties(curr_stn, next_stn, dest_stn, dep_next_train, JCode, (day + 1)%7, adjacency);
            int next_day = back_prop[0];
            int next_arrival_time = back_prop[1];
            int next_dept_time = back_prop[2];
            journey_info j1 = *j;
            journey_info* j_copy = &j1;

            (j_copy->no_of_stops)++;
            j_copy->waiting_time[j_copy->no_of_stops] = dep_next_train - arrival_time  + 2400;
            j_copy->journey_code[j_copy->no_of_stops] = JCode;
            j_copy->next_stn[j_copy->no_of_stops] = curr_stn;
            j_copy->next_depart[j_copy->no_of_stops] = next_dept_time;
            j_copy->departure_day[j_copy->no_of_stops] = next_day;


            search_for_station(next_stn, dest_stn, maxStopOvers - 1, maxTransitTime, JCode, next_day, next_arrival_time, adjacency, j_copy);
          }
        }
        else
        {

        }
      }
      else 
      {

      } 
      trains_avail = trains_avail->next;
    }
    next_station_list = next_station_list->next;
  }
}


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  int start_stn = stnNameToIndex.get(srcStnName)->value;
  int dest_stn = stnNameToIndex.get(destStnName)->value;
  cout<<GREEN<<"Journey starts from: "<<station_name(start_stn)<<" and ends on: "<<station_name(dest_stn)<<endl;
  cout<<RESET;
  int code_train = -1;
  int day = -1;
  int arrival_time = -1;
  journey_info *j_ = new journey_info(0,0,0,0,0,0);
  search_for_station(start_stn, dest_stn, maxStopOvers, maxTransitTime, code_train, day, arrival_time, adjacency, j_);
}

#endif

