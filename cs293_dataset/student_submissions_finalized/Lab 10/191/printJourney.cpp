#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<vector>
using namespace std;

void getPlanJourneys(srcStnName, destStn, maxStopOvers, maxTransitTime){
	
}


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
	
	vector<vector<int>> answer;	
	
	auto newVertice = DFS(Graph);
	for(int i = 0;i<=maxStopOvers;i++){
		if(getPLanJourneys(srcStnName, newVertice, i, maxTransitTime) && getPlanJourneys(newVertice, destStnName, maxStopOvers - i,maxTransitTime)){
			answer.push_back(combine(getPLanJourneys(srcStnName, newVertice, i, maxTransitTime), getPlanJourneys(newVertice, destStnName, maxStopOvers - i,maxTransitTime)));
		}
	}
}
  

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
	vector<int> journeyCodes; 
	vector<int> stnIndex; 
	vector<int> queue;
	vector<int> answer;
	auto start_index = stnNameToIndex.get(srcStnName)->value; 
	auto finish_index = stnNameToIndex.get(destStnName)->value; 
	queue.push_back(stnNameToIndex.get(srcStnName)->value);
	int isFirst = 1;
	while(true){
		auto index = queue[0]; 
		queue.erase(queue.begin());
		if(index != finish_index){ 
			
			auto adj = adjacency[index].toStations; 
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
  return answer;
}

#endif
