#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<vector>
using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

	// insert your code here
	vector<int> journeyCodes; //contains the potential journeyCodes that may result in direct journeys
	vector<int> stnIndex; //helps in the working journeyCodes and answer
	vector<int> queue; // the queue
	vector<int> answer;//final answer vector containing all journeyCodes
	auto start_index = stnNameToIndex.get(srcStnName)->value; //the srcStnName index of the dictionary
	auto finish_index = stnNameToIndex.get(destStnName)->value; // the destStnName index of the dicitionaryrue; // to distinguish be
	queue.push_back(stnNameToIndex.get(srcStnName)->value);
	int isFirst = 1; // first step of BST and the subsequent steps since in the modified BST first step is somewhat special
	while(true){
		auto index = queue[0]; // removing the first elelment from the queue
		queue.erase(queue.begin());
		if(index != finish_index){ // if index == finish_index then we need not continue with this iteration of the while loop and simply remove the node from the queue, since either this has already been covered by the answer or it is trivial
			
			auto adj = adjacency[index].toStations; // the adjacent nodes
			while(adj != nullptr){ // iterating through the adjacent nodes
				auto current_id = adj->object->adjacentStnIndex; 
				auto train_object = adj->object->trains;
				while(train_object != nullptr){ // iterating through the trains between two consective stations to see whether they can form a link between a dirsct journey from srcStnName to destStnName
					auto train = train_object->object->journeyCode;
					int i;
					for(i=0;i<journeyCodes.size();i++){
						if(journeyCodes[i] == train && stnIndex[i] == index){
							stnIndex[i] = current_id; // updating stnIndex 
						}
					}
					if(i == journeyCodes.size() && isFirst == 1){ // the first iteration of the BST main loop which results in appending in the journeyCodes
						if(current_id == finish_index){
							answer.push_back(train);
						}else{
							journeyCodes.push_back(train);
							stnIndex.push_back(current_id);
						}
					}
					//do not change
					train_object = train_object->next;
				}
				// don't change
				for(int i=0;i<journeyCodes.size();i++){ // if there is a potential direct train through current_id (at present scenario)
					if(stnIndex[i] == current_id){
						queue.push_back(current_id);
						break;
					}
				}
				adj = adj->next;
			}
		}
			
		for(int i=0;i<journeyCodes.size();i++){ // checking for an answer
			if(stnIndex[i] == finish_index){
				answer.push_back(journeyCodes[i]);
				auto iter1 = journeyCodes.begin()+i;
				auto iter2 = stnIndex.begin() + i;
				journeyCodes.erase(iter1);
				stnIndex.erase(iter2);
			}
		}
				
		for(int i=0;i<journeyCodes.size();i++){ //removing the journeys that are no longer direct journeys
			if(stnIndex[i] == index){
				auto iter = journeyCodes.begin() + i;
				journeyCodes.erase(iter);
				auto iter2 = stnIndex.begin() + i;
				stnIndex.erase(iter2);
			}
		}
		
		//don't change
		isFirst++;
		if(journeyCodes.size() == 0) break;
	}

	//converting the answer journeyCodes into suitable listOfObjects<TrainInfoPerStation*> *
	if(answer.size() != 0){
		listOfObjects<TrainInfoPerStation *> *x = new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(-1, 0, -1, -1));
		auto y = x;
		for(int i=0;i<answer.size();i++){
			auto objects = stationInfo[start_index];
			while(objects != nullptr){
				if(objects->object->journeyCode == answer[i]){
					x->next = new listOfObjects<TrainInfoPerStation *>(objects->object);
					x->next->prev = x;
					x = x->next;
				}
				objects = objects->next;
			}
		}
		
		y = y->next;
		
		printStationInfo(y);
	
	}else{
		cout << "No direct journeys available" <<endl;
	}
	//auto id = stnNameToIndex.get(srcStnName)->value;
	//cout << adjacency[id].toStations->object->trains->object->journeyCode<<endl;

	// Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
	// for the source station and then we can print it out by invoking
	// printStationInfo that we had used in Lab 7.
	// printStationInfo is a private member function of the Planner class
	// It is declared in planner.h and implemented in planner.cpp

	return;
}

#endif
