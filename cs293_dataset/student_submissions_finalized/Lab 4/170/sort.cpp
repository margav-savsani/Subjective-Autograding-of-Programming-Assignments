#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int SorterTree::partition(Journey * A,p,r){
	x = A[r];
	i = p-1;
	j = r+1;
	while(1){
		while(A[j]<=x) j=j-1;
		while(A[i]>=x) i=i+1;
		if(i<j) {
			Journey a = A[i];
			A[i] = A[j];
			A[j] = a;
		}
		else return j;
	}
}

SorterTree:: SorterTree(int c, int l){
	choice = c;
	Journey * A = A[l];
}

bool quicksort(Journey * J, int p, int r){
	p = start;
	r = finish;
	if ( p < r ){
    		q = partition(J,p,r);
    		quicksort(J,p,r);
    		quicksort(J,q+1,r);
	}
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    quicksort(A,start,finish);
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
