#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

using namespace std;
int partition(Journey array[], int low, int high, int choice, int size, int &comparisions) // creates the partition in the array using pivot
{
    int i = low;
    int j = high;
    int index;
    Journey* x ;
    if ( choice == 1 ) {
    
    	x = choose_one(array, low, high); 

   }
   else if( choice == 2 ){
   
   	x = choose_two(array, low, high);
   }
   
   else if ( choice == 3 ){
   
   	x = choose_three(array, low, high);
   }
   
   
   if ( x != nullptr){
   
   	for( int i=0; i<size; i++){

   		if ( *x == array[i] ){
   		
  			index = i;
  			break;
  		}
  	}
  }
  
  Journey k = array[i];
  array[i] = array[low];
  array[low] = k;
 
 
  Journey pivot = array[low];
  
  while (i < j)
    
  {
  
        while (!(pivot < array[i])){
            i++;
  	    comparisions++;
  	}          
        while (pivot < array[j]){
        
            j--;
	    comparisions++;
	}            
        if (i < j){
        
           Journey x = Journey(array[i].getJourneyCode(), array[i].getPrice());
           array[i] = Journey(array[j].getJourneyCode(), array[j].getPrice());
   	    array[j] =  Journey(x.getJourneyCode(), x.getPrice());
    	}
    	
  }
  
  
    Journey kx = Journey(array[low].getJourneyCode(), array[low].getPrice());
    array[low] = Journey(array[j].getJourneyCode(), array[j].getPrice());
    array[j] =  Journey(kx.getJourneyCode(), kx.getPrice());
    
    return j;
}

bool SorterTree::Quicksort(int start, int finish) // sort the array
{

	if ( start < finish )
    	{
    	
        int pivot = partition(array, start, finish, choice,l,comparisons);
        Quicksort(start, pivot - 1);
    	Quicksort(pivot + 1, finish);
    	
    	}
    	return true;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish) // Sort the array, with inserting it into the tree2
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    if ( start <= finish )
    	{
    	
        int pivot = partition(array, start, finish, choice,l,comparisons);
  
        tree->insert(array[pivot].getJourneyCode(), array[pivot].getPrice());
        QuicksortWithBSTInsert(start, pivot - 1);
    	QuicksortWithBSTInsert(pivot + 1, finish);
    	
    	}
    return true;
}

bool SorterTree::printArray() // print the array
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

bool SorterTree:: insertPivot(int JourneyCode, int price){ // insert the pivot into the array and tree

	for( int i=0; i<l; i++){
	
		if ( array[i].getJourneyCode()==JourneyCode && array[i].getPrice()==price){
		
			return false;
		}
	}

	array[l] = Journey( JourneyCode, price);
	l++;
	delete tree;
	tree = new BST();
	QuicksortWithBSTInsert(0, l-1);	
	return true;
}

