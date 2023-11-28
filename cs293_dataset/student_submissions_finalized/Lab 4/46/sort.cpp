#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::SorterTree(int choice, int l) {
    this->choice=choice;
    this->l=l;
    array=new Journey();
}

int partition(Journey* arr, int start, int finish) {
    Journey* pivot;
    switch(choice) {
        case 1:
            pivot=choose_one(arr,start,finish);
            break;
        case 2:
            pivot=choose_two(arr,start,finish);
            break;
        case 3:
            pivot=choose_three(arr,start,finish);
            break;
        case 4:
            pivot=choose_four(arr,start,finish);
            break;
    }
    QuicksortWithBSTInsert()
    int i=start-1;
    for(int j=start; j<=finish; j++) {
        if(*arr[j] < *pivot) {
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[finish]);
    return i+1;
}

bool SorterTree::Quicksort(int start, int finish)
{
    if(start>finish) {
        return false;
    }
    
    if(start < finish) {
        int part = partition(array,start,finish);
        Quicksort(array,start,part-1);
        Quicksort(array,part+1,finish);
    }
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    return true;
}

void SortWithTree(int )

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

BST* SorterTree::getTree() {
    return tree;
}
SorterTree::~SorterTree() {
    delete tree;
    delete array;
}
