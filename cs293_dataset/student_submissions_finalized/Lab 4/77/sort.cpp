#include "sort.h"
#include <iostream>
// Code up the functions defined in sort.cpp

void SorterTree::swap(Journey a, Journey b)
{
    Journey t=a; // ....overload assignment op in Journey
    a = b;
    b = t;
}

SorterTree::SorterTree(int choice, int l){
    int i=0;
    int code,val;
    choice=choice;
    while (i != l){
        cin>>code>>val;
        array[i]= Journey(code,val);
        i++;
    }
}

int SorterTree::partition(int start, int finish){
	Journey pivot = array[finish];
	int i = (start - 1);
	for (int j = start; j <= finish - 1; j++)
	{
		// If current element is smaller
		// than or equal to pivot
		if (array[j] < pivot) {
			// increment index of
			// smaller element
			i++;
			swap(array[i], array[j]);
		}
	}
	swap(array[i + 1], array[finish]);
	return (i + 1);


    //return(); 
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey *pivot = choose_one( array,start,finish);
    int pvtIdx = pivot - array;
    swap([pivot0],array[finish]);
    if(start<finish){
        
        int pi = partition(start, finish);
		// Separately sort elements before
		// partition and after partition
		Quicksort(start, pi - 1);
		Quicksort(pi + 1, finish);
	}

    
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    return false;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
