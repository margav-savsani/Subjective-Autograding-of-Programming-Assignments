#include "sort.h"
#include <iostream>
//#include <fstream>

// Code up the functions defined in sort.cpp

void swap(Journey * a, Journey *b){
    Journey temp = *a;
    *a = *b;
    *b = temp;
    return;
}

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    arr = new Journey[l];
    comparisons=0;
}

bool SorterTree::Quicksort(int start, int finish)
{   
    if(start >= finish){
        return false;
    }
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey* pivot;
    if(choice == 1){
        pivot = choose_one(arr,start,finish);
    }
    else if(choice == 2){
        pivot = choose_two(arr,start,finish);
    }
    else if(choice == 3){
        pivot = choose_three(arr,start,finish);
    }
    else if(choice == 4){
        pivot = choose_four(arr,start,finish);
    }

    int change = start - 1;
    for(int i = start; i < finish;i++){
        if(arr[i] < *pivot){
            change ++;
            swap(&arr[i] , &arr[change]);
        }
    } 
    swap (&arr[change + 1],pivot);
    change ++;
    Quicksort(start,change - 1);
    Quicksort(change+ 1,finish);
    return true;
}

/*bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}*/

void SorterTree::insertelem(int jc , int p , int i){
    Journey j(jc,p);
    arr[i] = j;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<arr[i].getJourneyCode()<<"\tJourney Price:"<<arr[i].getPrice()<<std::endl;
    }
    return true;
}
