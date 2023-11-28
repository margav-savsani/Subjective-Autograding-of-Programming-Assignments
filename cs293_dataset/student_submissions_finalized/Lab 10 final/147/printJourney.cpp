#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include "planner.h"
#include "codes.h"
#include <queue>
#endif
using namespace std;

namespace ns{Dictionary<int> stnNameToIndex;}
/*
  Idea: iterate over each of the days that the train runs from the srcStn.
  The fact that a journeycode runs on many days is the same as more edges between the same two stations, that's all. Just adds an extra iterate over days loop to our code.
*/
// a route is a direct journey between two not necessarily adjacent stations.

// represents a route
struct Edge{
	int startStation;
	int endStation;
	int journeyCode;
	int depTime;
	int arrivalTime;
};

struct toInvestigate{
	int endIndex; // index of the end node of the edge.
	int currJourneyCode;

	// different days for the same journey code are different here, we consider them separately
	
	listOfObjects<Edge> *listOfStops = nullptr; // the list of direct routes taken so far.
	listOfObjects<Edge> *currentRoute = nullptr; // listOfStops[-1]. The current journey.
	int StopsSoFar = 0;
	int waitingTimeSoFar = 0;

	// deep copy constructor
	toInvestigate(const toInvestigate &t): endIndex(t.endIndex), currJourneyCode(t.currJourneyCode), StopsSoFar(t.StopsSoFar), waitingTimeSoFar(t.waitingTimeSoFar){
		listOfStops = new listOfObjects<Edge>(t.listOfStops->object);
		auto curr1 = t.listOfStops->next;
		auto curr2 = listOfStops;
		if (!curr1) currentRoute = curr2;
		for(;curr1; curr1 = curr1->next){
			curr2 = curr2->next = new listOfObjects<Edge>(curr1->object);
			if (!curr1->next) currentRoute = curr2;
		}
	}
	// constructor required - the init list calls this one. Why? https://stackoverflow.com/questions/67776420/class-initializer-list-does-not-work-with-copy-constructor
	toInvestigate(int endIndex, int currJourneyCode, listOfObjects<Edge> *listOfStops): endIndex(endIndex), currJourneyCode(currJourneyCode){
		this->listOfStops = new listOfObjects<Edge>(listOfStops->object);
		auto curr1 = listOfStops->next;
		auto curr2 = this->listOfStops;
		if (!curr1) 
		for(;curr1; curr1 = curr1->next){
			curr2 = curr2->next = new listOfObjects<Edge>(curr1->object);
			if (!curr1->next) this->currentRoute = curr2;
		}
	}
};

ostream &operator<<(ostream &o, const Edge &e){
	o << ns::stnNameToIndex.getKeyAtIndex(e.startStation) << " to "
	<< ns::stnNameToIndex.getKeyAtIndex(e.endStation) << " with "
	<< "code=" << e.journeyCode;
	return o;
}

void printAJourney(listOfObjects<Edge> *listOfStops, Dictionary<int> &stnNameToIndex, int journeyCt){
	cout << BLUE << journeyCt << "." << RESET << endl;
	for (auto curr=listOfStops; curr; curr = curr->next){
		cout << "- Take train " << curr->object.journeyCode
		<< " from " << GREEN << stnNameToIndex.getKeyAtIndex(curr->object.startStation) << RESET;
		cout << " leaving at " << RED << curr->object.depTime << " hours" << RESET;
		cout << " upto " << GREEN << stnNameToIndex.getKeyAtIndex(curr->object.endStation);
		cout << RESET << "." << endl;
	}
}

