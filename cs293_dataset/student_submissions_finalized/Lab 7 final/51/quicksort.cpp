#ifndef QUICKSORT_CPP

#define QUICKSORT_CPP
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <iostream>

# ifndef STD_HEADERS
#include "std_headers.h"

# endif

# ifndef PLANNER_H
#include "planner.h"

# endif

# ifndef DICTIONARY_H
#include "dictionary.h"

# endif

# ifndef CODES_H
#include "codes.h"

# endif
//compares the date of both traininfoperstation and checks which is first 
//if the first one aopears first returns true
//for same date lesser arrtime is considered first and returns true if c1 has less arrtime
bool compare(listOfObjects <TrainInfoPerStation *> *c1, listOfObjects <TrainInfoPerStation *> *pivot)
{
	for (int i = 0; i < 7; i++)
	{
		if (c1->object->daysOfWeek[i] && pivot->object->daysOfWeek[i])
		{
			if (c1->object->daysOfWeek[i])
			{
				if (c1->object->arrTime < pivot->object->arrTime)
				{
					return true;
				}
				else
				{
					return false;
				}
				if (c1->object->arrTime == pivot->object->arrTime)
				{
					if (c1->object->depTime <= pivot->object->depTime)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}

		if (c1->object->daysOfWeek[i] || pivot->object->daysOfWeek[i])
		{
			if (c1->object->daysOfWeek[i])
			{
				return true;
			}
			if (pivot->object->daysOfWeek[i])
			{
				return false;
			}

		}

	}
	return false;
}


//to get the j th element pointer in the list 
//directly accesses the pointer without savig it so the attributes can be modified 
listOfObjects <TrainInfoPerStation *> *get_vec(listOfObjects <TrainInfoPerStation *> *a, int start)
{
	a->next;
	if (start == 0)
	{
		return a;
	}
	else
	{
		return get_vec(a->next, start - 1);
	}
}

//swap the objects of given indices
//swaps only the objects of the indices not the next& prev and other attributes
void update(vector<listOfObjects <TrainInfoPerStation *> *> myVector, int start, int end)
{
	TrainInfoPerStation *s1 = get_vec(myVector[0], start)->object;
	TrainInfoPerStation *s2 = get_vec(myVector[0], end - 1)->object;
	get_vec(myVector[0], start)->object = s2;
	get_vec(myVector[0], end - 1)->object = s1;

}


//implementation of quicksort 
//sorting recursively
void sorting(vector<listOfObjects <TrainInfoPerStation *> *> myVector, int start, int end, int K)
{
	if (end - start == 2)
	{

		if (compare(get_vec(myVector[0], end - 1), get_vec(myVector[0], start)))
		{
			update(myVector, start, end);
		}

	}
	srand(time(NULL));
	if (end - start > 2)
	{
		int piv_in;
		piv_in = start + (rand() % (end - start));

		int i = start;
		int j = end - 1;

		update(myVector, piv_in, end);

		while (i < j) // partition function

		{

			while (compare(get_vec(myVector[0], i), get_vec(myVector[0], end - 1)) && i < end - 1)
			{
				i++;

			}

			while (compare(get_vec(myVector[0], end - 1), get_vec(myVector[0], j)) && j > 0)
			{

				j--;

			}

			if (i < j)
			{
				update(myVector, i, j + 1);
			}
		}

		update(myVector, i, end);

		if (i - start > 1)
		{

			sorting(myVector, start, i, K);

		}
		if (end - i > 1)
		{

			sorting(myVector, i + 1, end, K);
		}
	}

}

//does the preprocessing and implements the sorting  
void Planner::Quicksort(listOfObjects <TrainInfoPerStation *> *stnInfoList)
{
	// A few static variable declarations
	static int K = 4; // Parameter to be experimented with
	static int recursionLevel = -1; // This can be used to find out at which
	// level of the recursion you are in

	// Increment recursion level on entering the function
	recursionLevel++;
	int length = 0;
	int prev_index;
	vector<listOfObjects <TrainInfoPerStation *> *> myVector;
	vector<listOfObjects <TrainInfoPerStation *> *> elems;

//preprocessing adding the list elements to a vector
//a vector that contains the pointers to the n/k partitioned lists 
	if (recursionLevel == 0)
	{
		listOfObjects <TrainInfoPerStation *> *dummy;
		dummy = stnInfoList;
		while (dummy != NULL)
		{
			length++;
			dummy = dummy->next;

		}

		dummy = stnInfoList;
		if (length % K == 0)
		{
			myVector.reserve(length / K);
		}

		if (length % K != 0)
		{
			myVector.reserve(length / K + 1);
		}
		int len = 0;
		while (dummy != NULL)
		{
			if (len % 4 == 0)
			{
				myVector.push_back(dummy);
			}
			len++;
			dummy = dummy->next;
		}

		
	
		sorting(myVector, 0, length, K);
	}

	// Decrement recursion level before leaving the function
	recursionLevel--;
	return;
}

void Planner::QuicksortSimple(listOfObjects <TrainInfoPerStation *> *stnInfoList, int start, int end)
{
	// A few static variable declarations
	static int K = 4; // Parameter to be experimented with
	static int recursionLevel = -1; // This can be used to find out at which
	// level of the recursion you are in

	// Increment recursion level on entering the function
	recursionLevel++;

	// If you need to set up additional storage (upto n/K TrainInfoPerStation
	// elements), it's ok to do it *once* using static variables/array.
	// Using the static recursionLevel, you can ensure that the storage
	// allocation is done only the first time Quicksort is called, and not
	// in every recursive call.
	//
	// Note that if you allocate space for upto n/K TrainInfoPerStation in
	// each recursive call, you will end up using much more than n/K space
	// overall.  So you MUST NOT allocate space in each recursive call.
	//
	// A variable/array defined using static is not created afresh in
	// each recursive call.  Instead, a single copy of it is maintained
	// across all recursions.

	if (recursionLevel == 0)
	{

	}

	recursionLevel--;
	return;
}

# endif