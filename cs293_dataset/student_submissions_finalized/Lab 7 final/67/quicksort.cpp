#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP
#include<vector>

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
// sort the list of TrainInfoPerStation objects in stnInfoList.	The
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
// and departure time within the day (next).	Thus Sun 900 < Sun 1100
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
// function Quicksort with only stnInfoList as its argument.	However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead.	Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points.

bool isLessThanOrEqualTo(TrainInfoPerStation* i1, TrainInfoPerStation* i2){
	for(int i=0;i<7;i++){
		if(i1->daysOfWeek[i] && i2->daysOfWeek[i])	break;
		if(i1->daysOfWeek[i] && !i2->daysOfWeek[i])	return true;
		if(!i1->daysOfWeek[i] && i2->daysOfWeek[i])	return false;
	}
	if(i1->depTime <= i2 ->depTime){
		return true;
	}
	return false;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
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
	// overall.	So you MUST NOT allocate space in each recursive call.
	//
	// A variable/array defined using static is not created afresh in
	// each recursive call.	Instead, a single copy of it is maintained
	// across all recursions.
	static vector<listOfObjects<TrainInfoPerStation*>*> storedAddresses; // This will store the address for Every Kth node.
	static int originalNumberOfNodes;
	static int leftMostUnsortedNode;
	static int numberOfSortedNodes;
	static int prevPivotIndex;
	if (recursionLevel == 0) {
		// Find length of the list stnInfoList, if needed.
		// Allocate additional space for upto n/K TrainInfoPerStation objects
		// if needed.
		// Do other things that you may want to do only at the beginning
		// as a pre-processing step.
		originalNumberOfNodes = 0;
		numberOfSortedNodes = 0;
		listOfObjects<TrainInfoPerStation*>* curr = stnInfoList;
		storedAddresses.clear();
		while(curr){
			if( originalNumberOfNodes%K == 0 ) {
				storedAddresses.push_back(curr);
			}
			originalNumberOfNodes++;
			curr = curr->next;
		}
		prevPivotIndex = originalNumberOfNodes;
	}
	int end = prevPivotIndex-1;
	// static variable and recursionLevel 0 works completed
	if(!( numberOfSortedNodes<end )){ // If single elements comes.
		recursionLevel--;
		if(numberOfSortedNodes==end){
			numberOfSortedNodes++;
		}
		return;
	}
	
	// Put your code for the core of QuicksortSimple here
	srand(time(0));
	int pivotIndex = rand()%(end - numberOfSortedNodes) + numberOfSortedNodes;
	listOfObjects<TrainInfoPerStation*>* pivot;
	int shift = pivotIndex % K;
	pivot = storedAddresses[pivotIndex/K];
	while(shift--){
		pivot = pivot -> next;
	}
	// Rearranging terms
	listOfObjects<TrainInfoPerStation*>* leftOfPivot = pivot -> prev, *rightOfPivot = pivot -> next;
	int leftPointerIndex = pivotIndex-1, rightPointerIndex = pivotIndex+1;
	while(leftPointerIndex >=numberOfSortedNodes || rightPointerIndex <= end){
		if(leftPointerIndex >=numberOfSortedNodes && isLessThanOrEqualTo(leftOfPivot->object,pivot->object)){
			leftOfPivot = leftOfPivot -> prev;
			leftPointerIndex --;
			continue;
		}
		if(rightPointerIndex <= end && isLessThanOrEqualTo(pivot->object,rightOfPivot->object)){
			rightOfPivot = rightOfPivot -> next;
			rightPointerIndex ++;
			continue;
		}
		// Exchange their positions....
		if(!(rightPointerIndex <= end)){
			pivotIndex--;
			TrainInfoPerStation* temp = pivot ->prev ->object;
			pivot->prev->object = leftOfPivot->object;
			leftOfPivot->object = temp;
			temp = pivot ->prev ->object;
			pivot->prev->object = pivot -> object;
			pivot->object = temp;
			pivot = pivot -> prev;
			leftPointerIndex--;
			leftOfPivot = leftOfPivot->prev;
			continue;
		}
		if(!(leftPointerIndex >= numberOfSortedNodes)){
			pivotIndex++;
			TrainInfoPerStation* temp = pivot ->next ->object;
			pivot->next->object = rightOfPivot->object;
			rightOfPivot->object = temp;
			temp = pivot ->next ->object;
			pivot->next->object = pivot -> object;
			pivot->object = temp;
			pivot = pivot -> next;
			rightPointerIndex++;
			rightOfPivot = rightOfPivot->next;
			continue;
		}
		TrainInfoPerStation* temp = rightOfPivot->object;
		rightOfPivot->object = leftOfPivot->object;
		leftOfPivot->object = temp;
		leftOfPivot = leftOfPivot -> prev;
		leftPointerIndex --;
		continue;
	}

	prevPivotIndex = pivotIndex;
	Quicksort(stnInfoList);
	numberOfSortedNodes++;
	prevPivotIndex = end + 1;
	Quicksort(stnInfoList);
	// Decrement recursion level before leaving the function
	recursionLevel--;
	return;
}
// {
// 	int numNodes = 0;
// 	listOfObjects<TrainInfoPerStation*>* curr = stnInfoList;
// 	while(curr){
// 		curr = curr->next;
// 		numNodes ++;
// 	}
// 	QuicksortSimple(stnInfoList,0,numNodes-1);
// }

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
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
	// overall.	So you MUST NOT allocate space in each recursive call.
	//
	// A variable/array defined using static is not created afresh in
	// each recursive call.	Instead, a single copy of it is maintained
	// across all recursions.
	static vector<listOfObjects<TrainInfoPerStation*>*> storedAddresses; // This will store the address for Every Kth node.
	static int originalNumberOfNodes;
	static int leftMostUnsortedNode;
	if (recursionLevel == 0) {
		// Find length of the list stnInfoList, if needed.
		// Allocate additional space for upto n/K TrainInfoPerStation objects
		// if needed.
		// Do other things that you may want to do only at the beginning
		// as a pre-processing step.
		originalNumberOfNodes = 0;
		listOfObjects<TrainInfoPerStation*>* curr = stnInfoList;
		storedAddresses.clear();
		while(curr){
			if( originalNumberOfNodes%K == 0 ) {
				storedAddresses.push_back(curr);
			}
			originalNumberOfNodes++;
			curr = curr->next;
		}
	}
	// static variable and recursionLevel 0 works completed
	if(!( start<end )){ // If single elements comes.
		recursionLevel--;
		return;
	}
	
	// Put your code for the core of QuicksortSimple here
	srand(time(0));
	int pivotIndex = rand()%(end - start) + start;
	listOfObjects<TrainInfoPerStation*>* pivot;
	int shift = pivotIndex % K;
	pivot = storedAddresses[pivotIndex/K];
	while(shift--){
		pivot = pivot -> next;
	}
	// Rearranging terms
	listOfObjects<TrainInfoPerStation*>* leftOfPivot = pivot -> prev, *rightOfPivot = pivot -> next;
	int leftPointerIndex = pivotIndex-1, rightPointerIndex = pivotIndex+1;
	while(leftPointerIndex >=start || rightPointerIndex <= end){
		if(leftPointerIndex >=start && isLessThanOrEqualTo(leftOfPivot->object,pivot->object)){
			leftOfPivot = leftOfPivot -> prev;
			leftPointerIndex --;
			continue;
		}
		if(rightPointerIndex <= end && isLessThanOrEqualTo(pivot->object,rightOfPivot->object)){
			rightOfPivot = rightOfPivot -> next;
			rightPointerIndex ++;
			continue;
		}
		// Exchange their positions....
		if(!(rightPointerIndex <= end)){
			pivotIndex--;
			TrainInfoPerStation* temp = pivot ->prev ->object;
			pivot->prev->object = leftOfPivot->object;
			leftOfPivot->object = temp;
			temp = pivot ->prev ->object;
			pivot->prev->object = pivot -> object;
			pivot->object = temp;
			pivot = pivot -> prev;
			leftPointerIndex--;
			leftOfPivot = leftOfPivot->prev;
			continue;
		}
		if(!(leftPointerIndex >= start)){
			pivotIndex++;
			TrainInfoPerStation* temp = pivot ->next ->object;
			pivot->next->object = rightOfPivot->object;
			rightOfPivot->object = temp;
			temp = pivot ->next ->object;
			pivot->next->object = pivot -> object;
			pivot->object = temp;
			pivot = pivot -> next;
			rightPointerIndex++;
			rightOfPivot = rightOfPivot->next;
			continue;
		}
		TrainInfoPerStation* temp = rightOfPivot->object;
		rightOfPivot->object = leftOfPivot->object;
		leftOfPivot->object = temp;
		leftOfPivot = leftOfPivot -> prev;
		leftPointerIndex --;
		continue;
	}

	QuicksortSimple(stnInfoList, start, pivotIndex-1);
	QuicksortSimple(stnInfoList, pivotIndex + 1, end);
	// Decrement recursion level before leaving the function
	recursionLevel--;
	return;
}

#endif
