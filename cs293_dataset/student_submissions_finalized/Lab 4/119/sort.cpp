#include "sort.h"
#include <iostream>

// my stuff
// #include "choose.h"

// Code up the functions defined in sort.cpp

//

SorterTree::SorterTree(int choice, int l){
    this->choice=choice; this->l = l;
    array = new Journey[l];
}

//

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    // TRIVIAL CASE
    if (start > finish || start < 0 || finish >= l) return false;
    if (start==finish) return true;

    if (finish-start==1){
        if (array[start].getJourneyCode() > array[finish].getJourneyCode()){
            Journey *t = new Journey; 
            *t = array[start];
            array[start] = array[finish];
            array[finish] = *t;
            delete t;
        }
        return true;
    }

    // trying out with FUNCTION ONE

    // ex. array = [22,31,2,1,3,4,6,5,7,95,101]
    //     index = [ 0, 1,2,3,4,5,6,7,8, 9, 10]

    Journey *pivot;                                                 // pointer to the Journey entry whose JourneyCode is pivot

    if (choice == 1){ pivot = choose_one(array, start, finish); }
    if (choice == 2){ pivot = choose_two(array, start, finish); }
    if (choice == 3){ pivot = choose_three(array, start, finish); }
    if (choice == 4){ pivot = choose_four(array, start, finish); }

    int pivotIndex = pivot-&array[0];                               // pivotIndex = 4

    // say pivot = 3 (at index 4)
    // say start = 2, finish = 8 (indexes, not positions)
    // number of elements to deal with = 7

    Journey *left = new Journey[finish-start+1];                      // partitions of size (finish-start+1) = 7
    Journey *right = new Journey[finish-start+1];                     // partitions of size (finish-start+1) = 7
    int counter_left=0, counter_right=0;

    for(int i=start; i<=finish; i++){                               
        if (array[i].getJourneyCode() < pivot->getJourneyCode()){
            left[counter_left]=array[i];
            counter_left++;
        }
        else {
            right[counter_right]=array[i];
            counter_right++;
        }
    }

    // left = [2,1]
    // counter_left = 2
    // right = [4,6,5,7]
    // counter_right = 4
    // counter_left + counter_right + 1 = finish-start + 1 = total numbers in consideration

    // now modifying the original array

    for(int i=start; i<=finish; i++){                               // i from 2 to 8
        if(i < start+counter_left){                                         
            array[i]=left[i-start-counter_left];                    // denoting indexes, array[2,3] = left[0,1]
        }
                                                                    // denoting indexes, array[4] = pivot
        else if(i > start+counter_left){
            array[i]=right[i-start-counter_left-1];                 // denoting indexes, array[5,6,7,8] = right[0,1,2,3]
        }
    } 

    // new array = [22,31,2,1,3,4,6,5,7,95,101]
    //     index = [ 0, 1,2,3,4,5,6,7,8, 9, 10]

    // now doing recursive call

    Quicksort(start, pivotIndex-1);
    Quicksort(pivotIndex+1,finish);

    return true;

    delete left, right;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    
    // my stuff
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }

    // my stuff
    return true;
}

SorterTree::~SorterTree(){
    delete array;
    // delete tree;
}