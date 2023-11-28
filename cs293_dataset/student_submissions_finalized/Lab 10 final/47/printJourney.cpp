#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#define YELLOW "\033[93m"

using namespace std;

listOfObjects<TrainInfoPerStation *> * expand_the_list(listOfObjects<TrainInfoPerStation *> *stnInfoList){ // this function is used to expand the the TrainInfoPerStation( for example if the train is running on sun, monday... then it splits it into two trains), it is a subpart of printStationInfo, given in planner.cpp.


  listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  // Expanding information in stnInfoList to get a list of train info
  // in which each element of the list refers to a single day of the
  // week.  This is the list that has to be finally sorted using
  // quicksort.

  currList = stnInfoList;
  expandedList = nullptr;
  int listLength = 0;
  while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
      // Make as many copies of currInfo as the total count of days in the week
      // when this train runs from/to this station
      int jCode = currInfo->journeyCode;
      int stSeq = currInfo->stopSeq;
      int arrTime = currInfo->arrTime;
      int depTime = currInfo->depTime;
    
      for (int i=0; i < 7; i++) {
	if (currInfo->daysOfWeek[i]) {
	  TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
	 
	  newExpandedElement->setDayOfWeek(i);

	  listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
	 

	  if (expandedList == nullptr) {
	    expandedList = newExpandedListElement;
	  }
	  else {
	    newExpandedListElement->next = expandedList;
	    expandedList->prev = newExpandedListElement;
	    expandedList = newExpandedListElement;
	  }
	  listLength++;
	}
      }
    }
    currList = currList->next;
  }


  return expandedList;

}


bool check( TrainInfoPerStation * train, TrainInfoPerStation * tail, int maxTransitTime){ // checks whether it is within maxTransitTime or not.
	
	int train_day;
	int tail_day;
	int head_arrivaltime = train->arrTime;
	int tail_departuretime = tail->depTime;
	if ( head_arrivaltime == -1 ){ // starts
		
		head_arrivaltime = 0;
	}
	if (tail_departuretime== -1){ // ends here.
	
		tail_departuretime = 2400;
	}
	
	for ( int i=0; i< 7; i++){ // days of arrival or departure at the station
		
		if ( train->daysOfWeek[i] == true )    train_day = i;

		if ( tail->daysOfWeek[i] == true )	 tail_day = i;

		
	}
	
	int x = (train_day-tail_day);// I dont know why % is not working here.
	
	if ( x < 0)   x = x+7; // so used this.

	
	if ( train_day == tail_day ){ // same day
	
		
		if ( head_arrivaltime >= tail_departuretime && head_arrivaltime - tail_departuretime <= (maxTransitTime*100) )	return true; // arriavl time > dept time.

		
	}
	else if ( x*24*100 + head_arrivaltime - tail_departuretime <= (maxTransitTime*100) )     return true;// differnt day, but still within time limit.

	return false;// if nothing above is satisfied.
	
}
		
		
		
	

