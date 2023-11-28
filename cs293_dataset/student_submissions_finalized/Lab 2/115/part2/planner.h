#ifndef PLANNER_H
#define PLANNER_H

const int DICT_SIZE=64;
struct Station
{
  char Station_Name[32];
};

struct My_Journey
{
  Station Station_1;
  Station Station_2;
  float Start_time;
};

struct Train
{
  Station Station_1;
  float Start_time;
  Station Station_2;
  float Finish_time;
};

class Planner
{
  Train* All_Trains;
  int Total_Trains;
  Station* All_Stations;
  int Total_Stations;
  bool Filled_or_not[64];
  public:
  Planner()
  {
    Total_Stations=0;
    Total_Trains=0;
    All_Trains = new Train[64];
    All_Stations= new Station[64];
    for(int i=0;i<64;i++)
    {
      Filled_or_not[i]=false;
    }
  }
  bool add(Train x);
  int hashValue(char* x);
  void Query_Station(Station x,float Start);
  Train* Query_Direct_Journey(My_Journey x);
  Train* Query_Journey(My_Journey x);
  bool add_station(Station x);
  bool check(char* k1,char* k2);
};

#endif