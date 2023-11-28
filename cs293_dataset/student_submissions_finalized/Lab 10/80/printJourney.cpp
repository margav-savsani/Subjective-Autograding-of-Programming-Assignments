#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
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
  Entry<int> * srcIndex = stnNameToIndex.get(srcStnName);
  Entry<int> * destIndex = stnNameToIndex.get(destStnName);

  if(srcIndex==destIndex){
    cout << "same source and dest" << endl;
    return;
  }
  listOfObjects<StationConnectionInfo *> * to_st_1 = adjacency[srcIndex->value].toStations;
  

  if(to_st_1==nullptr){
    cout << "no journeys" << endl;
    return;
  }
  listOfObjects<int>* queue_of_stations = new listOfObjects<int>(srcIndex->value);
  listOfObjects<int>* queue_of_stations_marker = queue_of_stations;
  listOfObjects<int>* journey_codes = new listOfObjects<int>(-2);
  listOfObjects<int>* journey_code_marker = journey_codes;

  int depth = 0;

  while(queue_of_stations!=nullptr){
    listOfObjects<StationConnectionInfo *> * to_st = adjacency[queue_of_stations->object].toStations;
    bool starting = false;
    while(to_st!=nullptr){
      if(journey_codes->object==-2){
        starting = true;
        if(to_st->object->adjacentStnIndex!=destIndex->value){
          listOfObjects<int> * node_to_insert = new listOfObjects<int>(to_st->object->adjacentStnIndex);
          queue_of_stations_marker->next = node_to_insert;
          queue_of_stations_marker = queue_of_stations_marker->next;
          listOfObjects<TrainInfoPerStation *> *my_trains = to_st->object->trains;
          while(my_trains!=nullptr){
            
            listOfObjects<int> * node_to_insert = new listOfObjects<int>(my_trains->object->journeyCode);
            journey_code_marker->next=node_to_insert;
            journey_code_marker = journey_code_marker->next;
            //cout << "pushing to list for testing: "<< my_trains->object->journeyCode<<endl;
            my_trains = my_trains->next;
          }
          node_to_insert = new listOfObjects<int>(-1);
          journey_code_marker->next=node_to_insert;
          journey_code_marker = journey_code_marker->next;
        }

        else{
          listOfObjects<TrainInfoPerStation *> *my_trains = to_st->object->trains;
          //cout << "printed trains1" << endl;
          //printStationInfo(my_trains);
          listOfObjects< TrainInfoPerStation*>* t_data = stationInfo[srcIndex->value];
          listOfObjects<TrainInfoPerStation*> * t_data2 = to_st->object->trains;
          while(t_data2!=nullptr){
            while(t_data!=nullptr){
              if(t_data->object->journeyCode==t_data2->object->journeyCode){
                listOfObjects<TrainInfoPerStation *> * my_trains2 = new listOfObjects<TrainInfoPerStation *>(t_data2->object);
                t_data2->next=nullptr;
                printStationInfo(my_trains);
              }
              t_data=t_data->next;
            }
            t_data2=t_data2->next;
          }
          // listOfObjects<TrainInfoPerStation *> * my_trains2 = new listOfObjects<TrainInfoPerStation *>(t_data);
          // //my_trains2->next = nullptr;
          // // printStationInfo(my_trains2);
          // while(my_trains2!=nullptr){
          //   //cout << "printed trainsss" << endl;
          //   //stationInfo()
            
          //   break;
          //   my_trains = my_trains->next;
          // }
        }
      }
      else{
        if(journey_codes->object==-1){
          //cout << "found an issue" << endl;
          journey_codes = journey_codes->next;
        }
        starting = false;
        int possible_next_st = to_st->object->adjacentStnIndex;
        //cout << "possible next station: " << stnNameToIndex.getKeyAtIndex(possible_next_st) << endl;
        listOfObjects<TrainInfoPerStation *> *my_trains = to_st->object->trains;
        bool just_added = false;
        while(my_trains!=nullptr){
          //int i = 0;
          //cout << "while" << endl;
          listOfObjects<int>* journey_code_marker2 = journey_codes;
          while(journey_code_marker2->object!=-1){
            //cout << "in here" << endl;
            //cout << "marker: " << journey_code_marker2->object << endl;
            if(my_trains->object->journeyCode==journey_code_marker2->object){
              //cout << "in here1" << endl;
              if(to_st->object->adjacentStnIndex!=destIndex->value){
                if(!just_added){
                  //cout << "adding station" << endl;
                  listOfObjects<int> * node_to_insert = new listOfObjects<int>(possible_next_st);
                  queue_of_stations_marker->next = node_to_insert;
                  queue_of_stations_marker = queue_of_stations_marker->next;
                  //queue_of_stations.push_back(possible_next_st);
                  just_added=true;
                }
                listOfObjects<int> * node_to_insert = new listOfObjects<int>(journey_code_marker2->object);
                journey_code_marker->next=node_to_insert;
                journey_code_marker = journey_code_marker->next;
                //journey_codes.push_back(journey_codes[i]);
                //cout << "journey_codes " << journey_code_marker2->object << endl;
                //cout << "upcoming j_code: " << journey_code_marker2->next->object << endl;
              }
              else{
                //cout << "printed trains2" << endl;
                listOfObjects<TrainInfoPerStation*>* t_data = stationInfo[srcIndex->value];
                //cout << t_data->next->next->object->journeyCode << endl;
                while(t_data!=nullptr){
                  // listOfObjects<TrainInfoPerStation*>* trains_from_src =  to_st_1->object->trains;
                  // while(trains_from_src!=nullptr){
                    //if(trains_from_src->object->journeyCode==my_trains->object->journeyCode){
                  //cout << "data: " << t_data->object->arrTime << " " << t_data->object->depTime << " " << t_data->object->journeyCode << endl;
                  //cout << " " << t_data->next->object->journeyCode << endl;
                  //cout << "dd: " << my_trains->object->journeyCode << endl;
                    if(t_data->object->journeyCode==my_trains->object->journeyCode){
                      listOfObjects<TrainInfoPerStation*>* t_data2 = new listOfObjects<TrainInfoPerStation*>(t_data->object);
                      t_data2->next=nullptr;
                      printStationInfo(t_data2);
                    }
                  
                    //printStationInfo(my_trains2);
                      //}
                    //}
                    //trains_from_src = trains_from_src->next;
                  t_data = t_data->next;
                }

                
              }
              //break;
            }
            journey_code_marker2 = journey_code_marker2->next;
            //cout << "new value of i: " << i << endl;
          }
          my_trains = my_trains->next;
          //cout << "my_train moved forward" << endl;
          if(my_trains==nullptr){
            //cout << "dead" << endl;
          }
        }
        if(just_added){
          listOfObjects<int> * node_to_insert = new listOfObjects<int>(-1);
          journey_code_marker->next=node_to_insert;
          journey_code_marker = journey_code_marker->next;
          //journey_codes.push_back(-1);
        }

        //journey_codes = journey_codes->next;
      }
      to_st = to_st->next;
    }

    if(starting){
      journey_codes = journey_codes->next;
    }
    else{
      while(journey_codes->object!=-1){
        journey_codes = journey_codes->next;
        //journey_codes.erase(journey_codes.begin());
      }
      journey_codes = journey_codes->next;
    }
    //journey_codes.erase(journey_codes.begin());
    queue_of_stations = queue_of_stations->next;
  }





  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
  
  return;
}

#endif
