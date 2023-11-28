#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
void partition(int start,int finish)
{
 int pivot = array[finish]; // pivot 
    int i = (start - 1); // Index of smaller element and indicates the right position of pivot found so far
  
    for (int j = start; j <= finish - 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (array[j] < pivot) 
        { 
            i++; // increment index of smaller element 
            swap(&array[i], &array[j]); 
        } 
    } 
    swap(&array[i + 1], &array[high]); 
    return (i + 1); 
}
bool SorterTree::Quicksort(int start, int finish)
{

  int pivot = array[finish]; // pivot 
    int i = (start - 1); // Index of smaller element and indicates the right position of pivot found so far
  
    for (int j = start; j <= finish - 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (array[j] < pivot) 
        { 
            i++; // increment index of smaller element 
            swap(&array[i], &array[j]); 
        } 
    } 
    swap(&array[i + 1], &array[finish]); 
    return (i + 1); 


     if (start < finish) 
    { 
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition(start,finish); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort( start, pi - 1); 
        quickSort( pi + 1, high); 
    } 
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
