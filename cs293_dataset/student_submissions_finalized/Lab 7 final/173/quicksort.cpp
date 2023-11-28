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

#include <time.h>

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

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  static int n =1;
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
  
  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
  static listOfObjects<TrainInfoPerStation *>** arr = new listOfObjects<TrainInfoPerStation *>* [(n/K)+1];
  
  // Put your code for the core of Quicksort here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;
  static int n =1;  
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
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    listOfObjects<TrainInfoPerStation *> *currList;
    currList = stnInfoList;
    while (currList->next != nullptr) {
    	n++;
			currList = currList->next;
		}
	}
  static listOfObjects<TrainInfoPerStation *>** A = new listOfObjects<TrainInfoPerStation *>* [(n/K)+1];
	
	A[0] = stnInfoList;
	for (int i=0; i<start; i++)                                       // This is for initializing A[0] = address of start_th node in the list 
		A[0]=A[0]->next;
		
	for (int i=0; i<(end-start+1)/K; i++) {
		A[i+1]=A[i];                                                    // Initializing array A(extra storage)
		for (int j=0; j<(end-start+1)/K; j++)
			A[i+1]=A[i]->next;
	}
	
  // Put your code for the core of QuicksortSimple here
	srand(time(0));
	int pivotIndex = start + (rand()%(end-start+1));
	int ind = (pivotIndex-start)/K;
	int rmdr = (pivotIndex-start)%K;

	listOfObjects<TrainInfoPerStation *> *pivotNode;
	pivotNode = A[ind];                                               
	for (int i=0; i<rmdr; i++)
		pivotNode = pivotNode->next;
	
	// pivotIndex=partition(stnInfoList, pivotNode, start, end);    // waste code
	
	listOfObjects<TrainInfoPerStation *> *currNode = stnInfoList, *sNode=stnInfoList; int day=0, day0=0; for(int i=0; i<7; i++) if(pivotNode->object->daysOfWeek[i]) day0=i;
	
	while (currNode != pivotNode) {
		cout << 1.1 << endl;
		for (int i=0; i<7; i++) if (currNode->object->daysOfWeek[i]) day=i;
		if (day<day0) currNode=currNode->next;
		else if (day==day0) { cout << 1.2 << endl;
			if(currNode->object->depTime < currNode->object->depTime) {cout << 1.3 << endl; currNode=currNode->next;}
			else {cout << 1.4 << endl;
				if (currNode->prev != nullptr) {currNode->prev->next=currNode->next;currNode->next->prev=currNode->prev;}
				else {currNode->next->prev = currNode->prev;}
					listOfObjects<TrainInfoPerStation *> *x = currNode->next;
					currNode->next=pivotNode->next;
					if(pivotNode->next != nullptr) pivotNode->next->prev = currNode;
					pivotNode->next = currNode;
					currNode->prev = pivotNode;
					pivotIndex--; currNode = x;
			}
		}
		else {cout << 1.5 << endl;
			if (currNode->prev != nullptr) {currNode->prev->next=currNode->next;currNode->next->prev=currNode->prev;}
			else {currNode->next->prev = currNode->prev;}
			listOfObjects<TrainInfoPerStation *> *x = currNode->next;
			currNode->next=pivotNode->next;
			
			if(pivotNode->next != nullptr) pivotNode->next->prev = currNode;
			pivotNode->next = currNode;
			currNode->prev = pivotNode;
			pivotIndex--; currNode = x;
		}
	} currNode = pivotNode->next;
	
	while (currNode != nullptr) {
		cout << 2.1 << endl;
		for (int i=0; i<7; i++) if (currNode->object->daysOfWeek[i]) {cout<<"2.1.1\n";day=i;}
		if (day>day0) currNode=currNode->next;
		else if (day==day0) { cout << 2.2 << endl;
			if(currNode->object->depTime > currNode->object->depTime) currNode=currNode->next;
			else { cout << 2.3 << endl;
				if (currNode->next != nullptr){currNode->prev->next = currNode->next; currNode->next->prev = currNode->prev;}
				else {currNode->prev->next = currNode->next;}
				listOfObjects<TrainInfoPerStation *> *x = currNode->next;
				currNode->prev=pivotNode->prev;
				if(pivotNode->prev != nullptr) pivotNode->prev->next = currNode;
				else {sNode = currNode;}
				pivotNode->prev = currNode;
				currNode->next = pivotNode;
				pivotIndex++; currNode = x;
			}
		}
		else { cout << 2.4 << endl;
			if (currNode->next != nullptr){currNode->prev->next = currNode->next; currNode->next->prev = currNode->prev;}
			else {currNode->prev->next = currNode->next;}
			listOfObjects<TrainInfoPerStation *> *x = currNode->next;
			currNode->prev=pivotNode->prev;
			if(pivotNode->prev != nullptr) pivotNode->prev->next = currNode;
			else {sNode = currNode;}
			pivotNode->prev = currNode;
			currNode->next = pivotNode;
			pivotIndex++; currNode = x;
		}
	} currNode = pivotNode->next;
	

	/* if (pivotIndex == 0)        // waste code
		QuicksortSimple(pivotNode->next, 1, end);
	else if (pivotIndex == end)    // waste code
		QuicksortSimple(stnInfoList, 0, end-1);
	else {                         // waste code
		QuicksortSimple(stnInfoList, 0, pivotIndex-1);
		QuicksortSimple(pivotNode->next, pivotIndex+1, end);
	}*/
	
	if (start < end) {
		// pivotIndex=partition(stnInfoList, pivotNode, start, end);
		QuicksortSimple(sNode, start, pivotIndex); cout << 3.1 << endl;
		QuicksortSimple(pivotNode->next, pivotIndex+1, end); cout << 3.2 << endl;
	}
	
	// Decrement recursion level before leaving the function
	recursionLevel--;
	return;
}

bool::isLessThan(listOfObjects<TrainInfoPerStation *> *x, listOfObjects<TrainInfoPerStation *> *y) {
	int xd, yd;
	for (int i=0; i<7; i++)
		if(x->object->daysOfWeek[i]) xd=i;	
	for (int i=0; i<7; i++)
		if(y->object->daysOfWeek[i]) yd=i;
	if (xd < yd) return true;
	if (xd==yd)
		return ((x->object->depTime)<(y->object->depTime));
	else return false;
}

#endif
