#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
	this->l = l;
	this->choice = choice;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start >= finish)
		return true;
	Journey* pivot;
	if(choice >=1 && choice<=4){
		return false;
	}	
	if(choice == 1){
		pivot = choose_one(array, start, finish);
	}
	else if(choice == 2){
		pivot = choose_two(array, start, finish);
	}
	else if(choice == 3){
		pivot = choose_three(array, start, finish);
	}
	else if(choice == 4){
		pivot = choose_four(array, start, finish);
	}
	int s = start-1;
	int f = finish+1;
	
	while(true){
		do{
			s++;
		}while(array[s]<*(pivot) && s<=f);
		
		do{
			f--;
		}while(array[s]>*(pivot) && f>=s);
		
		if(f>s){
			int temp;
			temp = array[s];
			array[s] = array[f];
			array[f]= temp;
		}else{
			break;
		}
	}
	
	SorterTree(array, start, f);
	SorterTree(array, f+1, finish);
	return true;
    
    
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
