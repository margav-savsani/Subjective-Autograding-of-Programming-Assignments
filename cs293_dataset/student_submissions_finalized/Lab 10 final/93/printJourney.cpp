/*
	This program leaks a ton of memory.
	DO NOT PUT THIS IN A LOOP.
	DO NOT USE THIS IF YOU WANT YOUR CODE TO BE MEMORY EFFICIENT.
	DO NOT USE THIS CODE AT ALL.
		-Ananth Krishna Kidambi
*/
#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
#include <functional>
// #include <queue>
#include <string>

using namespace std;
namespace my_ds{
//implementation of a single ended queue
	template <typename T>
	class queue_node{
	public:
		queue_node<T>* next;
		T object;
	};
	template <typename T> 
	class queue{
		queue_node<T>* start = NULL;
		queue_node<T>* end = NULL;
	public:
		void push(T obj){
			if(!start){
				start = end = new queue_node<T>{NULL, obj};
				return;
			}
			end->next = new queue_node<T>{NULL, obj};
			end = end->next;
		}
		T front(){
			return start->object;
		}
		void pop(){
			if(!start) return;
			auto temp = start;
			start = start->next;
			delete temp;
			if(!start)
				end = NULL;
		}
		bool empty(){
			return !start;
		}
	};

	template<typename T1, typename T2>
	class pair{
	public:
		T1 first;
		T2 second;
		pair(T1 a, T2 b): first{a}, second{b}{}
		pair(): first{NULL}, second{NULL}{}
	};
}
//======================================================================================//
	//Problem Specific code
//======================================================================================//

//..............................................................................//
	//utility code
//..............................................................................//

//represents a tree which stores the history of the journey
class historyNode{
public:
	const historyNode* parent;
	int src_stn;
	int dest_stn;
	TrainInfoPerStation* journey; //object corresponding to the source, NOT THE DESTINATION
	int num_stops; //number of stops till it arrives at the given node
	bool days[7]; //days corresponding to the departure time of the source

	historyNode(int src, int dest, TrainInfoPerStation* jrny, int stops, historyNode* par, const bool* days):src_stn{src}, dest_stn{dest}, num_stops{stops}, journey{jrny}, parent{par}{
		for(int i{0}; i<7; i++){
			this->days[i] = days[i];
		}
	}
	
};

//used to find the common objects given in the two lists
//the third parameter is the function used for comparison

listOfObjects<historyNode*>* find_common_codes(int src, int dest, listOfObjects<TrainInfoPerStation*>* dest_list, historyNode* in, listOfObjects<TrainInfoPerStation*>* out, int maxStops, int maxtime, function<my_ds::pair<bool, bool*>(historyNode* a, TrainInfoPerStation* c, TrainInfoPerStation* b, int maxTransitTime)> isPossible){
	listOfObjects<historyNode*>* list = NULL;
	auto temp = dest_list;
	TrainInfoPerStation* inTrain = NULL;
	while(temp){
		if(temp->object->journeyCode == in->journey->journeyCode){
			inTrain = temp->object;
			break;
		}
		temp = temp->next;
	}
	if(!inTrain){
		return NULL;
	}
	while(out){
		historyNode* temp = NULL;
		auto response = isPossible(in, inTrain, out->object, maxtime);
		if(in->journey->journeyCode == out->object->journeyCode){
			temp = new historyNode{src, dest, out->object, in->num_stops, in, response.second};
		}
		else if(in->num_stops >= maxStops){
			out = out->next;
			continue;
		}
		else if(response.first){
			temp = new historyNode{src, dest, out->object, in->num_stops+1, in, response.second};
		}
		else{
			out = out->next;
			continue;
		}
		auto temp1 = list;
		list = new listOfObjects<historyNode*>{temp};
		list->next = temp1;
		out = out->next;
		delete[] response.second;
	}
	return list;
}

unsigned int conv(int time){
	if(time < 0)
		return unsigned(time);
	return 60*(time/100)+time%100;
}

