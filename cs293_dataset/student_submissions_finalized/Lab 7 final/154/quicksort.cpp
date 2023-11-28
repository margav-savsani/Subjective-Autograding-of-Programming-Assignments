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
#include<cassert>

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
//
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

TrainInfoPerStation *choose_pivot(listOfObjects<TrainInfoPerStation *> **pivotals, int start, int end, int K){
	int pivotidx = start + rand() % (end - start + 1); // choose pivot index
	listOfObjects<TrainInfoPerStation *> * temp = pivotals[pivotidx / K ];
	for (int i=0; i< pivotidx%K; i++){ // so max k iterations
		temp = temp->next;
	}
	return new TrainInfoPerStation(*(temp->object));
}

bool lessthan(TrainInfoPerStation *t1, TrainInfoPerStation *t2){
	// custom less than function
	int t1d = 0;
	int t2d = 0;
	for(int i=0; i<7; i++){
		if(t1->daysOfWeek[i]) {t1d = i; break;}
	}
	for(int i=0; i<7; i++){
		if(t2->daysOfWeek[i]) {t2d = i; break;}
	}
	if(t1d == t2d) return (unsigned int) t1->depTime < (unsigned int) t2->depTime;
	else return t1d < t2d;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
	// A few static variable declarations
	static int K = 4; // Parameter to be experimented with
	static int recursionLevel = -1; // This can be used to find out at which
									// level of the recursion you are in
	static int N = 0;
	static listOfObjects<TrainInfoPerStation *> ** pivotals = nullptr; // array of pointers to find pivots in n/k
	static int start = 0; // start index of the partition
	static int end = -1; // end index of partition
	static listOfObjects<TrainInfoPerStation *> *endp = nullptr; // pointer to last element of the partition

	recursionLevel++; // Increment recursion level on entering the function
	
	if (recursionLevel == 0){ // preprocessing

		srand(time(0)); // seed the rng
		// finding N, end
		listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
		while(temp!=nullptr){
			endp = temp;
			temp = temp->next;
			N++;
		}
		end = N-1;
		// initialising pivotals
		pivotals = new listOfObjects<TrainInfoPerStation *>*[(N-1)/K + 1];
		temp = stnInfoList;
		pivotals[0]=temp;
		for(int i=0; i<(N-1)/K; i++){
			for(int j=0; j<K; j++){
				temp = temp->next;
			}
			pivotals[i+1] = temp;
		}
	}

	if(end > start){
		// partitioning
		TrainInfoPerStation *pivot = choose_pivot(pivotals, start, end, K);
		listOfObjects<TrainInfoPerStation *> *left = stnInfoList;
		listOfObjects<TrainInfoPerStation *> *right = endp;
		int leftidx = start;
		int rightidx = end;
		while(true){
			while(lessthan(left->object, pivot)){
				left = left->next;
				leftidx++;
			}
			while(lessthan(pivot, right->object)){
				right = right->prev;
				rightidx--;
			}
			if(rightidx > leftidx){
				swap(left->object, right->object);
				left = left->next;
				right = right->prev;
				leftidx++;
				rightidx--;
			}
			else{break;}
		}
		delete pivot;

		// further recursive calls
		int start_o = start; // original start
		int end_o = end; // original end
		listOfObjects<TrainInfoPerStation *> *endp_o = endp; // original end pointer

		start = start_o; end = rightidx; endp = right; // changing static variables before recursive call
		Quicksort(stnInfoList);

		start = rightidx+1; end = end_o; endp = endp_o; // chnaging static variables before recursive call
		Quicksort(right->next);
	}
	
	// Decrement recursion level before leaving the function
	recursionLevel--;
	if (recursionLevel == -1){
		delete[] pivotals;
		N = 0;
		start = 0;
	}
	return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
	// A few static variable declarations
	static int K = 4; // Parameter to be experimented with
	static int recursionLevel = -1; // This can be used to find out at which
									// level of the recursion you are in
	static int N = 0;
	static listOfObjects<TrainInfoPerStation *> ** pivotals = nullptr; // array of pointers to find pivots in n/k
	static listOfObjects<TrainInfoPerStation *> *endp = nullptr; // pointer to last element of the partition

	recursionLevel++; // Increment recursion level on entering the function
	
	if (recursionLevel == 0){ // preprocessing

		srand(time(0)); // seed the rng
		// finding N, end
		listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
		while(temp!=nullptr){
			endp = temp;
			temp = temp->next;
			N++;
		}
		// initialising pivotals
		pivotals = new listOfObjects<TrainInfoPerStation *>*[(N-1)/K + 1];
		temp = stnInfoList;
		pivotals[0]=temp;
		for(int i=0; i<(N-1)/K; i++){
			for(int j=0; j<K; j++){
				temp = temp->next;
			}
			pivotals[i+1] = temp;
		}
	}

	if(end > start){
		// partitioning
		TrainInfoPerStation *pivot = choose_pivot(pivotals, start, end, K);
		listOfObjects<TrainInfoPerStation *> *left = stnInfoList;
		listOfObjects<TrainInfoPerStation *> *right = endp;
		int leftidx = start;
		int rightidx = end;
		while(true){
			while(lessthan(left->object, pivot)){
				left = left->next;
				leftidx++;
			}
			while(lessthan(pivot, right->object)){
				right = right->prev;
				rightidx--;
			}
			if(rightidx > leftidx){
				swap(left->object, right->object);
				left = left->next;
				right = right->prev;
				leftidx++;
				rightidx--;
			}
			else{break;}
		}
		delete pivot;

		// further recursive calls
		listOfObjects<TrainInfoPerStation *> *endp_o = endp; // original end pointer

		endp = right; // changing static variables before recursive call
		QuicksortSimple(stnInfoList, start, rightidx);

		endp = endp_o; // chnaging static variables before recursive call
		QuicksortSimple(right->next, rightidx+1, end);
	}
	
	// Decrement recursion level before leaving the function
	recursionLevel--;
	if (recursionLevel == -1){
		delete[] pivotals;
		N = 0;
	}
	return;
}

#endif
