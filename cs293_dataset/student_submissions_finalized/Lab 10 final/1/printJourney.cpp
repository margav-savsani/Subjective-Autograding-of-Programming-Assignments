#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#define ll listOfObjects
using namespace std;

TrainInfoPerStation *find(ll<TrainInfoPerStation *> *all, int j_code){
	while(all != NULL){
		if(all->object->journeyCode == j_code){
			return all->object;
		}
		all = all->next;
	}
	return NULL;
}

struct BFS_Node{
	int stn_index = 0;
	int j_code = 0;
	int arr_time = 0;
	bool days[7] = {0}; 
	int stop_overs = 0;
	ll<TrainInfoPerStation *> *transits;
	BFS_Node(int a, int b, int c, bool *d, int e, ll<TrainInfoPerStation *> *f = NULL){
		stn_index = a;
		j_code = b;
		arr_time = c;
		for(int i = 0; i < 7; i++) days[i] = d[i];
		stop_overs = e;
		if(f) *transits = *f;
	}
	BFS_Node(){}
};

BFS_Node *new_node(BFS_Node *x, TrainInfoPerStation *next_train, int adj_stn, int next_arr_time, int limit, int stopovers){
	bool valid = false;
	bool intersecting_days[7] = {0};
	if(x->j_code == -1){
		for(int i = 0; i < 7; i++){
			intersecting_days[i] = next_train->daysOfWeek[i];
		}
		valid = true;
	}
	else{
		int hour_diff = (x->arr_time) / 100 - (next_train->depTime) / 100, day_diff = 0;
		if(hour_diff < 0){
			hour_diff = 24 + hour_diff;
			day_diff++;
		}
		if(next_train->depTime % 100 > x->arr_time % 100) hour_diff++;
		for(int i = 0; i < 7; i++){
			if(x->days[i]){
				for(int j = 0; j < 7; j++){
					if(next_train->daysOfWeek[j]){
						if(24 * (j - i - day_diff) + hour_diff >= 0
						&& 24 * (j - i - day_diff) + hour_diff <= limit
						){
							valid = true;
							intersecting_days[j] = 1;
						}
					}
				}
			}
		}
	}
	if(!valid) return NULL;
	else{
		int stop_overs_new = x->stop_overs + (x->j_code != next_train->journeyCode);
		ll<TrainInfoPerStation *> *to_add = nullptr;
		if(x->j_code != next_train->journeyCode){
			to_add = new ll<TrainInfoPerStation *>(next_train);
			*(to_add->next) = *(x->transits);
		}
		else{
			*(to_add) = *(x->transits);
		}
		if(stop_overs_new > stopovers) return NULL;
		return new BFS_Node(adj_stn, next_train->journeyCode, next_arr_time, intersecting_days, stop_overs_new, to_add);
	}
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

	// insert your code here;
	//values of the stations indices
	ll<BFS_Node *> *valids = nullptr;
	bool def[7] = {0};
  	int dest_idx = stnNameToIndex.get(destStnName)->value;
  	int src_idx = stnNameToIndex.get(srcStnName)->value;
	BFS_Node *src_node = new BFS_Node(src_idx, -1, 0, def, -1);
	ll<BFS_Node *> *BFS_queue = new ll<BFS_Node *>(src_node);
	ll<BFS_Node *> *q_end = BFS_queue;
	while(BFS_queue != nullptr){
		BFS_Node *curr = BFS_queue->object; //pick the head
		if(curr->stn_index == dest_idx){
			ll<BFS_Node *> *temp = BFS_queue;
			BFS_queue = BFS_queue->next;
			temp->next = valids;
			valids = temp;
		}
		else{
    		//traverse the adjacent stations of the current one
    		listOfObjects<StationConnectionInfo *> *to_list = adjacency[curr->stn_index].toStations;
			while(to_list != nullptr){
				listOfObjects<TrainInfoPerStation *> *trains = to_list->object->trains;
				int adj_stn_idx = to_list->object->adjacentStnIndex;
				while(trains != nullptr){
					TrainInfoPerStation *info = find(stationInfo[adj_stn_idx], trains->object->journeyCode);
					BFS_Node *to_add = new_node(BFS_queue->object, trains->object, adj_stn_idx, info->arrTime, maxTransitTime, maxStopOvers);
					if(to_add){
						ll<BFS_Node *> *new_node = new ll<BFS_Node *>(to_add);
						q_end->next = new_node;
						q_end = q_end->next;
					}
					trains = trains->next;
				}
				to_list = to_list->next;
			}
			BFS_queue = BFS_queue->next;
		}
	}
	// Whenever you need to print a journey, construct a
	// listOfObjects<TrainInfoPerStation *> appropriately, and then
	// use printStationInfo that we had used in Lab 7.
	// printStationInfo is a private member function of
	// the Planner class. It is declared in planner.h and implemented in
	// planner.cpp
	while(valids != nullptr){
		printStationInfo(valids->object->transits);
		valids = valids->next;
	}
	return;
}

#endif
