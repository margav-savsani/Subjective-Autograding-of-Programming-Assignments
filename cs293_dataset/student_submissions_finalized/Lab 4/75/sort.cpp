#include"sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int SorterTree::Partition(Journey* array, int p, int r){
    Journey x =  array[r]; // x is the pivot wrt which partition will be done
    int i = p-1;
    int j = r+1;

    while(true){
        while (x < array[j]){ // moving the right pointer to lower indices till it sees sorted array
            j--;
        }
        while (array[i] < x){ // moving the left pointer to higher indices till it sees sorted array
            i++;
        }
        if(i<j){
            Journey temp = array[i]; // exchanging the Journeys if they are not in correct order
            array[i] = array[j];
            array[j] = temp;
        }
        else{
            return j;
        }
    }
}
bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    int pivot = 0;
    if (start<finish){
        pivot = Partition(array, start, finish); // the pivot based on which array will be partitioned
        Quicksort(start, pivot);// recursively calling Quicksort to sort the first array
        Quicksort(pivot+1, finish);// recursively calling Quicksort to sort the second array
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
