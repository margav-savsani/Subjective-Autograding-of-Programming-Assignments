#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <functional>
// #include <queue>

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
}

//used to store the list of possible journeys to each station in the queue
class queueEntry{
	public:
	int stnName;
	listOfObjects<TrainInfoPerStation *> *common_trains;
};

//used to find the common objects given in the two lists
//the third parameter is the function used for comparison
template <typename T>
listOfObjects<T>* find_common_codes(listOfObjects<T>* L1, listOfObjects<T>* L2, function<bool(T a, T b)> isEqual){
	//change it to a more efficient algorithm later
	listOfObjects<T>* common = NULL;
	listOfObjects<T>* ptr1 = L1;
	while(ptr1){
		listOfObjects<T>* ptr2 = L2;
		while(ptr2){
			if(isEqual(ptr1->object, ptr2->object)){
				if(!common)
					common = new listOfObjects<T>(ptr1->object);
				else{
					auto temp = common;
					common = new listOfObjects<T>(ptr1->object);
					common->next = temp;
				}
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	return common;
}

//prints the list of direct journeys from the source station to the destination station
void Planner::printDirectJourneys(string srcStnName, string destStnName){
	my_ds::queue<queueEntry> stnQueue;
	auto srcStn = stationInfo[stnNameToIndex.get(srcStnName)->value];
	auto destStn = stationInfo[stnNameToIndex.get(destStnName)->value];
	listOfObjects<TrainInfoPerStation*>* list_of_common_stations = find_common_codes<TrainInfoPerStation*>(srcStn, destStn, [](TrainInfoPerStation* x, TrainInfoPerStation* y){return (x->journeyCode == y->journeyCode && x->stopSeq < y->stopSeq);});	
	stnQueue.push({stnNameToIndex.get(srcStnName)->value, list_of_common_stations});
	listOfObjects<TrainInfoPerStation*>* direct_journeys = NULL; //stores the list of direct journeys
	while(!stnQueue.empty()){
		auto stn = stnQueue.front();
		stnQueue.pop();
		auto neighbour = adjacency[stn.stnName].toStations;
		while(neighbour){
			auto trains = neighbour->object->trains;
			auto new_common_codes = find_common_codes<TrainInfoPerStation*>(stn.common_trains, trains, [](TrainInfoPerStation* x, TrainInfoPerStation* y){return (x->journeyCode == y->journeyCode && x->stopSeq < y->stopSeq);});	
			auto test = new_common_codes;
			if(new_common_codes && neighbour->object->adjacentStnIndex != stnNameToIndex.get(destStnName)->value)
				stnQueue.push({neighbour->object->adjacentStnIndex, new_common_codes});
			else if(new_common_codes){
				if(!direct_journeys){
					direct_journeys = new_common_codes;
				}
				else{
					while(new_common_codes){
						auto temp = new_common_codes;
						new_common_codes = new_common_codes->next;
						temp->next = direct_journeys;
						direct_journeys = temp;
					}
				}
			}
			neighbour = neighbour->next;
		}
		//freeing up heap memory
		auto temp = stn.common_trains;
		while(temp){
			auto temp1 = temp;
			temp = temp->next;
			delete temp1;
		}
	}
	if(direct_journeys)
		printStationInfo(direct_journeys);
	else
		cout<<"No direct journeys available"<<endl;
}
