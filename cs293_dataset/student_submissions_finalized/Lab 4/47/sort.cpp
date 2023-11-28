#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

using namespace std;
int partition(Journey* arr, int start, int r){

	Journey* c = new Journey();
	c = choose_two(arr,start,finish);
	int i = start-1;
	int j = finish+1;
	while(true){
	
		while( arr[--j]>*c || arr[j]==*c ){}
		while( arr[++i]<*c || arr[i]==*c ){}
		if( i<j){
			
			Journey y;
			y = arr[i];
			arr[i] = arr[j];
			arr[j] = y;
		}
	}
	return j;
}
						
	
	
bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if( start < finish ){
    
   	 int k = partition(array, start, finish);
    	 Quicksort(start,k);
    	 Quicksort(k+1,finish);
    }
    
    return true;
    
    
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    
    
      int k = partition(array, start, finish);
      tree->root = TreeNode(array[k]);
      (tree->root)->left = QuicksortWithBSTInsert(start,finish-1);
      (tree->root)->right = QuicksortWithBSTInsert(finish+1, finish);
      
  
}

bool SorterTree:: insertPivot(int JourneyCode, int price){

	return tree.insert(JourneyCode, price);
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

