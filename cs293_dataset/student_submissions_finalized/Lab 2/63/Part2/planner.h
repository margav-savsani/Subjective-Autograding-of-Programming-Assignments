#include<string.h>
#include "dictionary.cpp"
#include "circularQueue.cpp"
#include<iostream>
using namespace std;

#ifndef PLANNER_H
#define PLANNER_H


struct Station {
	char Sta[32];
	Station(string s = ""){
		strcpy(Sta, s.c_str());
	}
};

struct Train{
	Station S;
	float start_time;
	Station D;
	float end_time;
	Train(string s1 = "", float t1 = 0, string s2 = "", float t2 = 0){
		S = Station(s1);
		D = Station(s2);
		start_time = t1;
		end_time = t2; 
	}
};

struct Entry{
	char key[32] = "";
	DynamicQueue<Train>* value;
	Entry(){
		value = new DynamicQueue<Train>;
	}
	~Entry(){
		delete value;
	}
};

template class Dictionary<Entry>;

class Planner {
	Dictionary<Entry> Start;
public:
	bool add_start(string s1, float t1, string s2, float t2);
	bool add(string s1, float t1, string s2, float t2);
	bool query_station(string s1, float t1);
	bool query_journey(string s1, float t1, string s2);
};

#endif