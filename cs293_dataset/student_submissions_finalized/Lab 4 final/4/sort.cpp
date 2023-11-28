#include "sort.h"
#include <iostream>

SorterTree::SorterTree(int choice,int l){
	this -> choice = choice;
	this -> l = l;
	tree = new BST();
}

void swap(Journey &x1, Journey &x2){
	Journey temp = x1;
	x1 = x2;
	x2 = temp;
}

// Code up the functions defined in sort.cpp
void SorterTree::add( int length){
	array = new Journey[length];
	for(int i=0;i<length;i++){
		int x,y;
		cin>>x>>y;
		array[i].getJourneyCode()=x;
		array[i].getPrice()=y;
		}	
	}
	
	
int SorterTree::Partition(Journey pivot,int start,int finish)
{
 
    // Journey *pivot;
	// if (choice == 1 ){
	// 	pivot = choose_one(array,start,finish);
	// }
	// else if (choice == 2){
	// 	pivot = choose_two(array,start,finish);
	// }
	// else if ( choice == 3){
	// 	pivot = choose_three(array,start,finish);
	// }
 
    /*int count = 0;
    for (int i = start + 1; i <= finish; i++) {
        if (array[i] <= array[start])
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;*/
 
    // Sorting left and right parts of the pivot element
    int begin = start, end = finish;
 
    while (true){ 
		while (array[end] > pivot) {
            end=end-1;comparisons++;
        }
		
		while (array[begin] <  pivot) {
            begin= begin+1;comparisons++;
        }
		comparisons+=2;
        if (begin < end) {
            swap(array[begin], array[end]);
			//printArray();
			//cout << endl;
        }
		else 
		 if(begin==end) return end-1;
		 return end;
    }
}

bool SorterTree::Quicksort(int start, int finish){
	// base case
	Journey *pivot;
	if (choice == 1 ){
	 	pivot = choose_one(array,start,finish);
	}
	else if (choice == 2){
	 	pivot = choose_two(array,start,finish);
	}
	else if ( choice == 3){
	 	pivot = choose_three(array,start,finish);
	}

    if (start < finish){
		int p = Partition(*pivot, start,finish); // partitioning the array
		
		Quicksort(start, p );// Sorting the left part
		// Sorting the right part
		Quicksort(p+1,finish);
	}
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
	
	
    if (start < finish){
		Journey *pivot;
		if (choice == 1 ){
			pivot = choose_one(array,start,finish);
		}
		else if (choice == 2){
			pivot = choose_two(array,start,finish);
		}
		else if ( choice == 3){
			pivot = choose_three(array,start,finish);
		}
		//cout << pivot->getJourneyCode()<<endl;
		insertPivot(pivot->getJourneyCode(), pivot->getPrice());
		int p = Partition(*pivot, start,finish); // partitioning the array
		if (p == finish) QuicksortWithBSTInsert(start,p-1);
		else QuicksortWithBSTInsert(start, p );// Sorting the left part
		if (p+1==start) QuicksortWithBSTInsert(start+1,finish);// Sorting the right part
		else QuicksortWithBSTInsert(p+1,finish);
	}	
	
	
	return false;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::insertPivot(int JourneyCode, int price) {
	tree->insert(JourneyCode,price);
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
	tree->printBST("");
    return true;
}
