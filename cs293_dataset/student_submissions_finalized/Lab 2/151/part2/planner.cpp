#include <iostream>
#include "planner.h"

using namespace std;


// constructor

Planner::Planner(){
	N = 64;
	a = new vector<Journey>[N];
}


// performs hash function on Station1 string only

int Planner::hashValue(string s1){

	long long sum = s1[0];
	int p = 31;

	for (int i = 1; i < s1.length(); ++i)
	{
		sum = sum * p + s1[i];					// polynomial accumulation
	}

	double pol = gold_conj * sum;				
	return int(N * (pol - (long)pol));			// returns N * frac{pol}
}


// creates a new journey, and pushes it into the dictionary.
// the chain is sorted by start time of journeys

void Planner::newJourney(string s1, int t1, string s2, int t2){
	int h = hashValue(s1);
	if(a[h].size() == 0) a[h].push_back(Journey{s1, t1, s2, t2});		// if vector is empty, journey is simply pushed in
	else {
		for( auto i = a[h].begin(); i != a[h].end(); ++i){				// if vector has elements:
			if(t1 >= a[h].back().ts) {									// if start time is largest, immediately pushed to back
				a[h].push_back(Journey{s1, t1, s2, t2});
				break;
			}
			else if(t1 > (*i).ts) continue;
			else{
				a[h].insert( i, Journey{s1, t1, s2, t2});				// else inserted at proper location according to time
				break;
			}
		}
	}
}


// returns all journeys that occur after specified time from given station
// the journeys are returned in a vector

vector<Journey> Planner::queryStation(string s1, int t){
	int h = hashValue(s1);
	vector<Journey> v;
	for( auto i = a[h].begin(); i != a[h].end(); ++i) {
		if( (*i).ts >= t ) v.push_back(*(i));							// journeys with start time >= t are pushed out
	}

	return v;
}


// returns a vector of journeys, that satisfies the conditions:
// the start time of the train must be as min as possible
// and there can be one intermediate station

vector<Journey> Planner::queryJourney(string s1, int t, string s2){
	int h = hashValue(s1);
	vector<Journey> v;
	for( auto i = a[h].begin(); i != a[h].end(); ++i){						// iterator, for going through all elements
		if(t <= (*i).ts){		
			if( (*i).stat_end == s2 ){
				v.push_back(*(i));											// if end station is correct, then return current journey
				break;
		 	} else {														// if not correct, then check if the end station can act as intermediate
				int h2 = hashValue((*i).stat_end);
				bool found = false;
				for( auto j = a[h2].begin(); j != a[h2].end(); ++j){
					if( (*j).ts >= (*i).te && (*j).stat_end == s2 ){		// if intermediate station has journey to end station
						v.push_back((*i));									// both jouney1 and journey2 are pushed
						v.push_back((*j));
						found = true;
						break;
					}
				}
				if(found) break;
			}
		} else {
			continue;
		}
	}
	return v;
}
