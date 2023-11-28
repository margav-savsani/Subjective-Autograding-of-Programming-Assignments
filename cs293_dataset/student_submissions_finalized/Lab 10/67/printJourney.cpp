#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct QueueNode{
	int numberOfStopOversUsed;
	int* stopStationsIdx;
	int* trainToBoard;
	int* dayOfBoarding;
	QueueNode(int n,int srcStnIdx){
		numberOfStopOversUsed = 0;
		stopStationsIdx = new int[n];
		trainToBoard = new int[n];
		dayOfBoarding = new int[n];
		for(int i=0;i<n;i++){
			stopStationsIdx[i] = -1;
			trainToBoard[i] = -1;
			dayOfBoarding[i] = -1;
		}
	}
	~QueueNode(){
		delete[] stopStationsIdx;
		delete[] trainToBoard;
		delete[] dayOfBoarding;
	}
};
struct LongJourney{
	int* stopStationsIdx;
	int* trainToBoard;
	int* transitWaitTime;
	LongJourney(int n,int srcStnIdx){
		stopStationsIdx = new int[n];
		trainToBoard = new int[n];
		transitWaitTime = new int[n];
		for(int i=0;i<n;i++){
			stopStationsIdx[i] = -1;
			trainToBoard[i] = -1;
			transitWaitTime[i] = -1;
		}
	}
};
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
	static int recursionLevel = -1;
	recursionLevel++;
	static int srcStnIndex;
	static int destStnIndex;
	static listOfObjects<int>* jCdList;
	static listOfObjects<queueNode>* queueStart = nullptr;
	static listOfObjects<queueNode>* queueEnd = nullptr;
	if(recursionLevel == 0){
		srcStnIndex = stnNameToIndex.get(srcStnName)->value;
        destStnIndex = stnNameToIndex.get(destStnName)->value;
		jCdList = nullptr;
		queueNode curr(srcStnIndex,-1,nullptr);
		queueStart = nullptr;
		queueEnd = nullptr;
		curr.stnIdx = srcStnIndex;
		curr.jrnyCode = -1;
		queueStart = new listOfObjects<queueNode>(curr);
		queueEnd = queueStart;
	}
	// Take queueStart and perform BFS. If jrnyCode = -1, add all in queue, else add only those with the corresponding jrnyCode
	if(queueStart == nullptr){
		recursionLevel--;
		return;
	}
	listOfObjects<queueNode>* nodeToDelete = queueStart;
	queueNode curr = queueStart->object;
	queueStart = queueStart->next;
	delete nodeToDelete;
	if(queueStart == nullptr){
		queueEnd = nullptr;
	}
	if(curr.stnIdx == destStnIndex){
		listOfObjects<int>* jrnyCodeToAdd = new listOfObjects<int>(curr.jrnyCode);
		jrnyCodeToAdd->next = jCdList;
		jCdList = jrnyCodeToAdd;
		printDirectJourneys(srcStnName,destStnName);
		recursionLevel--;
		return;
	}
	listOfObjects<StationConnectionInfo*> *adjList = adjacency[curr.stnIdx].toStations;
	while(adjList){
		StationConnectionInfo* currAdjacentStation = adjList->object;
		listOfObjects<TrainInfoPerStation*>* currTrainList = currAdjacentStation->trains;
		while(currTrainList){
			if(curr.jrnyCode == -1 || currTrainList->object->journeyCode == curr.jrnyCode){
				listOfObjects<queueNode>* nodeToAdd = new listOfObjects<queueNode>(toAdd);
				if(queueStart == nullptr){
					queueStart = nodeToAdd;
					queueEnd = queueStart;
				}else{
					queueEnd->next = nodeToAdd;
					queueEnd = queueEnd->next;
				}
			}
			currTrainList = currTrainList->next;
		}
		adjList = adjList->next;
	}

	printDirectJourneys(srcStnName,destStnName);

	// Printing Final Answer
	if(recursionLevel==0){
		if(jCdList == NULL){
			cout<<"No direct Journeys Available"<<endl;
		}else{
			listOfObjects<TrainInfoPerStation*>* trainsFromSource = stationInfo[srcStnIndex];
			listOfObjects<TrainInfoPerStation*>* ansList = nullptr;
			while(trainsFromSource && jCdList){
				int currJourneyCode = trainsFromSource->object->journeyCode;
				listOfObjects<int>* temp = jCdList;
				listOfObjects<int>* prev = nullptr;
				while(temp){
					if(temp->object == currJourneyCode){
						if(prev == nullptr){
							jCdList = jCdList->next;
						}else{
							prev -> next = temp -> next;
						}
						if(!ansList){
							ansList = new listOfObjects<TrainInfoPerStation*>(trainsFromSource->object);
						}else{
							listOfObjects<TrainInfoPerStation*>* trainInfoToAdd = new listOfObjects<TrainInfoPerStation*>(trainsFromSource->object);
							trainInfoToAdd -> next = ansList;
							ansList = trainInfoToAdd;
						}
						break;
					}
					prev = temp;
					temp = temp -> next;
				}
				trainsFromSource = trainsFromSource->next;
			}
			printStationInfo(ansList);
		}
	}
	recursionLevel--;
	return;
}

#endif
