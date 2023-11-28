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

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
	int x;x=rand()%10+1;
	listOfObjects<TrainInfoPerStation *> *c=stnInfoList;
	for(int i=0;i<x;i++){
		c=c->next;
	}
	c->next=nullptr;
	// Put your code here.
}
