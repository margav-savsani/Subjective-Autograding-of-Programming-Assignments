#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

bool lessthan(TrainInfoPerStation * t1, TrainInfoPerStation * t2){
    for(int i=0; i<7; i++){
		if(t1->daysOfWeek[i]==t2->daysOfWeek[i]) continue;
		return t1->arrTime < t2->arrTime;
	}
	return true;
}

TrainInfoPerStation* choose_pivot(listOfObjects<TrainInfoPerStation *> *stnInfoList){

}

void Quicksort(listOfObjects<TrainInfoPerStation *> * stnInfoList)
{
    // Put your code here.
    // progress
}
