#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

void SorterTree::Quicksort(int start, int finish)
{
	if (start < finish){
	x = choose_three(array, start, finish);
	//int x = atoi(argv[2]);
	int i = start - 1, j = finish + 1;
	while (1){
		while ( array[j] > array[x] )
			j = j-1;
		while ( array[i] < array[x] )
			i = i+1;
		if (i < j){
			Journey *f;
			f = array[i];
			array[i] = array[j];
			array[j] = f;
		}
		else int k = j;
		QuickSort(start, k-1);
		QuickSort(k, finish);
	} 
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
} 

void SorterTree::QuicksortWithBSTInsert(TreeNode *root, int start, int finish)
{	
	if (start < finish){
        x = choose_three(array, start, finish);
	tree->root = array[x];
        int i = start - 1, j = finish + 1;
        while (1){
                while ( array[j] > array[x] )
                        j = j-1;
                while ( array[i] < array[x] )
                        i = i+1;
                if (i < j){
                        Journey *f;
                        f = array[i];
                        array[i] = array[j];
                        array[j] = f;
                }
		else int k = j;
		QuicksortWithBSTInsert((tree->root)->left,start, k-1);
		QuicksortWithBSTInsert((tree->root)->right,k,finish);
		
		
	}	
	
	/*Quicksort( start, finish );
	for (int i=start; i<=finish; i++){
		insert(array[i]->JourneyCode, array[i]->price);
	}*/
	
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}	
