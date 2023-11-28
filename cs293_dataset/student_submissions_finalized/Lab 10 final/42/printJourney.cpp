#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef VECTOR_H
#include <vector>
#include <algorithm>
#endif


using namespace std;

struct BFS_Info{
    vector<int> lst_stn_index; // list of stations of departure, including the current one
    vector<int> lst_jcode; // list of jcodes of departures from the previous stations
    vector<int> dep_day_at_prev_station; // 0 to 6, 0 for Sunday, -1 if the user starts from there too
    vector<int> dep_time_at_prev_station; // 0 to 6, 0 for Sunday, -1 if the user starts from there too
    vector<int> arr_day_at_station; // 0 to 6, 0 for Sunday, -1 if the user starts from there too
    vector<int> arr_time_at_station; // arrival time at the given station, may not be of the train with code jcode, -1 if it starts there or if the user starts from there too
    int no_stop_overs; // number of change overs before the departure of this train (may include any change over to board the current train too)

    BFS_Info(){
      no_stop_overs = 0;
    }

    BFS_Info(vector<int> lst_stn_index, vector<int> lst_jcode, vector<int> arr_day_at_station, vector<int> dep_day_at_prev_station, vector<int> arr_time_at_station, vector<int> dep_time_at_prev_station, int no_stop_overs){
      this->lst_stn_index = lst_stn_index;
      this->lst_jcode = lst_jcode;
      this->dep_time_at_prev_station = dep_time_at_prev_station;
      this->dep_day_at_prev_station = dep_day_at_prev_station;
      this->arr_day_at_station = arr_day_at_station;
      this->arr_time_at_station = arr_time_at_station;
      this->no_stop_overs = no_stop_overs;
    }

