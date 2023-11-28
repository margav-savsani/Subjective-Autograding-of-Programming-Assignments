#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;



bool find( int index, int JourneyCode, int final, int dept_time, int day, StationAdjacencyList adjacency[512]){
	if( index == final ){//  base case
	return true;}
	else {
		int initial = index;
		listOfObjects<StationConnectionInfo *> * next_list = adjacency[initial].toStations;// list of stations from this station.
		while( next_list != NULL ){
  			StationConnectionInfo* next = next_list->object;// next station 	
  			listOfObjects<TrainInfoPerStation *> *trains = next->trains;// one of the trains from next station.
  			while( trains != NULL ){
  				TrainInfoPerStation* train = trains->object;
  				int this_day;
  				int i=0; 
		        while(i<7){
  					if ( train->daysOfWeek[i] == true ){
  					this_day = i;
  					break;}
				i++;}
  				if ( train->journeyCode == JourneyCode && (( this_day == day && train->arrTime > dept_time ) || ( this_day > day ) ) ){
  					return find( next->adjacentStnIndex, JourneyCode, JourneyCode, train->depTime, this_day, adjacency);
  				}
  				trains = trains->next;}
  			next_list = next_list->next;
  		}
  	}
  	return false;}
	
void Planner::printDirectJourneys(string srcStnName, string destStnName){
  int initial = (stnNameToIndex.get(srcStnName))->value; // starting station index.
  int final = (stnNameToIndex.get(destStnName))->value; // ending station index.
  listOfObjects<StationConnectionInfo *> * next_list = adjacency[initial].toStations;// storing linkedlist of station lists next to station.
  listOfObjects<TrainInfoPerStation *> *reaches = NULL;// list that stores the trains that can reach the destination.
  while( next_list != NULL ){
  	
  	StationConnectionInfo* next = next_list->object;// next station 	
  	listOfObjects<TrainInfoPerStation *> * trains = next->trains;// one of the trains from next station.
  	while( trains != NULL ){
  		
  		int day;
  		TrainInfoPerStation* train = trains->object;
  		int i=0; 
		while(i<7){
  			if ( train->daysOfWeek[i] == true ){
  				day = i;
  				break;}
			i++;
  		}
  		if ( train->depTime != -1 ){
  			bool found = find( next->adjacentStnIndex, train->journeyCode, final, train->depTime, day, adjacency);
  			if ( found == true ){// the train reaches the destination, so add it in the list.
  				if ( reaches == NULL ){
  					reaches = new listOfObjects<TrainInfoPerStation *>(train);}
  				else{
  					listOfObjects<TrainInfoPerStation *> *train_new = new listOfObjects<TrainInfoPerStation *>(train);
  					reaches->prev = train_new;
  					train_new->next = reaches;
  					reaches = train_new;
  				}
  			}									
  		}
  		trains = trains->next;
  	}
  	next_list = next_list->next;
  }
  
  if ( reaches != NULL ){printStationInfo(reaches);}
else{cout<<"No direct journeys available"<<endl;}

  	
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
