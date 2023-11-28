#include <iostream>
#include <cmath>
#include "journey.cpp"

using namespace std;

Station::Station(){
	jrnies = new Journey[24];
}

//Adding a journey entry to a station
void Station::add_jrny(Journey jrny){
	int index = (int)(jrny.stime/100);
	while(jrnies[index].stime!=-1) index=(index+1)%24;
	jrnies[index]=jrny;
}

//Returns fastest stime2 for travel to stn2	
int Station::check_train_availability(float stime, char stn2[]){ //have to check least time available ==> modif reqd
	int index = (int)(stime/100);
	int best_stime2 = 2400;
	int i = index;
	do{
		if(strcmp(stn2,jrnies[i].stn2)==0 && jrnies[i].stime>=stime && jrnies[i].stime<best_stime2){
			best_stime2 = jrnies[i].stime;
		}
		i = (i+1)%24;
	}
	while(i!=index);
	return best_stime2;
}
