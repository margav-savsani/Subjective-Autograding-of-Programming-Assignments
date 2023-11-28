#ifndef PLANNER_H
#define PLANNER_H
const int MAX_NAME =  32; //incl terminal null
const int START_SIZE =  48;
const int DICT_SIZE =  64;
const int PRIME_POLY = 41;
const int PRIME_MOD = 18973;
const double PHINV= 0.618033988;
using namespace std;
#include<string.h>

struct Journey {
	// define suitable fields here

	char source[MAX_NAME];
	char destination[MAX_NAME];
	float departure;
	float arrival;

	Journey(const char src_[], float dep_, const char dest_[], float arr_){
		strcpy(source, src_);
		departure = dep_;
		strcpy(destination, dest_);
		arrival = arr_;
	}

};

struct Station {
// define suitable fields here
	int size; // possible size without growth
	int tail;//1+index of last filled element -- effective filled size
	char stname[MAX_NAME];// name of the station
	Journey** jq=NULL;
	//ordered array of journeys
	Station(char stn_[]){
		tail=0;
		strcpy(stname,stn_);
		size=START_SIZE;
		jq = new Journey*[size];
	}
	~Station(){
		for(int i=0 ; i<tail; i++){
			delete jq[i];
		}
		delete[] jq;
	}

	int insert(Journey* jrny);//insert a journey in the queue
	void grow();//grow queue size
	int find(float time);//finds starting index in array departing on or after time
	int find(float time, char stn[]);//finds starting index in array with given stn as destination and departing on or after time
	void print_all(float time);//prints all journeys departing on or after time -- used for QUERY_STATION
	int gettail(){return tail;}
};



class Planner {
// define suitable fields here
	//das dictionary of Stations
	Station* tt[DICT_SIZE] = {};
	
	int hash(char stationname[]); //the hash is finally here
	int Find(char station[]);//find dictionary entry corresponding to station
	int FindCreate(char station[]);//find corresponsing dictionary entry to make a new station 
 
	void Route(char* from, float starttime, char* to); //this generates the earliest starting route -- QUERY_JOURNEY

	public:

		~Planner(){
			for(int i = 0;i<DICT_SIZE;i++){
				if (tt[i] != NULL) delete tt[i];
			}
		}
		void Query(); //interface
	
};

#endif