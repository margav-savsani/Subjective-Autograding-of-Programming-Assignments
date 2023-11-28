#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp



bool SorterTree::Quicksort(int start, int finish){
     
      if(start<finish){
          int cut = partition(array,start,finish);
          
          
          Quicksort(start,cut);
          Quicksort(cut+1,finish);
      }  
      
      return true;
  }



bool SorterTree::QuicksortWithBSTInsert(int start, int finish);


bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
