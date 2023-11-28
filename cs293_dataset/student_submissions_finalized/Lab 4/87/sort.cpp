#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
	if (start < finish){
	int x = array[finish]->JourneyCode;
	int i = start - 1, j = finish + 1;
	while (1){
		while ( array[j]->JourneyCode > x )
			j = j-1;
		while ( array[j]->JourneyCode < x )
			i = i+1;
		if (i < j){
			Journey *x;
			x = array[i];
			array[i] = array[j];
			array[j] = array[i];
		}
		else int p = atoi(argv[2]);
		QuickSort(p, finish);
		QuickSort(start, p-1); 
	} 
	return true;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
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
