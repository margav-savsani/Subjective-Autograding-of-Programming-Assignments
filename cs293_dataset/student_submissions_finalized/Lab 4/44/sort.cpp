#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    Journey* arr = array;
    if (start < finish)  
    {  
        int pivot = arr[finish]; 
        int i = (start - 1);  
        for (int j = start; j <= finish - 1; j++)  
        {  
            if (arr[j] < pivot)  
            {  
                i++; 
                int t = arr[i];  
                arr[i] = arr[j];  
                arr[j] = t;   
            }  
        }  
        int t = arr[i+1];  
        arr[i+1] = arr[finish];  
        arr[finish] = t;  

        int pi = i+1;  
        QuickSort(start, pi - 1);  
        QuickSort(pi + 1, finish);  
    }  

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
