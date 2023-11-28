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
	BFS_Node(int a, int b, int c, bool *d, int e, ll<TrainInfoPerStation *> *f){
		stn_index = a;
		j_code = b;
		arr_time = c;
		for(int i = 0; i < 7; i++) days[i] = d[i];
		stop_overs = e;
		*transits = *f;
	}
};

BFS_Node *new_node(BFS_Node *x, TrainInfoPerStation *next_train, int adj_stn, int next_arr_time, int limit){
	bool valid = false;
	bool intersecting_days[7] = {0};
	if(next_train->depTime - x->arr_time >= 0){
		for(int i = 0; i < 7; i++){
			if(x->days[i] && next_train->daysOfWeek[i]){
				valid = next_train->depTime - x->arr_time < limit; 
				intersecting_days[i] = true;
			}
		}
	}
	else{
		for(int i = 0; i < 7; i++){
			if(x->days[i] && next_train->daysOfWeek[(i + 1) % 7]){
				valid = 2400 - next_train->depTime + x->arr_time < limit; 
				intersecting_days[(i + 1) % 7] = true;
			}
		}	
	}
	if(!valid) return NULL;
	else{
		int stop_overs_new = x->stop_overs + (x->j_code != next_train->journeyCode);
		ll<TrainInfoPerStation *> *to_add = nullptr;
		if(x->j_code != next_train->journeyCode){
			to_add = new ll<TrainInfoPerStation *>(next_train);
			to_add->next = x->transits;
		}
		else{
			to_add = x->transits;
		}
		return new BFS_Node(adj_stn, next_train->journeyCode, next_arr_time, intersecting_days, stop_overs_new, to_add);
	}
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

	// insert your code here

	ll<BFS_Node *> *BFS_queue = nullptr;

	// Whenever you need to print a journey, construct a
	// listOfObjects<TrainInfoPerStation *> appropriately, and then
	// use printStationInfo that we had used in Lab 7.
	// printStationInfo is a private member function of
	// the Planner class. It is declared in planner.h and implemented in
	// planner.cpp


	return;
}

#endif
