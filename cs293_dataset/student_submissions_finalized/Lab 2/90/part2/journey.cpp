#include <iostream>
#include <cmath>
#include "planner.h"

using namespace std;

//initialising empty jrnies to weird values to distinguish them
Journey::Journey(){
		stime = ftime = -1;
		strcpy(stn2,"NULL");
}	
	
//Setting journey variables.
void Journey::set_jrny_details(float stime, char stn2[], float ftime){
	this->stime = stime;
	this->ftime = ftime;
	strcpy(this->stn2, stn2);
}