my_ds::pair<bool, bool*> isPossible(historyNode* c, TrainInfoPerStation* a, TrainInfoPerStation* b, int maxTransitTime){
	// return {true, new bool[7]};
	maxTransitTime*=60;
	bool arr_on_same_day = (unsigned(a->arrTime) >= unsigned(c->journey->depTime));//stores whether the arrival in c->destStn is on the same day as that of departure from c->srcStn
	bool dep_on_same_day = (unsigned(b->depTime) >= unsigned(a->arrTime));//stores whether the arrival from c->destStn is on the same day as that of departure from c->destStn
	bool* intersection = new bool[7];
	if(arr_on_same_day && dep_on_same_day){
		bool isEmpty{1};
		for(int i{0}; i<7; i++){
			intersection[i] = (c->days[i] && b->daysOfWeek[i]);
			if(intersection[i]) isEmpty = 0;
		}
		if(isEmpty) return {false, intersection};
		if(maxTransitTime + conv(a->arrTime) < conv(b->depTime)){
			return {false, intersection};
		}
	}
	else if(arr_on_same_day){
		bool isEmpty{1};
		for(int i{0}; i<7; i++){
			intersection[i] = (c->days[i] && b->daysOfWeek[i]);
			if(intersection[i]) isEmpty = 0;
		}
		if(isEmpty) return  {false, intersection};
		if(maxTransitTime + conv(a->arrTime) < conv(2400) + conv(b->depTime))
			return  {false, intersection};
	}
	else if(dep_on_same_day){
		bool isEmpty{1};
		for(int i{0}; i<7; i++){
			intersection[i] = (c->days[(i+6)%7] && b->daysOfWeek[i]);
			if(intersection[i]) isEmpty = 0;
		}
		if(isEmpty) return  {false, intersection};
		if(maxTransitTime + conv(a->arrTime) < conv(b->depTime))
			return  {false, intersection};
	}
	else{
		bool isEmpty{1};
		for(int i{0}; i<7; i++){
			intersection[i] = (c->days[(i+6)%7] && b->daysOfWeek[i]);
			if(intersection[i]) isEmpty = 0;
		}
		if(isEmpty) return  {false, intersection};
		if(maxTransitTime + conv(a->arrTime) < conv(2400) + conv(b->depTime))
			return  {false, intersection};
	}
	return {true, intersection};
}

//.........................................................................//
	//Actual function
//........................................................................//

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){
	my_ds::queue<historyNode*> stnQueue;
	auto srcStn = stationInfo[stnNameToIndex.get(srcStnName)->value];
	auto destStn = stationInfo[stnNameToIndex.get(destStnName)->value];
	listOfObjects<historyNode*>* final_list = NULL;

	auto jrny_from_src = adjacency[stnNameToIndex.get(srcStnName)->value].toStations;
	while(jrny_from_src){
		auto temp = jrny_from_src->object->trains;
		// cout<<jrny_from_src->object->trains->object->arrTime<<endl;
		while(temp){
			auto node = new historyNode{stnNameToIndex.get(srcStnName)->value, jrny_from_src->object->adjacentStnIndex, temp->object, 0, NULL, temp->object->daysOfWeek};
			if(jrny_from_src->object->adjacentStnIndex == stnNameToIndex.get(destStnName)->value){
				auto temp = final_list; 
				final_list = new listOfObjects<historyNode*>{node};
				final_list->next = temp;
			}
			else
				stnQueue.push(node);
			temp = temp->next;	
		}
		jrny_from_src = jrny_from_src->next;
	}

	while(! stnQueue.empty()){
		auto currJrnyHistory = stnQueue.front();
		stnQueue.pop();
		
		if(currJrnyHistory->num_stops > maxStopOvers)
			continue;

		auto neighbour = adjacency[currJrnyHistory->dest_stn].toStations;
		while(neighbour){
			auto list = find_common_codes(currJrnyHistory->dest_stn, neighbour->object->adjacentStnIndex, stationInfo[currJrnyHistory->dest_stn], currJrnyHistory, neighbour->object->trains, maxStopOvers, maxTransitTime, isPossible);
			if(!list){
				neighbour = neighbour->next;
				continue;
			}
			if(stnNameToIndex.get(destStnName)->value == neighbour->object->adjacentStnIndex){
				auto temp = final_list;
				final_list = list;
				auto temp1 = final_list;
				while(temp1->next)
					temp1 = temp1->next;
				temp1->next = temp;
			}
			else{
				while(list){
					stnQueue.push(list->object);
					list = list->next;
				}
			}
			neighbour = neighbour->next;
		}
	}

	if(!final_list){
		cout<<"NO JOURNEYS AVAILABLE"<<endl;
		return;
	}

	while(final_list){
		cout<<"Journey:............................................"<<endl;
		const historyNode* temp = final_list->object;
		if(!temp)
			continue;
		string res;
		while(temp){
			string res1 = "days: ";
			for(int i{0}; i<7; i++){
				res1 = res1 + to_string(temp->days[i]);
			}
			res1 += "\n";
			res1 += "in time: " + to_string(temp->journey->arrTime) + "\nout time: " + to_string(temp->journey->depTime) + "\n";
			res = "take train " + to_string(temp->journey->journeyCode) + " from " + stnNameToIndex.getKeyAtIndex(temp->src_stn) + " to " + stnNameToIndex.getKeyAtIndex(temp->dest_stn) + ".\n" + res1 + res;
			temp = temp->parent;
		}	
		cout<<res<<endl;
		final_list = final_list->next;
	}
}

#endif
