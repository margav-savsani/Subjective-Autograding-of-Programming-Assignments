#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

Journey* Partition(Journey* &array,int start,int finish){
	int x,i,j;
	x = array[start];
	i = finish - 1;
	j = start + 1;
	while true{
		while( array[j] <= x){
			j = j-1;
		}
		while( array[i] >= x){
			i = i+1;
		}
		if (i < j){
			swap( array[i], array[j] );
		}
		else{
			return j;
		}
	}
}

bool SorterTree::Quicksort(int start, int finish)
{	
	if( finish < start ){
		int q = Partition(array,start,finish);
		Quicksort( start , q);
		Quicksort(q+1 , finish);
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