    void show(){
      cout<<"Station Indices"<<endl;
      for(int i=0;i<lst_stn_index.size();i++){
        cout<<lst_stn_index[i]<<" ";
      }
      cout<<endl;
      cout<<endl;
      cout<<"Journey Codes"<<endl;
      for(int i=0;i<lst_jcode.size();i++){
        cout<<lst_jcode[i]<<" ";
      }
      cout<<endl;
      cout<<endl;
      cout<<"Dep Times"<<endl;
      for(int i=0;i<dep_time_at_prev_station.size();i++){
        cout<<dep_time_at_prev_station[i]<<" ";
      }
      cout<<endl;
      cout<<endl;
      cout<<"Dep Days"<<endl;
      for(int i=0;i<dep_day_at_prev_station.size();i++){
        cout<<dep_day_at_prev_station[i]<<" ";
      }
      cout<<endl;
      cout<<endl;
      cout<<"Arrival Days"<<endl;
      for(int i=0;i<arr_day_at_station.size();i++){
        cout<<arr_day_at_station[i]<<" ";
      }
      cout<<endl;
      cout<<endl;
      cout<<"Arrival Times"<<endl;
      for(int i=0;i<arr_time_at_station.size();i++){
        cout<<arr_time_at_station[i]<<" ";
      }
      cout<<endl;
      cout<<endl;
      cout<<"Stop Overs"<<endl;
      cout<<no_stop_overs<<endl;
      cout<<endl;
      cout<<endl;
      cout<<endl;

    }
};
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  int src_index = stnNameToIndex.get(srcStnName)->value;
  int dest_index = stnNameToIndex.get(destStnName)->value;
  if (srcStnName == destStnName){
    cout<<"The source and destination are the same"<<endl;
    return;
  }
  vector<BFS_Info> bfs_queue;
  vector<BFS_Info> bfs_dest;

  BFS_Info start_elem = BFS_Info();
  start_elem.lst_stn_index.push_back(src_index);

  bfs_queue.push_back(start_elem);
  listOfObjects<StationConnectionInfo*> * a1 = adjacency[src_index].toStations;
  while (a1!=nullptr){
    StationConnectionInfo* b1 = a1->object;
    int to_index = b1->adjacentStnIndex;
    listOfObjects<TrainInfoPerStation *> * c1 = b1->trains;
    while(c1!=nullptr){
      int jcode = c1->object->journeyCode;
      listOfObjects<TrainInfoPerStation *> * a2 = stationInfo[src_index];
      while (a2!=nullptr){
        TrainInfoPerStation* b2 = a2->object;
        if (b2->journeyCode == jcode){
          for (int i=0;i<7;i++){
            if (b2->daysOfWeek[i]){
              listOfObjects<TrainInfoPerStation *> * a3 = stationInfo[to_index];
              while (a3 != nullptr){
                TrainInfoPerStation* b3 = a3->object;
                if (b3->journeyCode == jcode){
                  for (int j = i; j<i+2;j++){
                    if (b3->daysOfWeek[j%7]){
                      BFS_Info inf = BFS_Info();
                      inf.dep_day_at_prev_station.push_back(i);
                      inf.dep_time_at_prev_station.push_back(b2->depTime);
                      inf.lst_jcode.push_back(jcode);
                      inf.lst_stn_index.push_back(src_index);
                      inf.lst_stn_index.push_back(to_index);
                      if ((i == j) && (b3->arrTime > b2->depTime)){
                        inf.arr_day_at_station.push_back(i);
                        inf.arr_time_at_station.push_back(b3->arrTime);
                        bfs_queue.push_back(inf);
                      }
                      else if ((i == (j - 1)%7) && (b3->arrTime <= b2->depTime)){
                        inf.arr_day_at_station.push_back((i+1)%7);
                        inf.arr_time_at_station.push_back(b3->arrTime);
                        bfs_queue.push_back(inf);
                      }
                      
                    }
                  }
                }
                a3 = a3->next;
              }
            }
          }
        }
        a2 = a2->next;
      }
      c1 = c1->next;
    }
    a1 = a1->next;
  }

  bfs_queue.erase(bfs_queue.begin());

  while (bfs_queue.size() != 0){
    BFS_Info elem = bfs_queue[0];
    int stn_index = elem.lst_stn_index[elem.lst_stn_index.size() - 1];
    if (stn_index == dest_index){
      BFS_Info final = bfs_queue[0];
      bfs_queue.erase(bfs_queue.begin());
      bfs_dest.push_back(final);
      continue;
    }

    listOfObjects<StationConnectionInfo*> * a = adjacency[stn_index].toStations;
    while (a!=nullptr){
      StationConnectionInfo* b = a->object;
      int to_index = b->adjacentStnIndex;
      listOfObjects<TrainInfoPerStation *> * c = b->trains;
      while(c!=nullptr){
        TrainInfoPerStation* d = c->object;
        int j_code = d->journeyCode;
        int prev_arr_day = elem.arr_day_at_station[elem.arr_day_at_station.size() - 1];
        int prev_arr_time = elem.arr_time_at_station[elem.arr_time_at_station.size() - 1];
        if (j_code == elem.lst_jcode[elem.lst_jcode.size() - 1]){
            listOfObjects<TrainInfoPerStation *> * a2 = stationInfo[stn_index];
            while (a2!=nullptr){
              TrainInfoPerStation* b2 = a2->object;
              if (b2->journeyCode == j_code){
                for (int i=prev_arr_day;i<=prev_arr_day;i++){
                  if (b2->daysOfWeek[i]){
                    vector<int> st_ind = elem.lst_stn_index;
                    vector<int> st_jcode = elem.lst_jcode;
                    vector<int> dep_day_stn = elem.dep_day_at_prev_station;
                    vector<int> dep_time_stn = elem.dep_time_at_prev_station;
                    st_ind.push_back(to_index);
                    st_jcode.push_back(j_code);
                    if (b2->depTime > b2->arrTime){
                      dep_day_stn.push_back(i);
                      dep_time_stn.push_back(b2->depTime);
                    }
                    else{
                      dep_day_stn.push_back((i+1)%7);
                      dep_time_stn.push_back(b2->depTime);
                    }
                    listOfObjects<TrainInfoPerStation *> * a3 = stationInfo[to_index];
                    while (a3 != nullptr){
                      TrainInfoPerStation* b3 = a3->object;
                      if (b3->journeyCode == j_code){
                        for (int j = dep_day_stn[dep_day_stn.size() - 1]; j<dep_day_stn[dep_day_stn.size() - 1]+2;j++){
                          if (b3->daysOfWeek[j%7]){
                            vector<int> arr_day_stn = elem.arr_day_at_station;
                            vector<int> arr_time_stn = elem.arr_time_at_station;
                            if ((dep_day_stn[dep_day_stn.size() - 1] == j) && (b3->arrTime > b2->depTime)){
                              arr_day_stn.push_back(dep_day_stn[dep_day_stn.size() - 1]);
                              arr_time_stn.push_back(b3->arrTime);
                              BFS_Info inf = BFS_Info(st_ind,st_jcode,arr_day_stn,dep_day_stn,arr_time_stn,dep_time_stn,elem.no_stop_overs);
                              bfs_queue.push_back(inf);
                            }
                            else if ((dep_day_stn[dep_day_stn.size() - 1] == (j - 1)%7) && (b3->arrTime <= b2->depTime)){
                              arr_day_stn.push_back((dep_day_stn[dep_day_stn.size() - 1]+1)%7);
                              arr_time_stn.push_back(b3->arrTime);
                              BFS_Info inf = BFS_Info(st_ind,st_jcode,arr_day_stn,dep_day_stn,arr_time_stn,dep_time_stn,elem.no_stop_overs);
                              bfs_queue.push_back(inf);
                            }
                            
                          }
                        }
                      }
                      a3 = a3->next;
                    }
                  }
                }
              }
              a2 = a2->next;
            }
        }
        else{
          listOfObjects<TrainInfoPerStation *> * a2 = stationInfo[stn_index];
          while (a2 != nullptr){
            TrainInfoPerStation* b2 = a2->object;
            if (b2->journeyCode == j_code){
              for (int day=prev_arr_day;day<7+prev_arr_day;day++){
                int day1 = day;
                if (b2->daysOfWeek[day%7]){
                    if (b2->depTime < b2->arrTime) {
                      day1 = day+1;
                    }
                    else {
                      day1 = day;
                    }
                    if (((day1 - prev_arr_day)*2400 + (b2->depTime - prev_arr_time))/100 <= maxTransitTime && ((day1>prev_arr_day) || (b2->depTime>prev_arr_time))){
                      if (elem.no_stop_overs + 1 <= maxStopOvers){
                        vector<int> st_ind = elem.lst_stn_index;
                        vector<int> st_jcode = elem.lst_jcode;
                        vector<int> dep_day_stn = elem.dep_day_at_prev_station;
                        vector<int> dep_time_stn = elem.dep_time_at_prev_station;
                        st_ind.push_back(to_index);
                        st_jcode.push_back(j_code);
                        dep_time_stn.push_back(b2->depTime);
                        dep_day_stn.push_back(day1%7);
                        listOfObjects<TrainInfoPerStation *> * a3 = stationInfo[to_index];
                        while (a3 != nullptr){
                          TrainInfoPerStation* b3 = a3->object;
                          if (b3->journeyCode == j_code){
                            for (int j = dep_day_stn[dep_day_stn.size() - 1]; j<dep_day_stn[dep_day_stn.size() - 1] + 7;j++){
                              if (b3->daysOfWeek[j%7]){
                                vector<int> arr_day_stn = elem.arr_day_at_station;
                                vector<int> arr_time_stn = elem.arr_time_at_station;
                                if ((dep_day_stn[dep_day_stn.size() - 1] == j) && (b3->arrTime > b2->depTime)){
                                  arr_day_stn.push_back(dep_day_stn[dep_day_stn.size() - 1]);
                                  arr_time_stn.push_back(b3->arrTime);
                                  BFS_Info inf = BFS_Info(st_ind,st_jcode,arr_day_stn,dep_day_stn,arr_time_stn,dep_time_stn,elem.no_stop_overs+1);
                                  bfs_queue.push_back(inf);
                                }
                                else if (((dep_day_stn[dep_day_stn.size() - 1]) == (j - 1)%7) && (b3->arrTime <= b2->depTime)){
                                  arr_day_stn.push_back(((dep_day_stn[dep_day_stn.size() - 1])+1)%7);
                                  arr_time_stn.push_back(b3->arrTime);
                                  BFS_Info inf = BFS_Info(st_ind,st_jcode,arr_day_stn,dep_day_stn,arr_time_stn,dep_time_stn,elem.no_stop_overs+1);
                                  bfs_queue.push_back(inf);
                                }
                                
                              }
                            }
                          }
                          a3 = a3->next;
                        }
                      }
                    }
                }
              }
            }
            a2 = a2->next;
          }
        }
        c = c->next;
      }
      a = a->next;
    }
    bfs_queue.erase(bfs_queue.begin());
  }

  cout<<endl;

  if (bfs_dest.size() == 0){
    cout<<RED<<"NO JOURNEYS FOUND"<<endl;
  }
  for (int i=0;i<bfs_dest.size();i++){
    BFS_Info a = bfs_dest[i];
    //a.show();
    cout<<"JOURNEY "<<i+1<<" : "<<endl;
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    for (int j=0;j<a.lst_jcode.size();j++){
      string stn_start = stnNameToIndex.getKeyAtIndex(a.lst_stn_index[j]);
      string stn_stop = stnNameToIndex.getKeyAtIndex(a.lst_stn_index[j+1]);
      int jcode = a.lst_jcode[j];
      string end_day = days[a.arr_day_at_station[j]];
      string start_day = days[a.dep_day_at_prev_station[j]];
      int end_time = a.arr_time_at_station[j];
      int start_time = a.dep_time_at_prev_station[j];
      cout<<GREEN<<stn_start<<RESET<<" to "<<GREEN<<stn_stop<<endl;
      cout<<BLUE<<"Journey Code: "<<RESET<<jcode<<"\t";
      cout<<RED<<"Departure: "<<RESET<<start_day<<", "<<start_time<<"\t";
      cout<<RED<<"Arrival: "<<RESET<<end_day<<", "<<end_time<<endl;
      cout<<endl;
      if((j != a.lst_jcode.size() - 1) && (a.lst_jcode[j] != a.lst_jcode[j+1])){
          int day1 = a.dep_day_at_prev_station[j+1];
          int depTime = a.dep_time_at_prev_station[j+1];
          int day_prev = a.arr_day_at_station[j];
          int dep_cum_time = 2400*day1 + depTime;
          int arr_cum_time = 2400*day_prev + end_time;
          int transit_time = 0;

          if (dep_cum_time%100 >= arr_cum_time%100){
            transit_time = dep_cum_time - arr_cum_time;
          }
          else{
            int diff_mins = (dep_cum_time%100 + 60 - arr_cum_time%100);
            int diff_hours = dep_cum_time/100 - arr_cum_time/100 - 1;
            transit_time=diff_hours*100 + diff_mins;
          }

          if(day_prev > day1) transit_time += 16800;

          cout<<GREEN<<"Transit Time : "<<RESET<<transit_time<<endl;
      }
    }
    cout<<BLUE<<"No of stopovers : "<<RESET<<a.no_stop_overs<<endl;
    cout<<endl;
  }


  
}

#endif
