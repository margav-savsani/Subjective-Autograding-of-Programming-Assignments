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

void Expand(){

}

void Quicksort(listOfObjects<TrainInfoPerStation *> *&stnInfoList)
{
	// IDEA :
	// We will split array of N elements into k equal parts by creating an array of pointers of size N/k 
	// then choose a random pointer from N/k pointers and traverse that section ok k elements to chhose a random element as pivot
	// then we will split linked list into 2 parts
	// we will again choose a random element in those 2 parts by same method
}
