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
  				break;
  			}
			i++;
  		}}}
  		
  		
 

  	
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
