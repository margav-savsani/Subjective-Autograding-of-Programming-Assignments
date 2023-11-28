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
	TrainInfoPerStation* sourceTrainWithThisJourneyCode;
	queueNode(){}
	queueNode(int stnIdx,int jrnyCode,TrainInfoPerStation* sourceTrainWithThisJourneyCode){
		this->stnIdx = stnIdx;
		this->jrnyCode = jrnyCode;
		this->sourceTrainWithThisJourneyCode = sourceTrainWithThisJourneyCode;
	}
};
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
	static int recursionLevel = -1;
	recursionLevel++;
	static int srcStnIndex;
	static int destStnIndex;
	static listOfObjects<TrainInfoPerStation*>* ansList;
	static listOfObjects<int>* jCdList;
	static listOfObjects<queueNode>* queueStart = nullptr;
	static listOfObjects<queueNode>* queueEnd = nullptr;
	if(recursionLevel == 0){
		srcStnIndex = stnNameToIndex.get(srcStnName)->value;
        destStnIndex = stnNameToIndex.get(destStnName)->value;
		ansList = nullptr;
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
		listOfObjects<TrainInfoPerStation*>* toAdd = new listOfObjects<TrainInfoPerStation*>(curr.sourceTrainWithThisJourneyCode);
		listOfObjects<int>* jrnyCodeToAdd = new listOfObjects<int>(curr.jrnyCode);
		jrnyCodeToAdd->next = jCdList;
		jCdList = jrnyCodeToAdd;
		toAdd->next = ansList;
		ansList = toAdd;
		// cout<<curr.jrnyCode<<endl;
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
				if(curr.jrnyCode == -1){
					curr.sourceTrainWithThisJourneyCode = currTrainList->object;
				}
				queueNode toAdd(currAdjacentStation->adjacentStnIndex,currTrainList->object->journeyCode,curr.sourceTrainWithThisJourneyCode);
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

	// Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
	// for the source station and then we can print it out by invoking
	// printStationInfo that we had used in Lab 7.
	// printStationInfo is a private member function of the Planner class
	// It is declared in planner.h and implemented in planner.cpp

	if(recursionLevel==0){
		if(ansList == NULL){
			cout<<"No direct Journeys Available"<<endl;
		}else{
			// while(jCdList){
			// 	cout<<jCdList->object<<endl;
			// 	jCdList=jCdList->next;
			// }
			listOfObjects<TrainInfoPerStation*>* trainsFromSource = stationInfo[srcStnIndex];
			ansList = nullptr;
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
