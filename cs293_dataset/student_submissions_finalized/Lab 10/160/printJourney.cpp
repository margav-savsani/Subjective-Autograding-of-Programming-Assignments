#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
	int sindex=(stnNameToIndex.get(srcStnName))->value;
	int dindex=(stnNameToIndex.get(destStnName))->value; 
	listOfObjects<StationConnectionInfo *>* adjstnlist=adjacency[sindex].toStations;
	//linkedlist of station lists next to station.
	listOfObjects<TrainInfoPerStation*>* direct_trains=nullptr;
	// list that stores the trains that can reach the destination.

	while(adjstnlist!=nullptr){
		StationConnectionInfo* next=adjstnlist->object;
		// next station 	
		listOfObjects<TrainInfoPerStation *>* trains=next->trains;
		// one of the trains from next station.
		while(trains!=nullptr){
			int day;
			TrainInfoPerStation* train=trains->object;
			for(int i=0;i<7;i++){
				if(train->daysOfWeek[i]){
					day=i;
					break;
				}
			}
			if(train->depTime!=-1){
				if(direct_check(train->journeyCode,dindex,train->depTime,day,adjacency,next->adjacentStnIndex)){
					// the train reaches the destination, so add it in the list.
					listOfObjects<TrainInfoPerStation*>* node=new listOfObjects<TrainInfoPerStation*>(train);
					if(direct_trains==nullptr){
						direct_trains =node;
					}
					else{
						listOfObjects<TrainInfoPerStation*>* temp;
						temp=direct_trains;
						while(temp->next!=nullptr){
							temp=temp->next;
						}
						temp->next=node;
					}
				}
			}
			trains = trains->next;
		}
		adjstnlist = adjstnlist->next;
	}
	if(direct_trains!=nullptr){
		printStationInfo(direct_trains);
	}
	else{
		cout<<"No Direct Journeys!"<<endl;
	}
}

#endif
