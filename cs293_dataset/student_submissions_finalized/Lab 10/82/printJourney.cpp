#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "planner.h"

using namespace std;

struct StationNode
{
	int stnIndex;
	listOfObjects<TrainInfoPerStation *> *trains;
	int numAdjStn;
	StationNode** adjacentPath;
	StationNode* parent;


	StationNode(int index, listOfObjects<TrainInfoPerStation*>* trn, int numStn, StationNode** adj, StationNode* par){
		stnIndex = index;
		trains = trn;
		numAdjStn = numStn;
		adjacentPath = adj;
		parent = par;
	}
};

class DFSTree{
	public:
	StationNode* root;

	DFSTree(){
		root = nullptr;
	}
};

bool Planner::DFS(StationAdjacencyList* src, int srcIndex, StationAdjacencyList* dest, int destIndex){
	static bool visited[DICT_SIZE] = {0};

	if(stnNameToIndex.getKeyAtIndex(srcIndex) == stnNameToIndex.getKeyAtIndex(destIndex)) return true;

	listOfObjects<StationConnectionInfo*>* currStn = src->toStations;
	int numAdj = 0;
	while(currStn != nullptr){
		if(!visited[currStn->object->adjacentStnIndex]){
			if(DFS(&adjacency[currStn->object->adjacentStnIndex], currStn->object->adjacentStnIndex, dest, destIndex)){

			}
			numAdj++;
		}
		currStn = currStn->next;
	}
	StationNode** = new StationNode[numAdj];
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{


	// insert your code here
	//
	// cout << "This function is to be implemented by you." << endl;


	// Whenever you need to print a journey, construct a
	// listOfObjects<TrainInfoPerStation *> appropriately, and then
	// use printStationInfo that we had used in Lab 7.
	// printStationInfo is a private member function of
	// the Planner class. It is declared in planner.h and implemented in
	// planner.cpp

	return;
}

#endif
