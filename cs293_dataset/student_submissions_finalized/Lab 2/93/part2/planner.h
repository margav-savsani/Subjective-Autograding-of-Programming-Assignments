#ifndef PLANNER_H
#define PLANNER_H
#include <iostream>
#include <string.h>
#include "dictionary.cpp"

#define EPSILON 1E-5


using namespace std;

struct Query{
	//stores the query entered by the user 
	char action[15]; //ADD or QUERY_STATION or QUERY_JOURNEY or EXIT
	float start_time, end_time; 
	char start_station[32];
	char end_station[32];
	void get_query(){
		//takes the query as input from stdin
		cin>>action;
		if(strcmp(action, "ADD")==0){
			cin>>start_station;
			cin>>start_time;
			cin>>end_station;
			cin>>end_time;
		}
		else if(strcmp(action, "QUERY_STATION")==0){
			cin>>start_station;
			cin>>start_time;
		}
		else if(strcmp(action, "QUERY_JOURNEY")==0){
			cin>>start_station;
			cin>>start_time;
			cin>>end_station;
		}
		else if(strcmp(action, "EXIT")==0){
			return;
		}
		else{
			cout<<"Invalid Query"<<endl;
		}
	}
};

class Planner {
	// define suitable fields here
	Dictionary d; //stores the journeys 
	void add_journey(Query q){
		//adds a journey to the dictionary
		Entry* e = d.get(q.start_station);
		Journey j;
		strcpy(j.src_station, q.start_station);
		strcpy(j.dest_station, q.end_station);
		j.start_time = q.start_time;
		j.end_time = q.end_time;
		if(e){
			(e->j).push_back(j);
		}
		else{
			d.put(j);
		}
	}

	void Query_station(char* src_station, float start_time){
		//Finds the next train starting from this station
		Entry* e = d.get(src_station);
		if(e==NULL){
			cout<<"Station Not Found"<<endl;
			return;
		}
		bool found = 0;
		for(auto a: e->j){
			if(a.start_time+EPSILON>start_time){
				cout<<a.src_station<<" "<<a.start_time<<" "<<a.dest_station<<endl;
				found = 1;
			}
		}
		if(!found)	
			cout<<"No Trains Available"<<endl;
	}

	void Query_journey(char* start_station, float start_time, char* end_station){
		//finds the train between start_station and end_station after start_time that leaves the earliest
		Entry* e = d.get(start_station);
		if(!e){
			cout<<"Invalid Start Station";
			return;
		}
		Journey min_journey; //stores the relevent journey that starts the earliest
		bool direct = 0; //stroes 1 if the journey is direct 
		bool found = 0; //stores whether an appropriate journey has been found
		Journey min_journey2; //stores the second journey for a journey with a layover
		min_journey.start_time = start_time+1E100;
		for(auto a: e->j){
			if(a.start_time+EPSILON>start_time&&a.start_time<min_journey.start_time){
				if(strcmp(a.dest_station, end_station)==0){
					min_journey = a;
					direct = 1;
					found = 1;
				}
				else{
					Entry* e1 = d.get(a.dest_station);
					if(e1==NULL) continue;
					for(auto b: e1->j){
						if(strcmp(b.dest_station, end_station)==0&&a.end_time+EPSILON<b.start_time){
							min_journey = a;
							direct = 0;
							found = 1;
							min_journey2 = b;
							break;
						}
					}
				}
			}
		}
		if(!found){
			cout<<"No Trains Between These Stations"<<endl;
			return;
		}
		if(direct){
			cout<<"Starts at: "<<min_journey.start_time<<endl;
		}
		else{
			cout<<"Starts at: "<<min_journey.start_time<<endl;
			cout<<"Intermediate Station: "<<min_journey.dest_station<<endl;
			cout<<"Leave Time: "<<min_journey2.start_time<<endl; 
		}
	}
public:
	void interact(){
		//interacts with the user and takes input from stdin
		Query q;
		while(true){
			cout<<">>>";
			q.get_query();
			if(strcmp(q.action, "ADD")==0){
				add_journey(q);
			}
			else if(strcmp(q.action, "QUERY_STATION")==0){
				Query_station(q.start_station,q.start_time);
			}
			else if(strcmp(q.action, "QUERY_JOURNEY")==0){
				Query_journey(q.start_station,q.start_time,q.end_station);
			}
			else if(strcmp(q.action, "EXIT")==0){
				return;
			}
			else{
				cout<<"Invalid Query"<<endl;
			}
		}
	}
};

#endif