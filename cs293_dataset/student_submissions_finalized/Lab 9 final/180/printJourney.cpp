#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

int next_in_journey (listOfObjects<TrainInfoPerStation *> * for_jc,StationAdjacencyList* curr_stn){  // if there is a journey A-B-C-D. and we give B as curr_stn this function will return index of C in dictionary
  listOfObjects<StationConnectionInfo *> * adjacented = curr_stn->toStations;
  int jc = for_jc->object->journeyCode;
  while(adjacented != nullptr){                                          //traverse through all the adjacent vertex of given vertex
    
    listOfObjects<TrainInfoPerStation *> * train_list_temped = adjacented->object->trains;
    while(train_list_temped != nullptr){                                  //get list of all trains from selected adjacent station
      if(train_list_temped->object->journeyCode == jc){                   //if journeycode matches..then return the corrosponding stn index
        int result =  adjacented->object->adjacentStnIndex;
        adjacented = nullptr;
        train_list_temped = nullptr;
        return result;
      }
      train_list_temped = train_list_temped->next;
    }
    train_list_temped = nullptr;
    adjacented = adjacented->next; 
  }
  adjacented = nullptr;
  return -100;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{ 
  int src_ind = stnNameToIndex.get(srcStnName)->value;              //get dictionary index of given station 
  listOfObjects<TrainInfoPerStation *> * answer_head = nullptr;                        //this will contain train info from stations at level 1
  listOfObjects<TrainInfoPerStation *> * answer_tail = nullptr;
  listOfObjects<StationConnectionInfo *> * adjacent = adjacency[src_ind].toStations;
  while (adjacent != nullptr){
    
    listOfObjects<TrainInfoPerStation *> * train_list_temp = adjacent->object->trains;
    
    if(stnNameToIndex.getKeyAtIndex( adjacent->object->adjacentStnIndex) == destStnName){        //if station adjacent to the source station is destination station the add it to answer_list directly 
      while(train_list_temp != nullptr){
        if(answer_head == nullptr){
          answer_head= new listOfObjects<TrainInfoPerStation*> (train_list_temp->object);
          answer_tail = answer_head;  
        }
        else{
          answer_tail->next = new listOfObjects<TrainInfoPerStation*> (train_list_temp->object);
          answer_tail = answer_tail->next ;
        }
        train_list_temp = train_list_temp->next;
      }
    }
    while(train_list_temp != nullptr){
      int jc = train_list_temp->object->journeyCode;
      //int ind = next_in_journey(train_list_temp , adjacency[adjacent->object->adjacentStnIndex]);
    
      //listOfObjects<StationConnectionInfo *> * next = adjacency[ind].toStations;
      listOfObjects<StationConnectionInfo *> * next_stn = adjacent;
      int ind = next_stn->object->adjacentStnIndex;
      
      next_stn = adjacency[ind].toStations;
      while(next_stn != nullptr){                                       //else continue from the given station and take next stations using next_stn function
        ind = next_in_journey(train_list_temp,&adjacency[ind]);
        
        if(ind == -100){
          break;
        }
        if(stnNameToIndex.getKeyAtIndex( ind) == destStnName){          //if the next stn is destination station add the journey to our answer
          
          if(answer_head == nullptr){
            answer_head= new listOfObjects<TrainInfoPerStation*> (train_list_temp->object);
            answer_tail = answer_head;  
          }
          else{
            answer_tail->next = new listOfObjects<TrainInfoPerStation*> (train_list_temp->object);
            answer_tail = answer_tail->next ;
          }
          break;
        }
          
      }
      train_list_temp = train_list_temp->next;

    }
  adjacent = adjacent->next;
  }
  if(answer_head == nullptr){                         //no direct journeys available
    cout << "No direct journeys available" << endl;
  }

  //converting the obtained list of jorneys by to_stations of sorce to their info at the source
  //for this just get the list of all journeys containing A by stationInfo array
  //then from this list take those journeys whose journey code is in our answer list
  listOfObjects<TrainInfoPerStation *> * src_list = stationInfo[src_ind];
  listOfObjects<TrainInfoPerStation *> * final_answer_head = nullptr;
  listOfObjects<TrainInfoPerStation *> * final_answer_tail = nullptr;
  listOfObjects<TrainInfoPerStation *> * temp_src_list = src_list;
  while(temp_src_list != nullptr){
    int jc = temp_src_list->object->journeyCode;
    listOfObjects<TrainInfoPerStation *> * temp = answer_head;
    while(temp != nullptr){
      int jc2 = temp->object->journeyCode;
      if(jc == jc2){
        if(final_answer_head == nullptr){
            final_answer_head= new listOfObjects<TrainInfoPerStation*> (temp_src_list->object);
            final_answer_tail = final_answer_head;  
          }
          else{
            final_answer_tail->next = new listOfObjects<TrainInfoPerStation*> (temp_src_list->object);
            final_answer_tail = final_answer_tail->next ;
          }
          break;
      }
      temp = temp->next;
    }
    temp_src_list = temp_src_list->next;
  }
  printStationInfo(final_answer_head);
}
 