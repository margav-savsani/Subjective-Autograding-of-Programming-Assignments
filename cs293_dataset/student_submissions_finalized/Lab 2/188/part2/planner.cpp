
#include "plannerhelp.cpp"
#include <iostream>
using namespace std;

//Planner.cpp is here
struct Journey
{
  // define suitable fields here
  struct Station start_Station;
  struct Station end_Station;
};

struct Query
{
  // define suitable fields here
  float time1;
  char name[32];
  float time2;
};

class Planner
{
  // define suitable fields here
private:
  Dictionary startStations;
  Dictionary endStations;

public:
  Planner(){};
  void AddJourney(char *Station1, float time1, char *Station2, float time2)
  {
    //cout<<"Entered AddJourney Function"<<endl;
    // Initializing all values
    struct Station sStation, eStation;
    strcpy(sStation.name, Station1);
    strcpy(eStation.name, Station2);
    //cout<<"Copy done"<<endl;
    sStation.time = time1;
    eStation.time = time2;
    //cout<<"Struct Initialization done"<<endl;
    sStation.isStart = true;
    eStation.isStart = false;
    startStations.put(sStation);
    endStations.put(eStation);
    startStations.giveStart(sStation.name, startStations.getStart(sStation.name));
    startStations.giveEnd(sStation.name, endStations.getStart(eStation.name));
    
    //cout<<(sStation.start)<<" "<<(sStation.end)<<endl;
    //cout<<(startStations.getStart(sStation.name))<<" "<<startStations.getEnd(sStation.name)<<endl;

    //cout<<(sStation.link)->name<<" "<<(eStation.link)->name<<endl;
    //eStation.link = &sStation;
    //cout<<eStation.link<<" "<<&sStation<<endl;
    //cout<<(eStation.link)->name<<" "<<&sStation<<endl;
    //cout<<"Stations Linked"<<endl;
    // Defining Struct Journey
    struct Journey journey;
    journey.start_Station = sStation;
    journey.end_Station = eStation;
    //
    //cout<<"Added Successfully"<<endl;
  }
  void query_station(char *station, float time)
  {
    // Searching station
    cout<<"Entered query_station"<<endl;
    int head = startStations.hashValue(station);
    int tail = startStations.findFreeIndex(station);
    //cout<<head<<" "<<tail<<endl;
    //cout<<head<<" "<<tail<<endl;
    Station *ptr1 = startStations.getStart(station);
    Station *ptr2 = startStations.getEnd(ptr1->name);

    for (int i = head; i < tail; i++)
    {
      if ((ptr1->time >= time))
      {
        //char str1[32];
        //strcpy(str1, "Munich");
        cout<<" "<<ptr1->time<< " "<<(ptr2->name)<<endl;
      }
      ptr1 = ptr1 + 1;
    }
  }
  Query query_journey(char *station1, float time, char *station2)
  {
    
    int head = startStations.hashValue(station1);
    
    int tail = startStations.findFreeIndex(station1);
    cout<<head<<" "<<tail<<endl;
    Station *arr = startStations.getStart(station1);
    Station* dest = startStations.getEnd(station1);
    //cout<<(dest->name)<<endl;
    int min_time = 9999;
    //int index = 0;
    Query query;
    query.time1 =9999;
    query.time2 =9999;
    strcpy(query.name, "\0");

    for (int i = head; i < tail; i++)
    {
      //cout << "entered quer_journey loop"<<endl;
      //Station *ptr2 = startStations.getStart((ptr->link)->name);
      Station *inter = startStations.getStart(dest->name);
      if (inter == NULL) continue;
      else
      {
        if (strcmp((startStations.getEnd(inter->name))->name, station2) == 0)
        {
          if ((min_time > arr->time) && (arr->time>time)) 
          {
            min_time = arr->time;
            query.time1 = arr->time;
            strcpy(query.name, inter->name);
            query.time2 = inter->time;
          }
        }
      }
      
      if (strcmp((dest)->name, station2) == 0)
      {
        //cout<<"if1"<<endl;
        if ((min_time > (arr->time) && (arr->time)>time))
        {
          min_time = arr->time;
          cout<<min_time<<endl;
          query.time1 = arr->time;
          //strcpy(query.name,"\0");
          //query.time2 = 0;

          
        }
      }
      //cout<<"if2"<<endl;
      
    arr = arr+1; 
    //cout <<"arr:"<<arr<<endl;
    }
    
    return query; 
    
  }
};
