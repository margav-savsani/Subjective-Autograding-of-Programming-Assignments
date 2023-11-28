#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef PLANNER_H
#include "planner.h"
#endif
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

bool direct_check(int mindex,int dindex,int departure,int day,StationAdjacencyList adjacency[512],int cindex){
	if(cindex == dindex){
		//base case
		return true;
	}
	else {
		listOfObjects<StationConnectionInfo *>* adjstnlist=adjacency[cindex].toStations;
		// list of stations adjacent this station.
		while(adjstnlist!=nullptr){
			StationConnectionInfo* next=adjstnlist->object;
			listOfObjects<TrainInfoPerStation *>* trains=next->trains;
			while(trains!=nullptr){
				TrainInfoPerStation* train=trains->object;
				int x;
				for(int i=0;i<7;i++){
					if(train->daysOfWeek[i]){
						x = i;
						break;
					}
				}
				if(train->journeyCode==mindex&&(((x==day)&&(departure<train->arrTime))||(day<x))){
					return direct_check(mindex,mindex,train->depTime,x,adjacency,next->adjacentStnIndex);
				}
				trains = trains->next;
			}
			adjstnlist = adjstnlist->next;
		}
	}
	return false;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName){
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