void planJourneys( int initial_station, int final_station, int maxStopOvers, int maxTransitTime, StationAdjacencyList* adjacency, listOfObjects<TrainInfoPerStation *> *head, listOfObjects<TrainInfoPerStation *> *tail, listOfObjects<int> *head_int, listOfObjects<int> *tail_int, Planner* planning, int &n, Dictionary<int> stnNameToIndex){ // does most of the work.
	
	if ( maxStopOvers == -1) return; // maxStopOvers exceeded, which is our base case.

	if ( initial_station == final_station){ // found the path.
	
		n++;// to make the output beautiful, calculated number of possible ways also.
		cout<< n<<"."<<endl;
		// print the TrainInfoPerStation.
		listOfObjects<TrainInfoPerStation *> *printing_the_list = head;
		listOfObjects<int> *head_list_new = head_int;
		listOfObjects<TrainInfoPerStation *> *prev_list = nullptr; 
		int s = 0;
		while ( printing_the_list != nullptr ){// print one of the possibilty.
			

		
			if ( prev_list != nullptr && printing_the_list->object->journeyCode != prev_list->object->journeyCode )  {
			
				s++; cout <<YELLOW<<"Stopover "<<s<<": "<<stnNameToIndex.getKeyAtIndex(head_list_new->object) <<endl; // to keep count of stopovers on the console, defined the color yellow in the file.
			
			}
			else{
				
				cout <<YELLOW<<"Station: "<<stnNameToIndex.getKeyAtIndex(head_list_new->object) <<endl;
			}
			
			planning->printStationInfo(new listOfObjects<TrainInfoPerStation *>(printing_the_list->object));// printing the element, one by one.
			
			prev_list = printing_the_list;// maintain the prev train.
			
			printing_the_list = printing_the_list->next;// update.
			head_list_new = head_list_new->next;
		}
		
		
		return;
		
	}
	

	listOfObjects<StationConnectionInfo *> *toStations = adjacency[initial_station].toStations;// got the stations, to which i can go from this station.
	
	while( toStations != nullptr ){ // loop through all the stations
		
		listOfObjects<TrainInfoPerStation *> *expanded_trains = expand_the_list(toStations->object->trains);// expanded the trains using expand_the_list function.
		
		while( expanded_trains != nullptr){
			
			if ( tail == nullptr){ // if tail is nullptr, then its our first train, so simply add.

				head = tail = new listOfObjects<TrainInfoPerStation *>(expanded_trains->object);
				head_int = tail_int = new listOfObjects<int>(initial_station);
				planJourneys( toStations->object->adjacentStnIndex, final_station, maxStopOvers, maxTransitTime, adjacency, head, tail, head_int, tail_int, planning, n, stnNameToIndex);
				head = tail = nullptr;
				head_int = tail_int = nullptr;
						
			}
			
			else{	
			
				bool allow_train;
				int stopovers;
				if ( tail->object->journeyCode == expanded_trains->object->journeyCode){// as sir said, if same journey code dont think them as a transition and apply same function.
				
					allow_train = true;
					stopovers = maxTransitTime;// dont change stop overs
				}
				else{// if journey codes are different
			
					allow_train = check( expanded_trains->object, tail->object, maxTransitTime);// check whether tail and this train are within maxTransitTime or not.
					stopovers = maxStopOvers-1;// decrease stopovers because we have changed one train
					
				}
				if ( allow_train == true ){// go to next level by updating tail and tail_int.
				
						listOfObjects<TrainInfoPerStation *> *tail_dont_change = tail;
						listOfObjects<TrainInfoPerStation *> *next_object = new listOfObjects<TrainInfoPerStation *>(expanded_trains->object);
						tail->next = next_object;
						next_object->prev = tail;
						tail = next_object;
						listOfObjects<int> *tail_int_dont_change = tail_int;
						listOfObjects<int> *next_object_int = new listOfObjects<int>(initial_station);
						tail_int->next = next_object_int;
						next_object_int->prev = tail_int;
						tail_int = next_object_int;
						planJourneys( toStations->object->adjacentStnIndex, final_station, stopovers, maxTransitTime, adjacency, head, tail, head_int, tail_int, planning, n, stnNameToIndex);// recurssion.
						tail_dont_change->next = nullptr;
						tail = tail_dont_change;
						tail_int_dont_change->next = nullptr;
						tail_int = tail_int_dont_change;
						
				}
				
			}
			
			expanded_trains = expanded_trains->next; // update.
				
		}
		
		toStations = toStations->next;// update.
	}
			
			
			
}	
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  


  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of // ignore this statement as said in piazza.
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  
  // we dont have any restriction on running time 
  
  int initial_station = (stnNameToIndex.get(srcStnName))->value; // starting station index.
  int final_station = (stnNameToIndex.get(destStnName))->value; // ending station index.
  // we will implement dfs.
  int n = 0;
  planJourneys( initial_station, final_station, maxStopOvers, maxTransitTime, adjacency, nullptr, nullptr, nullptr, nullptr, this, n, stnNameToIndex); // helper function.
  // we are using tail and head because to make problem more easier.
  // head and tail stores trains,
  // head_int, tail_int stores index of the stations.
  cout<< n<< " Journeys found"<<endl; 
  return;
}

#endif
