#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

// partitioning function to quicksort. 
// p = end of array , r = start of array

// assumes that the tree is blank, i.e. space allocated on the heap

SorterTree::SorterTree(Journey* A, int l) {
    this->l = l;
    this->array = new Journey[l];
    this->array = A;
}

// assumes array is already present
SorterTree::SorterTree(int choice, int l) {
    this->l = l;
    this->choice=choice;
}

int Partition(Journey* A, int p, int r) {
    
    Journey x = A[r];
    int i = p-1;
    int j = r+1;

    while (true) {
        while (x < A[j]){ j = j - 1;}
        while (A[i] < x){ i = i + 1;}

        if (i<j){
            Journey temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
        else {
            return j;
        }
    }
}

void quicksort(Journey* A, int p, int r) {
    if (p<r){
        int q = Partition(A, p, r);
        quicksort(A, p, q);
        quicksort(A, q+1, r);
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // assumption, pivot is the last element 
    // Choose pivot and make it the last element 
    Journey pivot;
    if (choice == 1) {pivot = *choose_one(array, start, finish);}
    else if (choice == 2) {pivot = *choose_two(array, start, finish);}
    else if (choice == 3) {pivot = *choose_three(array, start, finish);}
    else if (choice == 4) {pivot = *choose_four(array, start, finish);}

    bool shift = false;
    for (int i=0; i<l-1; i++){
        if (array[i] == pivot){
            // once pivot is found, empty that space and shift all the remaining elements backward. 
            shift = true;
        }
        if (shift == true) {
            array[i] = array[i+1];
        }
    }
    // putting pivot as the final element. 
    array[l-1] = pivot;

    quicksort(array, start, finish);

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // calling the appropriate pivot based on choice

    Journey pivot;
    if (choice == 1) {pivot = *choose_one(array, start, finish);}
    else if (choice == 2) {pivot = *choose_two(array, start, finish);}
    else if (choice == 3) {pivot = *choose_three(array, start, finish);}
    else if (choice == 4) {pivot = *choose_four(array, start, finish);}

    // Split into 2 parts based on pivot choice
    // make two arrays based on pivot. Insert pivot, insert less elements in BST, more than elements in BST
    // recursive implementation
    
    int split = Partition(array, start, finish);
    insertPivot(pivot.getJourneyCode(), pivot.getPrice());

    // create two new trees 
    // create new constructor suited to this declaration
    SorterTree less(array, split - start + 1);
    SorterTree more(array, finish - split);

    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    less.QuicksortWithBSTInsert(start, split);
    more.QuicksortWithBSTInsert(split+1, finish);

    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

bool SorterTree::insertPivot(int JourneyCode, int price){ // insert node corresponding to chosen pivot in BST
    
    // if inserted, return true (insert takes care of this)

    return this->tree->insert(JourneyCode, price);
}

BST* SorterTree::getTree(){
    return tree;
}

SorterTree::~SorterTree() {
    delete array;
    delete tree;
}