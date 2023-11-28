#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#include "planner.h"
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <assert.h>
using namespace std;


int stops = -1;				// = -1 cuz inital jCode to arrive at srcStn is taken to be zero.
int depth=0;
TrainInfoPerStation *dummy = new TrainInfoPerStation(-1, 0, 0, 0);
listOfObjects<TrainInfoPerStation *> *path = new listOfObjects<TrainInfoPerStation *>(dummy);
listOfObjects<TrainInfoPerStation *> *tail = path;

void DFS(StationAdjacencyList *G, int currIdx, int destIdx, int maxStopOvers, int jCode)
{
	listOfObjects<StationConnectionInfo *> *adjList = G[currIdx].toStations;

	if (currIdx == destIdx)
	{
		// printStationInfo(path->next);
		listOfObjects<TrainInfoPerStation*>*x=path->next;
		while (x != nullptr) {
			cout << x->object->journeyCode << " ";
			x=x->next;
		}cout <<"\n";
		return;
	}
	if (G[currIdx].toStations == nullptr) {
		return;
	}

	while (adjList != nullptr)
	{
		listOfObjects<TrainInfoPerStation*> *ctoa = adjList->object->trains;
		while (ctoa != nullptr) {
			if ((jCode != ctoa->object->journeyCode) && (stops+1 <= maxStopOvers)) {
				listOfObjects<TrainInfoPerStation *> *copy = new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(-2, 0, 0, 0));
				copy->object=ctoa->object;
				tail->next=copy;
				tail->next->prev=tail;
				tail=tail->next;
				stops++;
				depth++;
				DFS(G, adjList->object->adjacentStnIndex, destIdx, maxStopOvers, ctoa->object->journeyCode);
				depth--;
				stops--;
				tail = tail->prev;
				tail->next = nullptr;
			}

			else if((jCode == ctoa->object->journeyCode)) {
				listOfObjects<TrainInfoPerStation *> *copy = new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(-2, 0, 0, 0));
				copy->object=ctoa->object;
				tail->next=copy;
				tail->next->prev=tail;
				tail=tail->next;
				depth++;
				DFS(G, adjList->object->adjacentStnIndex, destIdx, maxStopOvers, ctoa->object->journeyCode);
				depth--;
				tail = tail->prev;
				tail->next = nullptr;
			}
			ctoa=ctoa->next;
		}
		
		adjList = adjList->next;
	}
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

	// insert your code here
	int srcIndx = stnNameToIndex.get(srcStnName)->value;
	int destIndx = stnNameToIndex.get(destStnName)->value;

	DFS(adjacency, srcIndx, destIndx, maxStopOvers, 0);
	cout << "This function is to be implemented by you." << endl;

	// Whenever you need to print a journey, construct a
	// listOfObjects<TrainInfoPerStation *> appropriately, and then
	// use printStationInfo that we had used in Lab 7.
	// printStationInfo is a private member function of
	// the Planner class. It is declared in planner.h and implemented in
	// planner.cpp

	return;
}

#endif
