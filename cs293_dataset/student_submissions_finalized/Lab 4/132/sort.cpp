#include "sort.h"
#include <iostream>
#include<stdlib.h>


// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{   
if (l < r)
    {
        int pi = partition(array, l, r);
        Quicksort(array, l, pi - 1);
        Quicksort(array, pi + 1, r);
    }

//     void swap(int arr[], int i, int j)
// {
//     int temp = arr[i];
//     arr[i] = arr[j];
//     arr[j] = temp;
// }
// int partition(int arr[], int l, int r)
// {
//     int pivot = arr[r];
//     int i = l - 1;
//     for (int j = l; j < r; j++)
//     {
//         if (arr[j] < pivot)
//         {
//             i++;
//             swap(arr, i, j);
//         }
//     }
//     swap(arr, i + 1, r);
//     return i + 1;
// }

//  void QuickSort(int arr[], int l, int r)
// {
    
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