int subtractTimes(int day1, int time1, int day2, int time2){
	int ans = (day2 - day1)*10000;
	int tmp = (time2/100 - time1/100);
    if (tmp >= 0) ans += tmp*100;
    else ans = ans - 10000 + (24+tmp)*100;
	tmp = (time2 % 100 - time1 % 100);
	if (tmp >= 0) ans += tmp;
	else ans = ans - 100 + (60+tmp);
	return ans/100 == 99? ans - 7600: ans;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
	int journeyCt = 0;
	bool journeyListFlavorTextPrinted = false;
	ns::stnNameToIndex = this->stnNameToIndex;
	
	// insert your code here
	int srcIndex = stnNameToIndex.get(srcStnName)->value;
	int destIndex = stnNameToIndex.get(destStnName)->value;

	queue<toInvestigate> Q;
	for (auto connection = adjacency[srcIndex].toStations; connection; connection = connection->next){
		int adjVertex = connection->object->adjacentStnIndex;
		for (auto edge = connection->object->trains; edge; edge = edge->next){
			bool *days = edge->object->daysOfWeek;
			for (int j = 0; j < 7; j++){
				if (!days[j]) continue;
				auto startingRoute = new listOfObjects<Edge>({
					srcIndex, adjVertex, edge->object->journeyCode, j*10000 + edge->object->depTime, 0
				});
				for (auto i = stationInfo[adjVertex]; i; i = i->next){
					if (edge->object->journeyCode == i->object->journeyCode){
						startingRoute->object.arrivalTime = j*10000 + i->object->arrTime;
						break;
					}
				}
				Q.push({adjVertex, edge->object->journeyCode, startingRoute});
			}
		}
	}

	while(!Q.empty()){

		toInvestigate u = Q.front();
		Q.pop();
		
		if (u.endIndex == destIndex){
			if (!journeyListFlavorTextPrinted){
				cout << "Available journeys:\n";
				journeyListFlavorTextPrinted = true;
			}
			printAJourney(u.listOfStops, stnNameToIndex, ++journeyCt);
			cout << "Wish you a happy journey!\n\n";
			continue; // no need to check this journey code's path further after destination, can move to the next element of the queue.
		}

		for (auto connection = adjacency[u.endIndex].toStations; connection; connection = connection->next){
			int adjVertex = connection->object->adjacentStnIndex;
			for (auto edge = connection->object->trains; edge; edge = edge->next){

				// check whether we can continue on the same train.
				if (edge->object->journeyCode == u.currJourneyCode){
					auto v = u;
					v.endIndex = adjVertex;
					v.currentRoute->object.endStation = adjVertex;// uff need a deep copy in the constructor else u.currentRoute is also modified.
					Q.push(v); // continue exploring along that path
					continue;
				}

				// now we have to disembark and move to another train. But only if we are allowed to make another stop. Else we reject this edge and move on
				if (u.StopsSoFar == maxStopOvers) 
					continue;
				
				// update u and push. Make a copy to not modify u.
				auto v = u;
				int reachingEndIndexTime = u.currentRoute->object.arrivalTime%10000;
				int arrivalTimeNewTrain = edge->object->arrTime;
				int j = u.currentRoute->object.arrivalTime/10000;
				int nearestDay;
				for (nearestDay = j; nearestDay < 7; nearestDay++){
					if (subtractTimes(j, reachingEndIndexTime, nearestDay, arrivalTimeNewTrain) >= 0) break;
				}
				v.waitingTimeSoFar += subtractTimes(j, reachingEndIndexTime, nearestDay, arrivalTimeNewTrain);
				auto curr = v.listOfStops;
				while(curr->next) curr = curr->next;
				v.currentRoute = curr->next = new listOfObjects<Edge>({
					v.endIndex, adjVertex, edge->object->journeyCode,nearestDay*10000 + edge->object->depTime, 0
				});
				for (auto i = stationInfo[adjVertex]; i; i = i->next){
					if (u.currJourneyCode == i->object->journeyCode){
						v.currentRoute->object.arrivalTime = nearestDay*10000 + i->object->arrTime + ((i->object->arrTime < edge->object->depTime)?10000:0);
						break;
					}
				}
				v.endIndex = adjVertex;
				v.StopsSoFar++;
				v.currJourneyCode = edge->object->journeyCode;
				if (v.waitingTimeSoFar <= maxTransitTime*100) 
					Q.push(v);
			}
		}
	}
	if (journeyCt == 0){
		cout << "Sorry, no journeys found.\n";
	}
	return;
}

#endif
