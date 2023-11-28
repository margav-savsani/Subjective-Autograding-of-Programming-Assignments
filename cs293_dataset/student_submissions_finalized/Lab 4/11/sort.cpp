#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{    
    Journey* pivot = array; 
    //  switch (choice)
    //  {
    //  case 1 : 
    //     pivot = choose_one(array,start,finish); 
    //     break;
    //  case 2: 
    //     pivot = choose_two(array,start,finish); 
    //     break;
    //  case 3 : 
    //     pivot = choose_three(array,start,finish); 
    //     break;
    //  case 4 : 
    //     pivot = choose_four(array,start,finish) ;  
    //     break;     
    //  default: 
    //     return false ; 
    //     break;
    //  }

    int i = start - 1 , j = finish + 1 , p ;

    while (true) {
        while ()
        do {
            i++;
            comparisons++; 
        } while (array[i] < *pivot )  ;

        do {
            j--;
            comparisons++; 
        } while (*pivot < array[j] );

        if (i >= j) { 
            p = j ; 
            break ; 
        }
        swap(array[i], array[j]);
    }

     if ( start < finish ) {
        Quicksort(start,p-1) ; 
        Quicksort(p + 1,finish) ; 
     }
     return true ; 
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
// {
//     switch (choice)
//      {
//      case 1 : 
//         partition = choose_one(tree,start,finish); 
//         break;
//      case 2: 
//         partition = choose_two(tree,start,finish); 
//         break;
//      case 3 : 
//         partition = choose_three(tree,start,finish); 
//         break;
//      case 4 : 
//         partition = choose_four(tree,start,finish) ;  
//         break;     
//      default: 
//         return false ; 
//         break;
//      }
//      if ( start < finish ) {
//         Quicksort(start,partition-1) ; 
//         Quicksort(partition + 1,finish) ; 
//      }
//     // Call appropriate pivot function based on choice
//     // Split into 2 parts based on pivot choice
//     // Recursively keep sorting
//     // Insert chosen pivot into the tree appropriately

}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
