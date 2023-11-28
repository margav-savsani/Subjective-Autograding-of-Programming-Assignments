#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int piv, int len) { choice = piv; l = len; }

bool SorterTree::Quicksort(int start, int finish)
{
    // ensure start <= finish, start >= 0 and finish <= N-1
    if(start<=finish && start>=0 && finish<l) {
    	Journey *pivot, *A, *B ; 
		// Call appropriate pivot function based on choice
		if (choice == 1) { 
			pivot1(array) = choose_one(array, start, finish);
		}
		else if (choice == 2) { 
			pivot2(array) = choose_two(array, start, finish);
		}
		else if (choice == 3) { 
			pivot3(array) = choose_three(array, start, finish);
		}
		else if (choice == 4) { 
			pivot4(array) = choose_four(array, start, finish);
		}
		//int len = sizeof(pivot)/sizeof(pivot[0]);
		int i = 0;
		int a = 0;
		int b = 0;
    	// Split into 2 parts based on pivot choice
    	
			for (int j = start; j<=finish; j++) {
				if(array[j] < pivot) {
					A[a] = array[j]; 
					a++;
				}
				else {
					B[b] = array[j];
					b++;
				}
			}
    	
    	
    	// Recursively keep sorting
    	
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // ensure start <= finish, start >= 0 and finish <= N-1
    if(start<=finish && start>=0 && finish<l) { 
		// Call appropriate pivot function based on choice
		if (choice == 1) { 
			choose_one(Journey* x, start, finish);
		}
		if (choice == 2) { 
			choose_two(Journey* x, start, finish);
		}
		if (choice == 3) { 
			choose_three(Journey* x, start, finish);
		}
		if (choice == 4) { 
			choose_four(Journey* x, start, finish);
		}
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
