#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP
#include <cstdlib>
#include <vector>
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

// If you are using the updated planner.cpp, then you simply need to
// sort the list of TrainInfoPerStation objects in stnInfoList.  The
// function that calls Quicksort in planner.cpp (i.e. printStationInfo)
// will then automatically pretty-print the sorted list.
//
// USING THE UPDATED planner.cpp FILE IS STRONGLY RECOMMENDED
//
// Notice that there is a variable K in Quicksort that is to be used as
// described in the problem statement in problems_statement.pdf
// Specifically, if the first call to Quicksort has an argument list of
// n TrainInfoPerStation objects, you can't use additional storage space
// for more than n/K TrainInfoPerStation objects overall (across all
// recursive calls), you must implement random choice for pivot (i.e.
// each element in the list being sorted should be equally likely to
// be chosen as pivot), and each call to finding a random pivot
// within the list being sorted must take time within O(K), regardless
// of how long the list to be sorted is.
//
// In the function signature of Quicksort, stnInfoList is a list of
// TrainInfoPerStation objects that is to be sorted. In the updated
// planner.cpp file, this list (unsorted) is already prepared for you,
// and you need to simply ensure that the list is sorted (see note
// below about sorting order) when Quicksort returns.
//
// A note about the sorting order:
//
// The final list should be sorted with respect to day of week (first)
// and departure time within the day (next).  Thus Sun 900 < Sun 1100
// < Mon 800 < Thu 700 < Fri 1200
//
//
// Based on how we saw some of you were trying to approach the problem
// in the lab of Sep 23, we are providing another function QuicksortSimple
// with a slightly extended signature. In addition to the list stnInfoList,
// which is passed as the first argument to QuicksortSimple, there are two
// integer parameters "start" and "end", just like in the usual Quicksort
// of an array (as in Prof. Naveen Garg's lectures, for example).
// How do we interpret these "start" and "end" variables in this case,
// when we are trying to sort a list?
// Well, here is one way of thinking about this: If we start
// counting elements of the list starting from stnInfoList and
// chasing "next" pointers until nullptr is reached, the corresponding
// elements can be thought of as elements of a (virtual) array indexed
// from 0 onwards.
// Then, the call to Quicksort must sort the part of the list
// consisting of elements at indices start, start+1, ... until end
// of the above virtual array.
// The whole point of this assignment is to have you do this without
// converting the whole list to an array.
//
// Remember it is indeed possible to solve this problem using the
// function Quicksort with only stnInfoList as its argument.  However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead.  Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points.

bool TrainInfoPerStation::operator<(TrainInfoPerStation trainInfo)
{
	int j = 0, k = 0;
	for (int i = 0; i < 7; i++)
	{
		if (this->daysOfWeek[i])
		{
			j = i;
		}
		if (trainInfo.daysOfWeek[i])
		{
			k = i;
		}
	}
	if (j < k)
	{
		return true;
	}
	else if (j > k)
	{
		return false;
	}
	else if (this->depTime < trainInfo.depTime)
	{
		return true;
	}
	else if (this->depTime > trainInfo.depTime)
	{
		return false;
	}
	else if (this->arrTime < trainInfo.arrTime)
	{
		return true;
	}
	else if (this->arrTime > trainInfo.arrTime)
	{
		return false;
	}
	else
	{
		return this->journeyCode < trainInfo.journeyCode;
	}
}
bool TrainInfoPerStation::operator>(TrainInfoPerStation trainInfo)
{
	int j = 0, k = 0;
	for (int i = 0; i < 7; i++)
	{
		if (this->daysOfWeek[i])
		{
			j = i;
		}
		if (trainInfo.daysOfWeek[i])
		{
			k = i;
		}
	}
	if (j > k)
	{
		return true;
	}
	else if (j < k)
	{
		return false;
	}
	else if (this->depTime > trainInfo.depTime)
	{
		return true;
	}
	else if (this->depTime < trainInfo.depTime)
	{
		return false;
	}
	else if (this->arrTime > trainInfo.arrTime)
	{
		return true;
	}
	else if (this->arrTime < trainInfo.arrTime)
	{
		return false;
	}
	else
	{
		return this->journeyCode > trainInfo.journeyCode;
	}
}

listOfObjects<TrainInfoPerStation *> *getEnd(listOfObjects<TrainInfoPerStation *> *start,
											 vector<listOfObjects<TrainInfoPerStation *> *> startIndices, int begin, int end, int K)
{
	// print(start);
	// cout<<len<<endl;
	int closest_partition = (end - begin) / K;

	listOfObjects<TrainInfoPerStation *> *ptr = startIndices[closest_partition];

	int counter = closest_partition * K;

	while (counter < end)
	{
		ptr = ptr->next;
		counter++;
	}
	return ptr;
}

