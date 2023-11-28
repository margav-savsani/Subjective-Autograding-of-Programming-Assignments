#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#include "queue" 



void Planner::printDirectJourneys(string srcStnName, string destStnName)
{ 

   listOfObjects<TrainInfoPerStation *>*  journeys =  nullptr ; //MATCH Journeys 
   int source_index = stnNameToIndex.get(srcStnName)->value ;  
   int dest_index = stnNameToIndex.get(destStnName)->value ;

   queue<pair<int,int>> Queue ;  // the first int is for station index and second int is for journey code 
   listOfObjects<StationConnectionInfo *>  *tostations = (adjacency[source_index]).toStations ; //to stations 
   while ( tostations != nullptr ) {  // add all joruneys from first station to the queue 
           listOfObjects<TrainInfoPerStation *>* train = tostations->object->trains ;  
           while ( train != nullptr ) { 
                  //add match journey 
                  if ( tostations->object->adjacentStnIndex ==  dest_index ) { //if the to station is destination , then add to journeys
                         if ( journeys == nullptr ) {
                             journeys = new listOfObjects<TrainInfoPerStation *>(train->object) ;
                         }
                         else  {  
                              //add to the journeys 
                              listOfObjects<TrainInfoPerStation *>*  last_journey = journeys ; 
                              while ( last_journey->next != nullptr) last_journey = last_journey->next ;
                              last_journey->next = new listOfObjects<TrainInfoPerStation *>(train->object) ;
                         }
                   } 
                  //add to last of the queue .
                  Queue.push( make_pair(tostations->object->adjacentStnIndex ,train->object->journeyCode) ); 
                  train = train->next ;
           }
           tostations = tostations->next ; 
   }

   while( !Queue.empty() ) { //if queue has some remaining stations to visit 
        pair<int,int> curr = Queue.front(); //get the breadth first station , journey to visit 
        Queue.pop();
        int stn_index  = curr.first ; 
        int jrnyCode =  curr.second  ; 
        listOfObjects<StationConnectionInfo *>  *tostations = (adjacency[stn_index]).toStations ; 

        while ( tostations != nullptr ) {
          listOfObjects<TrainInfoPerStation *>* train = tostations->object->trains ; 
           while ( train != nullptr ) { 
                if ( train->object->journeyCode == jrnyCode ) { 

                   if ( tostations->object->adjacentStnIndex ==  dest_index ) { //if the to station is destination , then add to journeys
                         if ( journeys == nullptr ) {
                             journeys = new listOfObjects<TrainInfoPerStation *>(train->object) ;
                         }
                         else  {  
                              //add to the journeys 
                              listOfObjects<TrainInfoPerStation *>*  last_journey = journeys ; 
                              while ( last_journey->next != nullptr) last_journey = last_journey->next ;
                              last_journey->next = new listOfObjects<TrainInfoPerStation *>(train->object) ;
                         }
                   } 
                  //add to last of the queue .
                   Queue.push( make_pair(tostations->object->adjacentStnIndex ,train->object->journeyCode) ); 
                }
                train = train->next ;
           }
           tostations = tostations->next ; 
        }
   }
   //print the matches
   if ( journeys == nullptr ) cout<<"No direct journeys available"<<endl ; 
   else printStationInfo(journeys) ;
   
  return;
}

#endif


   
