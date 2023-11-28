#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    this -> choice = choice;
    this -> l = l;
    array = new Journey[l*sizeof(Journey)];
    comparisons = 0;
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

template <typename T> void swap(T* a, T* b){
  T temp = *a;
  *a = *b;
  *b = temp;
}

template <typename T> void partition(T arr[], int low, int high,int pivot){
    T pivot_elem = arr[pivot];
    int i = low - 1;
    for (int j = low; j < high; j++){
        if (arr[j] <= pivot_elem){
            swap<T>(arr[++i],arr[j]);
        }
    }
    swap(arr[++i],arr[high]);
    return i;
}
