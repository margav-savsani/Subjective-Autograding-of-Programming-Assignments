#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

BST* SorterTree::getTree(){ return tree; }

SorterTree::SorterTree(int choice, int l){
    this->choice=choice; this->l = l;
    array = new Journey[l];

    Journey *x;
    for(int i=0; i<l; i++){
        unsigned int c,p; cin >> c >> p;
        x = new Journey(c,p);
        array[i] = *x;
    }
    delete x;

    tree = new BST();
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    // TRIVIAL CASE
    if (start > finish || start < 0 || finish >= l) return false;
    if (start==finish) return true;
    if (finish-start==1){
        comparisons++;
        Journey *t = new Journey; 
        if (array[start].getJourneyCode() > array[finish].getJourneyCode()){
            *t = array[start];
            array[start] = array[finish];
            array[finish] = *t;
        }
        delete t;
        return true;
    }

    // GETTING PIVOT INDEX
    Journey *pivot;                                                         // pointer to the Journey entry whose JourneyCode is pivot
    if (choice == 1){ pivot = choose_one(array, start, finish); }
    if (choice == 2){ pivot = choose_two(array, start, finish); }
    if (choice == 3){ pivot = choose_three(array, start, finish); }
    
    int pivotIndex = pivot-&array[0];

    // CREATING BLANK PARTITIONS
    Journey *left = new Journey[finish-start+1];                            // partitions of size (finish-start+1) = 7
    Journey *right = new Journey[finish-start+1];                           // partitions of size (finish-start+1) = 7
    int counter_left=0, counter_right=0;

    // COPYING THE ELEMENTS TO THEIR RESPECTIVE PARTITIONS
    for(int i=start; i<=finish; i++){                                       // check in (start to end), except...    
        if (i==pivotIndex) continue;                                        // except pivotIndex
        comparisons++;
        if (array[i].getJourneyCode() < pivot->getJourneyCode()){
            left[counter_left]=array[i];
            counter_left++;
        }
        else {
            right[counter_right]=array[i];
            counter_right++;
        }
    }

    // NOW ADJUSTING THE PIVOT INDEX
    pivotIndex = start+counter_left;

    Journey *pivot_point = new Journey;                             // preventing overlap in the below for-loop
    *pivot_point = *pivot;

    // NOW MODIFYING THE ORIGINAL ARRAY
    for(int i=start; i<=finish; i++){                               // i from 2 to 8
        if(i < pivotIndex){                                         
            array[i]=left[i-start];                                 // denoting indexes, array[3] = left[0]
        }
        else if(i == pivotIndex) array[i] = *pivot_point;           // denoting indexes, array[4] = pivot
        else if(i > pivotIndex){
            array[i]=right[i-pivotIndex-1];                         // denoting indexes, array[5] = right[0]
        }
    } 

    // NOW DOING RECURSIVE CALL
    if (pivotIndex > start) Quicksort(start, pivotIndex-1);
    if (pivotIndex < finish) Quicksort(pivotIndex+1,finish);

    delete left, right, pivot, pivot_point;
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    // TRIVIAL CASE
    if (start > finish || start < 0 || finish >= l) return false;
    if (start==finish) {
        insertPivot(array[start].getJourneyCode(),array[start].getPrice());
        return true;
    }
    if (finish-start==1){
        comparisons++;
        Journey *t = new Journey; 
        if (array[start].getJourneyCode() > array[finish].getJourneyCode()){
            *t = array[start];
            array[start] = array[finish];
            array[finish] = *t;
        }
        insertPivot(array[start].getJourneyCode(),array[start].getPrice());
        insertPivot(array[finish].getJourneyCode(),array[finish].getPrice());
        delete t;
        return true;
    }

    // GETTING PIVOT INDEX
    Journey *pivot;                                                         // pointer to the Journey entry whose JourneyCode is pivot
    if (choice == 1){ pivot = choose_one(array, start, finish); }
    if (choice == 2){ pivot = choose_two(array, start, finish); }
    if (choice == 3){ pivot = choose_three(array, start, finish); }
    
    int pivotIndex = pivot-&array[0];

    // CREATING BLANK PARTITIONS
    Journey *left = new Journey[finish-start+1];                            // partitions of size (finish-start+1) = 7
    Journey *right = new Journey[finish-start+1];                           // partitions of size (finish-start+1) = 7
    int counter_left=0, counter_right=0;

    // COPYING THE ELEMENTS TO THEIR RESPECTIVE PARTITIONS
    for(int i=start; i<=finish; i++){                                       // check in (start to end), except...    
        if (i==pivotIndex) continue;                                        // except pivotIndex
        comparisons++;
        if (array[i].getJourneyCode() < pivot->getJourneyCode()){
            left[counter_left]=array[i];
            counter_left++;
        }
        else {
            right[counter_right]=array[i];
            counter_right++;
        }
    }

    // NOW ADJUSTING THE PIVOT INDEX
    pivotIndex = start+counter_left;

    Journey *pivot_point = new Journey;                             // preventing overlap in the below for-loop
    *pivot_point = *pivot;

    // NOW MODIFYING THE ORIGINAL ARRAY
    for(int i=start; i<=finish; i++){                               // i from 2 to 8
        if(i < pivotIndex){                                         
            array[i]=left[i-start];                                 // denoting indexes, array[3] = left[0]
        }
        else if(i == pivotIndex) array[i] = *pivot_point;           // denoting indexes, array[4] = pivot
        else if(i > pivotIndex){
            array[i]=right[i-pivotIndex-1];                         // denoting indexes, array[5] = right[0]
        }
    } 

    // NOW INSERTING PIVOT INTO BST
    insertPivot(array[pivotIndex].getJourneyCode(),array[pivotIndex].getPrice());

    // NOW DOING RECURSIVE CALL
    if (pivotIndex > start) QuicksortWithBSTInsert(start, pivotIndex-1);
    if (pivotIndex < finish) QuicksortWithBSTInsert(pivotIndex+1,finish);

    delete left, right, pivot, pivot_point;
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    tree->insert(JourneyCode,price);
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
