#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

void exchange(int* num1, int* num2) 
{ 
    int temp = *num1; 
    *num1 = *num2; 
    *num2 = t; 
} 
  

int partition (int data[], int start, int end) 
{ 
    int pivot = data[end]
    int i = (start - 1); 
  
    for (int j = start; j <= end - 1; j++) 
    { 

        if (data[j] < pivot) 
        { 
            i++; 
            exachange(&data[i], &data[j]); 
        } 
    } 
    exchange(&data[i + 1], &data[end]); 
    return (i + 1); 
} 

void Quick_Sort(int data[], int start, int end) 
{ 
    if (start < end) 
    { 
        int pi = partition(data, start, end); 
  
        Quick_Sort(data, start, pi - 1); 
        Quick_Sort(data, pi + 1, end); 
    } 
}

bool SorterTree::Quicksort(int start, int finish)
{

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    int* data;
    Quick_sort(data,start,finish)
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
