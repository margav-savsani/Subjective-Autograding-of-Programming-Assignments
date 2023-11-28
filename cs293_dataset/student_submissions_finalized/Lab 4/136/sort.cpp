#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
int SorterTree::partition(Journey *array,int s,int e){
         
Journey j=array[choice];
   int  i = s, j=e;
     
    while(true){
    
        while(array[j]>x){ j=j-1; }
        while(array[i]<x){ i=i+1; }
        if(i<j){
            Journey a = array[i];
            array[i] = array[j];
            array[j] = a;  
        }
        
        else { return j;}
    }  
         
}

bool SorterTree::Quicksort(int start, int finish){
     
      if(start<finish){
          int cut = partition(array,start,finish);
          
          
          Quicksort(start,cut);
          Quicksort(cut+1,finish);
          return true;
      }
      return false;
}
bool SorterTree::Quicksort(int start, int finish)
{
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
