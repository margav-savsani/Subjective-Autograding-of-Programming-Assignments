#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree :: SorterTree(int choice, int l){
	choice = 0;
	l = 0;
	array = array;
}

void SorterTree :: Quicksort(Journey* arr, int start, int finish){
	// Call appropriate pivot function based on choice
	// Split into 2 parts based on pivot choice
	// Recursively keep sorting
	int pivot;
	switch(choice){
		case 1 :
        	pivot = choose_one(array, start, finish);
        	break;
    	case 2 :
			pivot = choose_two(array, start, finish);
			break;
    	case 3 :
			pivot = choose_three(array, start, finish);
			break;
		case 4 :
        	pivot = choose_four(array, start, finish);
        	break;
	}
	Quicksort(arr, start, pivot);
	Quicksort(arr, pivot+1, finish);
	
}

void SorterTree :: QuicksortWithBSTInsert(Journey* arr, int start, int finish){
	// Call appropriate pivot function based on choice
	// Split into 2 parts based on pivot choice
	// Recursively keep sorting
	// Insert chosen pivot into the tree appropriately
	int pivot;
	switch(choice){
		case 1 :
        	pivot = choose_one(array, start, finish);
        	break;
    	case 2 :
			pivot = choose_two(array, start, finish);
			break;
    	case 3 :
			pivot = choose_three(array, start, finish);
			break;
		case 4 :
        	pivot = choose_four(array, start, finish);
        	break;
	}
	insertPivot(array[pivot].getJourneyCode(), array[pivot].getPrice());
	QuicksortWithBSTInsert(arr, start, pivot);
	QuicksortWithBSTInsert(arr, pivot+1, finish);
}

bool SorterTree :: printArray(){
	for(int i=0; i<l; i++){
		std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
	}
}

bool SorterTree :: insertPivot(int JourneyCode, int price){
	return insert(JourneyCode, price);
}

BST* SorterTree :: getTree(){
	return tree;
}
