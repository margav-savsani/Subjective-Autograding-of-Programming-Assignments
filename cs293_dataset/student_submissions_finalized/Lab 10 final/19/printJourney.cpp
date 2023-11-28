#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
#include <vector>
#include <queue>

struct Element{
  public:
  int count;
  vector<int> trains;
  vector<int> stations;
  Element(int c, int t, int s){
    count = c; trains.push_back(t); stations.push_back(s);
  }
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){  
  int sour_index = stnNameToIndex.get(srcStnName)->value;
  int dest_index = stnNameToIndex.get(destStnName)->value;

  listOfObjects<TrainInfoPerStation *>* sour_trains = stationInfo[sour_index];
  queue<Element> BFS; // Inititlazation of BFS
  queue<Element> ANS; // To store the ans

  // to initialize the queue from source-station
  while(sour_trains != nullptr){
    BFS.push(Element(0,sour_trains->object->journeyCode,sour_index));
    sour_trains = sour_trains->next;
  }
  // all are inserted in queue for init.

  while(!BFS.empty()){
    Element elem = BFS.front(); // to get the first element of queue
    StationAdjacencyList* current = adjacency;
    listOfObjects<StationConnectionInfo *>* adj = current[elem.stations.back()].toStations;
    // got the all the stations from the initial station.
    while(adj != nullptr){
      int curr_stn_index = adj->object->adjacentStnIndex;
      // selected one of the adjacency station
      listOfObjects<TrainInfoPerStation *>* curr_stn_trains = adj->object->trains;
      // all the trains from prev to curr station.
      if(curr_stn_index == dest_index){
        // if it is the final destination.
        // to check whether the same train is there on curr stn or not.

        while(curr_stn_trains != nullptr){
          if(curr_stn_trains->object->journeyCode == elem.trains.back()){
            // if found then that train reaches the destination 
            // so can append in the final ans
            Element insert = elem;
            insert.stations.push_back(dest_index);
            ANS.push(insert);
            break;
          }
          curr_stn_trains = curr_stn_trains->next;
          // going to next train in curr to check this condition.
        }
      }

      // if the curr station is not the final destination.
      else{
        // to check a train is there from prev station to this station.
        while(curr_stn_trains != nullptr){
          if(curr_stn_trains->object->journeyCode == elem.trains.back()){
            // // if found then there is a path from prev to curr.
            listOfObjects<TrainInfoPerStation *>* curr_stn_trains_to_add = stationInfo[curr_stn_index];
            // Now add the same train and different trains cases in the queue.
            listOfObjects<TrainInfoPerStation *>* to_get_arr_time = stationInfo[curr_stn_index];
            int Arr;
            int Dep;

            while(to_get_arr_time != nullptr){
              if(elem.trains.back() == to_get_arr_time->object->journeyCode){
                Arr = to_get_arr_time->object->arrTime;
                // cout << stnNameToIndex.getKeyAtIndex(curr_stn_index) << " " << elem.trains.back() << " " << Arr << endl;
                break;
              }
              to_get_arr_time = to_get_arr_time->next;
              // got the arrival time of train in the curr station.
            }
            while(curr_stn_trains_to_add != nullptr){
              Dep = curr_stn_trains_to_add->object->depTime;
              if(curr_stn_trains_to_add->object->journeyCode == elem.trains.back()){
                Element insert = elem;
                insert.stations.push_back(curr_stn_index);
                insert.trains.push_back(curr_stn_trains_to_add->object->journeyCode);
                // adding the train and station name to insert and push it
                BFS.push(insert);
              }

              //TODO //here have to include Arr and Dep condition.
              else if(elem.count != maxStopOvers && Dep > Arr && Dep - Arr <= maxTransitTime*100){
                Element insert = elem;
                insert.stations.push_back(curr_stn_index);
                insert.trains.push_back(curr_stn_trains_to_add->object->journeyCode);
                insert.count ++;
                BFS.push(insert);
                // condition check if we want to change the train.
                // adding new train and station info and append it
                // update the count in elem before pushing it.
              }
              curr_stn_trains_to_add = curr_stn_trains_to_add->next;
            }
          }
          curr_stn_trains = curr_stn_trains->next;
        }
      }
      adj = adj->next;
    }
    BFS.pop();
  }
  // cout << ANS.size() << endl;
  if(ANS.empty()){
    cout << RED <<"NO TRAINS ARE PRESENT"<< RESET << endl;
  }
  while(!ANS.empty()){
    Element x = ANS.front();
    int sz = x.trains.size();
    int prev=x.trains[0];
    for(int i = 0; i < sz; i++){
      bool changing = false;
      if (prev != x.trains[i]){
        cout << RED<<"CHANGE THE TRAIN" << RESET<< endl;
        changing = true;
      }
      cout << BLUE << stnNameToIndex.getKeyAtIndex(x.stations[i]) << RESET << endl;
      listOfObjects<TrainInfoPerStation *>* a = stationInfo[x.stations[i]];
      // listOfObjects<TrainInfoPerStation *>* b = stationInfo[x.stations[i]];

      while(a != nullptr){
        if(a->object->journeyCode == x.trains[i]){

          if (changing){
            listOfObjects<TrainInfoPerStation *>* forcheck = stationInfo[x.stations[i]];
            while (forcheck != nullptr)
            {
              if (forcheck->object->journeyCode == prev)
              {
                float time = (a->object->depTime - forcheck->object->arrTime) / 100;
                cout << "Transist time " << BLUE << time << "hrs" << RESET << endl;
                break;
              }
              forcheck = forcheck->next;
            }
          }
          cout << GREEN << "Jcode"<<'\t' << a->object->journeyCode << RESET << '\t';
          if(a->object->arrTime == -1){
            cout << GREEN << "Arr" << '\t'<< "START" << RESET << '\t';
          }
          else{
            cout << GREEN << "Arr" << '\t'<< a->object->arrTime << RESET << '\t';
          }
          if(a->object->depTime == -1){
            cout << GREEN << "Dep" << '\t' << "END" << RESET << '\t' << endl;
          }
          else{
            // transist_dep = a->object->depTime;
            cout << GREEN << "Dep" << '\t' << a->object->depTime << RESET << '\t' << endl;
          }
          break;
        }
        a = a->next;
      }
      prev = x.trains[i];
      
    }
    cout << RED<< "DESTINATION REACHED"<< RESET << endl; 
    cout << BLUE << stnNameToIndex.getKeyAtIndex(x.stations.back()) << RESET << endl;
    // cout << "----------------------------" << endl;

    cout << endl;
    ANS.pop();
  }
  return;
}

#endif