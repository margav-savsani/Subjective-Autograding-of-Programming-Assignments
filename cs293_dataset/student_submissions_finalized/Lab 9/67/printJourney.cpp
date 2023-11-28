#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct queueNode{
	int stnIdx;
	int jrnyCode;
}
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
	static recursionLevel = -1;
	recursionLevel++;
	static listOfObjects<int> checkBreadth(-1);
	static int srcStnIndex;
	static int destStnIndex;
	static listOfObjects<TrainInfoPerStation*>* ansList;
	if(recursionLevel == 0){
		srcStnIndex = stnNameToIndex.get(srcStnName)->value;
        destStnIndex = stnNameToIndex.get(destStnName)->value;
		ansList = nullptr;
		listOfObjects<queueNode>* queueStart = nullptr;
		listOfObjects<queueNode>* queueEnd = nullptr;
		queueNode curr;
		curr.stnIdx = srcStnIndex;
		curr.jrnyCode = -1;
		queueStart = new listOfObjects<queueNode>(curr);
		queueEnd = queueStart
	}
	// Take queueStart and perform BFS. If jrnyCode = -1, add all in queue, else add only those with the corresponding jrnyCode
	listOfObjects<queueNode>* curr = queueStart;
	if(queueStart == nullptr){
		recursionLevel--;
		delete curr;
		return;
	}
	queueStart = queueStart->next;
	if(queueStart == nullptr){
		queueEnd = nullptr;
	}
	listOfObjects<StationConnectionInfo*> *adjList = adjacency[curr.stnIdx].toStations;
	// cout << "This function is to be implemented by you." << endl;

	// Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
	// for the source station and then we can print it out by invoking
	// printStationInfo that we had used in Lab 7.
	// printStationInfo is a private member function of the Planner class
	// It is declared in planner.h and implemented in planner.cpp
	
	recursionLevel--;
	return;
}
