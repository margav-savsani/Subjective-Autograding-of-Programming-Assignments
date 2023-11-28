#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
bool SorterTree::partition(Journey* A, int start, int finish){
	x=A(finish);
	i=start-1;
	j=finish+1;
	while(true){
		while(A[j]<x){j--;}
		while(A[i]<x){i++;}
		if(i<j){
			Journey p=A[i];
			A[i]=A[j];
			A[j]=p;
		}
		else return j;
	}
}
void SorterTree::Quicksort(Journey* A, int start, int finish){
	// Call appropriate pivot function based on choice
	// Split into 2 parts based on pivot choice
	// Recursively keep sorting
	if(start<finish){
		int q=partition(A, start, finish);
		Quicksort(A, start, q);
		Quicksort(A, q+1, finish);
	}
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
