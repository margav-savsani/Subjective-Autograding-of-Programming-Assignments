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

int k = 10;

bool operator<(TrainInfoPerStation a, TrainInfoPerStation b)
{
	int val1 = 0;
	for (int i = 0; i < 7; i++)
	{
		if (a.daysOfWeek[i])
		{
			val1 = i;
			break;
		}
	}

	int val2 = 0;
	for (int i = 0; i < 7; i++)
	{
		if (b.daysOfWeek[i])
		{
			val2 = i;
			break;
		}
	}

	int comp1 = val1 * 2400 + a.arrTime;
	int comp2 = val2 * 2400 + b.arrTime;

	return comp1 < comp2;
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
	// choosing the pivot randomly.
	int length = 0;
	int kcount = 0;

	// O(n) time
	while (stnInfoList->next != nullptr) {
		length++;
	}

	void *raw_memory = operator new[](length/k * sizeof(TrainInfoPerStation));
	TrainInfoPerStation *pivots = static_cast<TrainInfoPerStation *>(raw_memory);

	// O(n) time. 
	while (stnInfoList->next != nullptr)
	{
		if (kcount % (length/k) == 0)
		{
			pivots[kcount / (length/k)] = *stnInfoList->object;
		}
		kcount++;
	}

	int idx = rand() % length/k;
	int step = rand() % k; 

	// modify logic to step after choosing intermediate pivot. 

	return;
}
