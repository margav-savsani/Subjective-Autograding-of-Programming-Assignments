#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int partition(int* arr, int start, int end){
    int pivot = arr[start];
    int count = 0;
    for (int i=start+1; i<= end; i++) {
        if (arr[i] <= pivot)count++;
    }
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
    while (i < pivotIndex && j > pivotIndex) {
        while (arr[i] <= pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
    return pivotIndex;
}

bool SorterTree::Quicksort(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    int i=0;
    if(choice==1){choose_one(array, start,finish);}
    else if(choice==2){choose_two(array,start,finish);}
    else if(choice==3){choose_three(array,start,finish);}
    else if(choice==4){choose_four(array,start,finish);}

    if (start<finish) {
        int p=partition(array, start, finish);
        QuickSort(array,start, p-1);  // Before p
        QuickSort(array, p+1,finish); // After p
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
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
