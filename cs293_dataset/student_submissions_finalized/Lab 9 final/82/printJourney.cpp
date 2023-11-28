#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#define CONST_GROWTH 100
#define INIT_SIZE 100

using namespace std;



listOfObjects<TrainInfoPerStation*>* getIntersection(StationAdjacencyList* src, StationAdjacencyList* dest,Dictionary<int> stnNameToIndex){
	listOfObjects<StationConnectionInfo*>* adjSrc = src->toStations;
	listOfObjects<TrainInfoPerStation*>* possibleTrains = nullptr;
	while(adjSrc != nullptr){
		listOfObjects<TrainInfoPerStation*>* adjSrcTrain = adjSrc->object->trains;
		while(adjSrcTrain != nullptr){
			listOfObjects<StationConnectionInfo*>* adjDest = dest->fromStations;
			while(adjDest != nullptr){
				listOfObjects<TrainInfoPerStation*>* adjDestTrain = adjDest->object->trains;
				while(adjDestTrain != nullptr){
					if(adjSrcTrain->object->journeyCode == adjDestTrain->object->journeyCode){

						if(!possibleTrains)
						possibleTrains = new listOfObjects<TrainInfoPerStation*>(adjSrcTrain->object);
						else{
							listOfObjects<TrainInfoPerStation*>* temp = possibleTrains;
							while(temp->next != nullptr){
								temp = temp->next;
							}
							temp->next = new listOfObjects<TrainInfoPerStation*>(adjSrcTrain->object);
							temp->next->prev = temp;
						}
					}
					adjDestTrain = adjDestTrain->next;
				}
				adjDest = adjDest->next;
			}
			adjSrcTrain = adjSrcTrain->next;
		}
		adjSrc = adjSrc->next;
	}
	return possibleTrains;
}


void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
	// insert your code here
	// 0 -> white
	// 1 -> grey
	// 2 -> black

	StationAdjacencyList* source = &adjacency[stnNameToIndex.get(srcStnName)->value];
	StationAdjacencyList* destination = &adjacency[stnNameToIndex.get(destStnName)->value];
	

	// get the possible trains since trains which begins from source and reach destination will only form a possible path.
	listOfObjects<TrainInfoPerStation*>* possibleTrains = getIntersection(source, destination, stnNameToIndex);

	listOfObjects<TrainInfoPerStation*>* checkTrain = possibleTrains;

	listOfObjects<TrainInfoPerStation*>* finalList = nullptr;

	listOfObjects<StationAdjacencyList*>* queue = new listOfObjects<StationAdjacencyList*>(&adjacency[stnNameToIndex.get(srcStnName)->value]);

	while(checkTrain != nullptr){
		int code = checkTrain->object->journeyCode;
		queue->object = &adjacency[stnNameToIndex.get(srcStnName)->value];
		while(queue != nullptr){
			
			if(queue->object->toStations == nullptr) break;
			
			listOfObjects<StationConnectionInfo*> *adj = queue->object->toStations;
			while(adj != nullptr){
				bool c = false;
				listOfObjects<TrainInfoPerStation*>* train = adj->object->trains;
				while (train != nullptr)
				{

					if(train->object->journeyCode == code){
						if(stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex) == destStnName){
							if(finalList == nullptr){
								finalList = new listOfObjects<TrainInfoPerStation*>(checkTrain->object);
							}
							else{
								listOfObjects<TrainInfoPerStation*>* temp = finalList;
								while(temp->next != nullptr){
									temp = temp->next;
									finalList->next->prev = finalList;
								}
								temp->next = new listOfObjects<TrainInfoPerStation*>(checkTrain->object);
								temp->next->prev = temp;
							}
							c = true;
						}
						queue->object = &adjacency[adj->object->adjacentStnIndex];
						if(c) break;
					}
					if(c) break;
					train = train->next;
				}
				adj = adj->next;
			}
			
		}
		checkTrain = checkTrain->next;
	}

	if(!finalList){
		cout << "No direct journeys available" << endl;
	}
	else
	printStationInfo(finalList);


	// cout << "This function is to be implemented by you." << endl;

	// Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
	// for the source station and then we can print it out by invoking
	// printStationInfo that we had used in Lab 7.
	// printStationInfo is a private member function of the Planner class
	// It is declared in planner.h and implemented in planner.cpp

	return;
}

#endif