int length(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
	listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList;
	int count = 0;
	while (ptr != nullptr)
	{
		ptr = ptr->next;
		count++;
	}
	return count;
}

void generatePivot(listOfObjects<TrainInfoPerStation *> *&pivot,
				   vector<listOfObjects<TrainInfoPerStation *> *> startIndices, int start, int end, int K)
{
	// cout<<start<<" "<<end<<endl;
	int random = start + rand() % (end - start+1);
	int closest_partition = random / K;
	int counter = closest_partition * K - start;
	listOfObjects<TrainInfoPerStation *> *starter = startIndices[closest_partition];

	while (counter < (random - start))
	{
		starter = starter->next;
		counter++;
	}
	pivot = starter;
}

void PreProcess(listOfObjects<TrainInfoPerStation *> *start,
				vector<listOfObjects<TrainInfoPerStation *> *> &startIndices, int len, int K)
{
	int parititions = (len % K == 0) ? len / K : (len / K + 1);
	listOfObjects<TrainInfoPerStation *> *ptr = start;
	int j = 0;
	for (int i = 0; i < len; i++)
	{

		if (j == i / K)
		{
			startIndices[j] = ptr;

			j++;
		}
		ptr = ptr->next;
	}
}

listOfObjects<TrainInfoPerStation *> *Planner::Partition(
	listOfObjects<TrainInfoPerStation *> *startPtr,
	listOfObjects<TrainInfoPerStation *> *endPtr,
	listOfObjects<TrainInfoPerStation *> *pivot, int start, int end, int &index)
{
	listOfObjects<TrainInfoPerStation *> *s = startPtr;
	listOfObjects<TrainInfoPerStation *> *e = endPtr;
	if (start == end)
	{
		index = 0;
		return startPtr;
	}

	int i = start;
	int j = end;
	TrainInfoPerStation *p = pivot->object;
	while (true)
	{
		// print(startPtr);
		while (*p < *e->object)
		{
			e = e->prev;
			j--;
		}
		while (*s->object < *p)
		{
			s = s->next;
			i++;
		}

		if (i < j)
		{

			TrainInfoPerStation *temp = s->object;
			s->object = e->object;
			e->object = temp;
		}
		else
		{

			index = j;
			return e;
		}
	}
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{

	static int K = 3;
	static int len;
	static int start;
	static int end;
	static int size;
	static vector<listOfObjects<TrainInfoPerStation *> *> startIndices;

	// static int check =0;            // Parameter to be experimented with
	static int recursionLevel = -1; // This can be used to find out at which

	// Increment recursion level on entering the function
	recursionLevel++;
	if (recursionLevel == 0)
	{
		start = 0;
		end = length(stnInfoList) - 1;
		len = (end - start + 1);
		size = (len % K == 0) ? len / K : len / K + 1;
		startIndices.resize(size);
		PreProcess(stnInfoList, startIndices, len, K);
	}
	if (start >= end)
	{
		recursionLevel--;
		return;
	}

	int index;
	listOfObjects<TrainInfoPerStation *> *endPtr = getEnd(stnInfoList, startIndices, start, end, K);

	listOfObjects<TrainInfoPerStation *> *pivot = nullptr;
	generatePivot(pivot, startIndices, start, end, K);

	listOfObjects<TrainInfoPerStation *> *partition = nullptr;

	partition = Partition(stnInfoList, endPtr, pivot, start, end, index);
	int tempEnd = end;
	// int	tempStart = start;
	end = index - 1;
	Quicksort(stnInfoList);
	start = index + 1;
	end = tempEnd;
	Quicksort(partition->next);

	recursionLevel--;
	return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
	// A few static variable declarations
	if (end <= start)
		return;
	static int K = 3;
	static int len;
	static int size;
	static vector<listOfObjects<TrainInfoPerStation *> *> startIndices;

	// static int check =0;            // Parameter to be experimented with
	static int recursionLevel = -1; // This can be used to find out at which

	// Increment recursion level on entering the function
	recursionLevel++;
	if (recursionLevel == 0)
	{

		len = (end - start + 1);
		size = (len % K == 0) ? len / K : len / K + 1;
		startIndices.resize(size);
		PreProcess(stnInfoList, startIndices, len, K);
	}
	int index;
	listOfObjects<TrainInfoPerStation *> *endPtr = getEnd(stnInfoList, startIndices, start, end, K);

	listOfObjects<TrainInfoPerStation *> *pivot = nullptr;
	generatePivot(pivot, startIndices, start, end, K);

	listOfObjects<TrainInfoPerStation *> *partition = nullptr;

	partition = Partition(stnInfoList, endPtr, pivot, start, end, index);

	QuicksortSimple(stnInfoList, start, index - 1);
	QuicksortSimple(partition->next, index + 1, end);

	recursionLevel--;
	return;
}

#endif
