#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  // taking out the index where srcStn and destStn are stored
  // while finding the route whenever the number of stops exceeds maxStopOvers
  // then break
  
  // *************************************** TODO ***************************************
  // so applying dfs here would make more sense as starting from the source station we try
  // to traverse a path and if we reach a dead end without finding the destination we 
  // backtrack and check all other stations that can be reached through the station just before
  // and continue doing this till we cover all possible paths , but here let's say in a path
  // we come along the destination then we have to check if the number of different journey codes
  // we traversed along is less than the maxStopUser ,so we need to store it in some way
  // Also we need to make sure that we don't continue on a path where waiting time is greater
  // than the time passed as a parameter , so since we are performing a dfs we would have to 
  // bactrack on the path and continue the search from there i.e basically move to next in the
  // list of objects list that would be storing all these adjacent stations
  // Also take care of the days while you are checking the transit time between arrival
  // at a station and departure for the train from that station

  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex = stnNameToIndex.get(destStnName)->value;

  // initialising a variable to store list of journey codes for all journeys
  //num. of journeys found and also the list that stores those journeys
  int num_journeys = 0;
  int *journey_codes = nullptr;
  listOfObjects<TrainInfoPerStation *> *direct = nullptr;

  //getting the station adjacency list of both the src and dest station
  StationAdjacencyList *src_adj = &adjacency[srcIndex];
  StationAdjacencyList *dest_adj = &adjacency[destIndex];

  //stnadjlist is an list that would store a listofObjects behaving like a QUEUE
  //in BFS , which would have the node currently whose adj stations are being checked
  listOfObjects<StationAdjacencyList *> *stnadjlist = new listOfObjects<StationAdjacencyList *>(src_adj);

  //putting all possible trains from source station in a list
  //now we would implement BFS on each of the train routes
  //i.e will find only those trains that have a possibilty b/w them and then would apply BFS
  listOfObjects<TrainInfoPerStation *> *complistoftrainssrc = stationInfo[srcIndex];
  listOfObjects<TrainInfoPerStation *> *tp = nullptr;
  listOfObjects<TrainInfoPerStation *> *listoftrains = nullptr;

  //possible journey which would be considered while applying BFS on it
  while(complistoftrainssrc!=nullptr){
    listOfObjects<TrainInfoPerStation *> *complistoftrainsdest = stationInfo[destIndex];
    while(complistoftrainsdest!=nullptr){
      if(complistoftrainsdest->object->journeyCode==complistoftrainssrc->object->journeyCode){
        if(listoftrains==nullptr){
          listoftrains = new listOfObjects<TrainInfoPerStation *>(complistoftrainssrc->object);
          tp = listoftrains;
        }
        else{
          tp->next = new listOfObjects<TrainInfoPerStation *>(complistoftrainssrc->object);
          tp = tp->next;
        }
        break;
      }
      complistoftrainsdest=complistoftrainsdest->next;
    }
    complistoftrainssrc=complistoftrainssrc->next;
  }

  //looping over all possible trains
  //takes care of the cases if some link between the stations is broken down 
  while(listoftrains != nullptr){

    //journey code of the train currently being checked
		int jrnycode = listoftrains->object->journeyCode;
		stnadjlist->object = &adjacency[srcIndex];

    //for eah train route now we will loop over the adjacent stations of the current
    //node in queue to get the next station where the train goes
		while(stnadjlist != nullptr){

			listOfObjects<StationConnectionInfo*> *adj = stnadjlist->object->toStations;

      //if no adj stations from that station then no continuation possible
			if(adj == nullptr) break;
			
      //now looping over all the stations adjacent to the object in adjstnlist/queue here
      //to check where does the continuation of the route lie
			while(adj != nullptr){
				
				bool dest_found = false;
				listOfObjects<TrainInfoPerStation*> *train = adj->object->trains;

        //looping over the trains from that station
				while (train != nullptr)
				{
          //if journey code matches with that of the train going out from the source station
          //then we would add that journey code to the list
					if(train->object->journeyCode == jrnycode){
						if(stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex) == destStnName){
							if(journey_codes == nullptr){
								journey_codes = new int;
                journey_codes[num_journeys] = jrnycode;
                num_journeys++;
							}
							else{
								journey_codes[num_journeys] = jrnycode;
                num_journeys++;
							}
							dest_found = true;
						}
						stnadjlist->object = &adjacency[adj->object->adjacentStnIndex];
						if(dest_found) break;
					}
					if(dest_found) break;
					train = train->next;
				}
				adj = adj->next;
			}
		}
		listoftrains = listoftrains->next;
	}

  /*
  //loop till the node where the adjacency list is not 0 as where it is 0 we would have to backtrack
  while(src_adj != nullptr){
    // this would have all the statoins that are adjacent to the node whose src_adj is checked above
    listOfObjects<StationConnectionInfo*> *adj = adjstnlist->object->toStations;
    while(adj!=nullptr){
      num_stops++;
      if(num_stops>maxStopOvers) break; // recheck
      if(adj->object->trains->object->depTime - adj->object->trains->object->arrTime >= maxTransitTime){
        break;
      } //recheck
      adj = adj->next;
    }
    // setting the variable as the adjacency list of the adjacent station of src to loop recursively 
    src_adj = &adjacency[adj->object->adjacentStnIndex];
  }

  return;
  */

 if(num_journeys==0){
    cout << "Journey with change overs:" << endl;
  }
  else{
    cout << "Direct journies:" << endl;
    //add all those trains going from source station with journey code added in
    //the journey code array here
    listOfObjects<TrainInfoPerStation *> *listoftrains = stationInfo[srcIndex];
    //to access next pointers while maintaining direct one
    listOfObjects<TrainInfoPerStation *> *temp = nullptr;

    //finding all the journeys from the source with the same journey codes as that
    //of the journey codes found for the direct journeys
    while(listoftrains!=nullptr){
      for(int i=0;i<num_journeys;i++){
        if(journey_codes[i]==listoftrains->object->journeyCode){
          if(direct==nullptr){
            direct = new listOfObjects<TrainInfoPerStation *>(listoftrains->object);
            temp = direct;
          }
          else{
            temp->next = new listOfObjects<TrainInfoPerStation *>(listoftrains->object);
            temp = temp->next;
          }
          break;
        }
      }
      listoftrains = listoftrains->next;
    }
    printStationInfo(direct);
  }

}

#endif
