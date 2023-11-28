#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
int SorterTree::Partition(int start, int finish, Journey* pivot)
{
	int refcode = pivot->JourneyCode;
	int refindex = start;
	for(int i=start; i<=finish; i++){
		if (array[i] < *pivot) refindex++;
	
	}
	Journey temp = array[refindex];
	array[refindex] = *pivot;
	*pivot = temp;
	
	return refindex;
	
}


void SorterTree::Quicksort(int start, int finish)
{   
    Journey* pivot;
    
    	pivot = &(array[(start+finish)/2]) ;
    //make choice of pivot:
    /*if(choice==1){
    	pivot = choose_one(array, start, finish);
    }else if (choice==2){
    	pivot = choose_two(array, start, finish);
    }else if (choice==3){
    	pivot = choose_three(array, start, finish);
    }else if (choice==4){
    	pivot = choose_four(array, start, finish);
    }else pivot = &(array[(start+finish)/2]);*/
    
    if (start<finish){
    	//Partitioning:
    	int newIndex = Partition(start, finish, pivot);
    	
    	//Recursive Sorting:
    	
    	Quicksort(start, newIndex-1);
    	Quicksort(start, newIndex+1);
    	
    }
    else return;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

int SorterTree :: addJourney(int index, Journey journey){
	array[index] = journey;
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
