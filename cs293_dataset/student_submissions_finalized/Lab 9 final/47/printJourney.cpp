#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;



void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
 

  
  int initial_station = (stnNameToIndex.get(srcStnName))->value;// get the index of the initial_station.
  int final_station = (stnNameToIndex.get(destStnName))->value;// get the index of the final_station.
  
  listOfObjects<StationConnectionInfo *> * next_station_list = adjacency[initial_station].toStations;// first to stations.
  listOfObjects<TrainInfoPerStation *> *direct_train_first = nullptr ;// list of trains.
  listOfObjects<TrainInfoPerStation *> *direct_train_last = nullptr ;// pointer to the last train, to make addition simpler.
  listOfObjects<int> *index_values_first = nullptr;// pointer to index values first element.
  listOfObjects<int> *index_values_last = nullptr;// pointer to the index values last element, so that addition becomes easy.
  listOfObjects<TrainInfoPerStation *>* all_direct_trains_first = nullptr;// to store direct trains.
  listOfObjects<TrainInfoPerStation *>* all_direct_trains_last = nullptr;// to store direct trains, so that addition becomes easy.
  
  bool start = true;
  // adding elements in the next_station_list into the index_values_first and store corresponding stations in direct_train_first
  while ( next_station_list != nullptr){
  	
  	if ( start == true ){
  		
  		listOfObjects<TrainInfoPerStation *> *trains = (next_station_list->object)->trains;// add these trains to the direct_train_first	
  		direct_train_first = new listOfObjects<TrainInfoPerStation *>( trains->object );// created first element of the train list.
  		direct_train_last = direct_train_first;// made tail is equal to head when only one element is present.
  		index_values_first = new listOfObjects<int>( next_station_list->object->adjacentStnIndex ); // to store index values.
  		index_values_last = index_values_first;// to store index values.
  		trains = trains->next;// updated the train.
  		while ( trains != nullptr ){// add all elements into the linkedlist.
  			
  			 listOfObjects<TrainInfoPerStation *> *new_last = new listOfObjects<TrainInfoPerStation *>( trains->object );// add element to the trains list.
  			 new_last->prev = direct_train_last;
  			 direct_train_last->next = new_last;
  			 direct_train_last = new_last;
  			 trains = trains->next;// update the trains
  			 listOfObjects<int> *new_last_station_index = new listOfObjects<int>( next_station_list->object->adjacentStnIndex );// add element to the stations_index list.
  			 new_last_station_index->prev = index_values_last;
  			 index_values_last->next = new_last_station_index;
  			 index_values_last = new_last_station_index;
  			 	 
  		}
  		

  		start = false;
  	}
  	
  	else{
  		
  		listOfObjects<TrainInfoPerStation *> *trains = (next_station_list->object)->trains; // add these trains to the direct_train_last
  		while ( trains != nullptr ){// add all elements into the linkedlist.
  			
  			 listOfObjects<TrainInfoPerStation *> *new_last = new listOfObjects<TrainInfoPerStation *>( trains->object );// add element to the trains list.
  			 new_last->prev = direct_train_last;
  			 direct_train_last->next = new_last;
  			 direct_train_last = new_last;
  			 trains = trains->next;// update the trains.
  			 listOfObjects<int> *new_last_station_index = new listOfObjects<int>( next_station_list->object->adjacentStnIndex );// add element to the index list.		 
  			 new_last_station_index->prev = index_values_last;
  			 index_values_last->next = new_last_station_index;
  			 index_values_last = new_last_station_index;
  			  
  		}
  		
  	}
  		
  	next_station_list = next_station_list->next;	// update the station.
  		
  }
  
  while ( index_values_first != nullptr ){// if index_values_first is not empty, that means there are elements to still check.
  	
  	if ( index_values_first->object == final_station){// if this value is final_station index then we found a path.
  		
  		if (all_direct_trains_first == nullptr ){// add it to the all_direct_trains_first, because we want to print later.
  			
  			all_direct_trains_first = new listOfObjects<TrainInfoPerStation *>(direct_train_first->object);
  			all_direct_trains_last = all_direct_trains_first;
  		}
  		else{
  			
  			listOfObjects<TrainInfoPerStation *> *new_last_station_add = new listOfObjects< TrainInfoPerStation *>(direct_train_first->object  );
  			new_last_station_add->prev = all_direct_trains_last;
  			all_direct_trains_last->next = new_last_station_add;
  			all_direct_trains_last = new_last_station_add;
  			
  		}
  	}
  	
  	else{
  	
  		
  		listOfObjects<StationConnectionInfo *> * next_station_lists = adjacency[index_values_first->object].toStations;// list of stations from this station.
		while( next_station_lists != nullptr ){
  	
  			StationConnectionInfo* next_station = next_station_lists->object;// next station 	
  			listOfObjects<TrainInfoPerStation *> *trains = next_station->trains;// one of the trains from next station.
  			while( trains != nullptr ){
  				
  				int journeyCode_match = direct_train_first->object->journeyCode;
  				int day;
  				for ( int i=0; i<7; i++){
  		
  					if ( direct_train_first->object->daysOfWeek[i] == true ){
  				
  						day = i;
  						break;
  					}
  				}
  				
  				
  				TrainInfoPerStation* train = trains->object;
  				int day_this;
  				for ( int i=0; i<7; i++){
  		
  					if ( train->daysOfWeek[i] == true ){
  				
  						day_this = i;
  						break;
  					}
  				}
  				
  				if ( train->journeyCode == journeyCode_match && (( day_this == day && train->arrTime > direct_train_first->object->depTime ) || ( day_this > day ))){// if it matches the previous constraint( to match journeyCode), then add it at the last to the index_list.
  					
 
  			 		listOfObjects<TrainInfoPerStation *> *new_last = new listOfObjects<TrainInfoPerStation *>( train );//update the new_last.
  			 		new_last->prev = direct_train_last;
  			 		direct_train_last->next = new_last;
  			 		direct_train_last = new_last;
  			 		listOfObjects<int> *new_last_station_index = new listOfObjects<int>( next_station_lists->object->adjacentStnIndex );// update the index_values_last.
  			 		new_last_station_index->prev = index_values_last;
  			 		index_values_last->next = new_last_station_index;
  			 		index_values_last = new_last_station_index;
  			 		break;

  				}
  				trains = trains->next;// update the trains
  			}
  			
  			next_station_lists = next_station_lists->next;// go to next station in the list.
  			
  		} 		
  		
  	}
  	
  	index_values_first = index_values_first->next;// go to next index value.
  	direct_train_first = direct_train_first->next;// go to next index value.	
  	
  	
  }			 
  			
  	
  if ( all_direct_trains_first != nullptr ){// print if it is not nullptr
  		printStationInfo(all_direct_trains_first);
  }
  else{
  
  	cout<<"No direct journeys available"<<endl;
  
  }
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
