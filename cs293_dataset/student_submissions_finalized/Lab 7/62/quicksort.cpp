#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

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
// recursive quicksort
void RQuicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> **ptrarray, int listsize, unsigned int k)
{
	if (listsize==1) return ;
	int size1;
	//generate pivot
	//??
	listOfObjects<TrainInfoPerStation *> *pivot ; // = ??
	//partitioning

	RQuicksort(stnInfoList, ptrarray, size1, k);
	RQuicksort(pivot, ptrarray, listsize-size1, k);

}


// preprocessing + calling recursive quicksort
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList, unsigned int k = 4)
{
	if (stnInfoList == nullptr)	return;
	int size=0;
	listOfObjects<TrainInfoPerStation *> **ptrarray = nullptr;
	// splitting trains which run on multiple days, simulatenously getting size from it
	// 
	if (k>size) k = size;
	//calling quicksort
	RQuicksort(stnInfoList, ptrarray, size, k);

}

#endif