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

  // first let us extract the station infos from the station infos using the station name
  // assuming that the idex given by stnNameToIndex is the index where the station is stored 
  // in the station adjacency list

  //get gives an object of entry class so get its value which is the integer
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

  if(num_journeys==0){
    cout << "No direct journeys available" << endl;
  }
  else{
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

  return;
}

#endif
