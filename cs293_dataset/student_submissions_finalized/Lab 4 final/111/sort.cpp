#include "sort.h"
#include <iostream>
#include<string.h>
#include "choose.h"
// Code up the functions defined in sort.cpp
int SorterTree::partition(string array,int start,int finish){

 int pivot = array[start];
 
    int count = 0;
    for (int i = start + 1; i <= finish; i++) {
        if (array[i] <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(array[pivotIndex], array[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = finish;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (array[i] <= pivot) {
            i++;
        }
 
        while (array[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(array[i++], array[j--]);
        }
    }
 
    return pivotIndex;
}
 
bool SorterTree::Quicksort(int start, int finish)
{   
    int pivot;
    if(choice==1) pivot=choose_one(Journey* x, int start, int finish);
    if(choice==2) pivot=choose_two(Journey* x, int start, int finish);
    if(choice==3) pivot=choose_three(Journey* x, int start, int finish);
    if(choice==4) pivot=choose_four(Journey* x, int start, int finish);
     if (start< finish) 
    { 

        pivot  = partition(array,start,finish); 
  
        QuickSort(start, pivot  - 1);  //left partition
        QuickSort( pivot  + 1, finish); //right partition
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
