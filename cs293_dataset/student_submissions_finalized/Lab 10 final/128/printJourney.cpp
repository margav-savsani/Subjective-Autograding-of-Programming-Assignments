#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


#define spl_time -1
#define spl_jrnycode -1
using namespace std;

listOfObjects< listOfObjects<TrainInfoPerStation*>* >* generate_paths
( int srcIndex, int destIndex, int& maxStopOvers, int& maxTransitTime, 
  int num_stops, int curr_time, int curr_jrny, const StationAdjacencyList* adjacency){

  if(srcIndex == destIndex){
    return nullptr;
  }

  else if(num_stops > maxStopOvers){
    cout << "invalid" << endl;
    return nullptr;
  }

  listOfObjects<StationConnectionInfo*>* neighbors = adjacency[srcIndex].toStations;
  listOfObjects<StationConnectionInfo*>* currSt = neighbors;
  

  //stitcher
  listOfObjects< listOfObjects<TrainInfoPerStation*>* >* to_return = nullptr;
  listOfObjects< listOfObjects<TrainInfoPerStation*>* >* last_node = nullptr;

  while(currSt != nullptr ){
    listOfObjects<TrainInfoPerStation*>* currjrny = currSt->object->trains;
    while(currjrny != nullptr){
      
      //check if journey satisfies transit constraint
      int transit = 0;
      bool departure_array[7];
      if(currjrny->object->arrTime < currjrny->object->depTime){
        for(int i=0; i<7; i++){
          departure_array[i] = currjrny->object->daysOfWeek[i];
        }
      }
      else{
        for(int i=0; i<7; i++){
          departure_array[i] = currjrny->object->daysOfWeek[(i-1)%7];
        }
      }

      int day=0;
      if(curr_time == spl_time){
      
        while(!currjrny->object->daysOfWeek[day]){
          day++;
        }

      }
      else{
        day = curr_time/10000;
      }
      
      int new_day = day;
      if(departure_array[day] && currjrny->object->depTime > curr_time%10000){
        transit = (currjrny->object->depTime/100)*60 + currjrny->object->depTime%100
                - (((curr_time%10000)/100)*60 + curr_time%100);
        transit = (transit%60) ? transit/60 + 1 : transit/60;
        new_day = day;
      }
      else{
        for (int i = day+1; i< day + 7; i++){
          new_day = i%7;
          if(departure_array[new_day]){
            transit = i*24 + (currjrny->object->depTime/100)*60 + currjrny->object->depTime%100
                    - (day*24 + ((curr_time%10000)/100)*60 + curr_time%100);
            transit = (transit%60) ? transit/60 + 1 : transit/60;
            break;
          }
        }
      }
      int transit_time = (currjrny->object->journeyCode == curr_jrny) || (curr_jrny == spl_jrnycode) ? 0 :transit;
      if (transit_time <= maxTransitTime){
        //check if journey goes to destIndex
        if(currSt->object->adjacentStnIndex == destIndex){
          listOfObjects<TrainInfoPerStation*>* new_journey = new listOfObjects<TrainInfoPerStation*>(currjrny->object);
          listOfObjects< listOfObjects<TrainInfoPerStation*>* >* paths
           = new listOfObjects< listOfObjects<TrainInfoPerStation*>* >(new_journey);

          if(last_node != nullptr){
            last_node->next = paths;
          }
          if(to_return == nullptr){
            to_return = paths;
          }
          last_node = paths;
          currjrny = currjrny->next;
          continue;
        }

        //check if journey satisfies stopover constraint

        if(currjrny->object->journeyCode == curr_jrny || curr_jrny == spl_jrnycode){
          //calculate reach_time
          int reach_time;
          listOfObjects<StationConnectionInfo*>* from_stations = adjacency[currSt->object->adjacentStnIndex].fromStations;
          listOfObjects<StationConnectionInfo*>* iterate_fromSt = from_stations;
          while(iterate_fromSt != nullptr){
            listOfObjects<TrainInfoPerStation*>* iterate_fromTrains = iterate_fromSt->object->trains; 
            bool found =false;  
            while(iterate_fromTrains != nullptr){
              if(iterate_fromTrains->object->journeyCode == currjrny->object->journeyCode){
                found = true;
                if(currjrny->object->depTime < iterate_fromTrains->object->arrTime){
                  reach_time = new_day*10000 + iterate_fromTrains->object->arrTime;
                }
                else{
                  reach_time = ((new_day + 1)%7)*10000 + iterate_fromTrains->object->arrTime;
                }

                break;
              }
              iterate_fromTrains = iterate_fromTrains->next;
            }
            if(found){break;}
            iterate_fromSt = iterate_fromSt->next;            
          }
          //

          listOfObjects< listOfObjects<TrainInfoPerStation*>* >* paths = generate_paths
          (currSt->object->adjacentStnIndex, destIndex, maxStopOvers, maxTransitTime, num_stops,
          reach_time, currjrny->object->journeyCode, adjacency);
          if(last_node != nullptr){
            last_node->next = paths;
          }
          if(to_return == nullptr){
            to_return = paths;
          }

          listOfObjects< listOfObjects<TrainInfoPerStation*>* >* iterate_paths = paths;
          
          while(iterate_paths != nullptr){
            listOfObjects<TrainInfoPerStation*>* new_node = new listOfObjects<TrainInfoPerStation*>(currjrny->object);
            new_node->next = iterate_paths->object;
            //prev assignment

            iterate_paths->object = new_node;
            if(iterate_paths->next == nullptr){
              last_node = iterate_paths;
            }
            iterate_paths = iterate_paths-> next;
          }
        }

        else if(num_stops < maxStopOvers){
          //calculate reach_time
          int reach_time;
          listOfObjects<StationConnectionInfo*>* from_stations = adjacency[currSt->object->adjacentStnIndex].fromStations;
          listOfObjects<StationConnectionInfo*>* iterate_fromSt = from_stations;
          while(iterate_fromSt != nullptr){
            listOfObjects<TrainInfoPerStation*>* iterate_fromTrains = iterate_fromSt->object->trains; 
            bool found =false;  
            while(iterate_fromTrains != nullptr){
              if(iterate_fromTrains->object->journeyCode == currjrny->object->journeyCode){
                found = true;
                if(currjrny->object->depTime < iterate_fromTrains->object->arrTime){
                  reach_time = new_day*10000 + iterate_fromTrains->object->arrTime;
                }
                else{
                  reach_time = ((new_day + 1)%7)*10000 + iterate_fromTrains->object->arrTime;
                }

                break;
              }
              iterate_fromTrains = iterate_fromTrains->next;
            }
            if(found){break;}
            iterate_fromSt = iterate_fromSt->next;            
          }
          //
          
          listOfObjects< listOfObjects<TrainInfoPerStation*>* >* paths = generate_paths
          (currSt->object->adjacentStnIndex, destIndex, maxStopOvers, maxTransitTime, num_stops+1,
          reach_time, currjrny->object->journeyCode, adjacency);
          if(last_node != nullptr){
            last_node->next = paths;
          }
          if(to_return == nullptr){
            to_return = paths;
          }

          listOfObjects< listOfObjects<TrainInfoPerStation*>* >* iterate_paths = paths;
          
          while(iterate_paths != nullptr){
            listOfObjects<TrainInfoPerStation*>* new_node = new listOfObjects<TrainInfoPerStation*>(currjrny->object);
            new_node->next = iterate_paths->object;
            //prev assignment

            iterate_paths->object = new_node;
            if(iterate_paths->next == nullptr){
              last_node = iterate_paths;
            }
            iterate_paths = iterate_paths-> next;
          }
        }
        
      }

      currjrny = currjrny->next;

    }
    currSt = currSt->next;
  }

  return to_return;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex= stnNameToIndex.get(destStnName)->value;

  listOfObjects<listOfObjects<TrainInfoPerStation*>*>* path_list = generate_paths
      (srcIndex, destIndex, maxStopOvers, maxTransitTime, 0, spl_time, spl_jrnycode, adjacency);

  listOfObjects<listOfObjects<TrainInfoPerStation*>*>* iterate_path_list = path_list;
  if(iterate_path_list == nullptr){
    cout<< "No JOURNEYS SATISFYING CONSTRAINTS\n";
  }
  else{
    while(iterate_path_list != nullptr){
      printStationInfo(iterate_path_list->object);
      iterate_path_list = iterate_path_list -> next;
    }
  }
  




  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  //printStationInfo(to_print);

  return;
}

#endif
