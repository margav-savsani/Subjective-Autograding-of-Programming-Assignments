#include "sort.h"
#include <iostream>

// ISSUE : QUICK SORT ALGORITHM NOT WORKING PROPERLY -- DERIVE IMPL FROM SCRATCH.

// Code up the functions defined in sort.cpp

// partitioning function to quicksort. 
// p = end of array , r = start of array

// assumes that the tree is blank, i.e. space allocated on the heap

SorterTree::SorterTree(Journey* A, int l, int choice /*= 1*/) {
    this->l = l;
    //this->array = new Journey[l];
    this->array = A;
    this->tree = new BST();
    this->choice = choice;
}

/*
int Partition(Journey* A, int p, int r) {
    Journey x = A[r];
    int i = p-1;
    int j = r+1;

    while (true) {
    
        
        do {j = j - 1; } while(x<A[j]);

        do {i = i + 1; } while(A[i] < x);


        if (i<j){
            Journey temp = A[i];
            A[i] = A[j];
            A[j] = temp;


        }
        else {
            if (i == j) j = j-1;

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
    else {
        return;
    }
}
*/
int SorterTree::Partition(int start, int end)
{
 
    Journey pivot = array[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        comparisons++;
        if ((array[i] < pivot) || (array[i] == pivot))
            count++;
    }
    // Giving pivot element its correct position
    int pivotIndex = start + count;

    swap(array[pivotIndex], array[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
        comparisons++;
        while ((array[i] < pivot) || (array[i] == pivot)) {
            i++;
        }
        comparisons++;
        while (pivot < array[j]) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(array[i++], array[j--]);
        }
    }
 
    return pivotIndex;
}
 
void SorterTree::quickSort(int start, int finish)
{
    /* Swapping pivot with start */

    // base case
    if (start >= finish)
        return;
        
    Journey pivot;
    if (choice == 1) {pivot = *choose_one(array, start, finish);}
    else if (choice == 2) {pivot = *choose_two(array, start, finish);}
    else if (choice == 3) {pivot = *choose_three(array, start, finish);}
    // else if (choice == 4) {pivot = *choose_four(array, start, finish);}

    bool found = false;
    for (int i=start; i<=finish; i++){
        if (array[i] == pivot){
            // cout << i << endl;
            swap(array[i], array[start]);
            found = true;
            break;
        }
    }

    if (!found){
        cout << "Sorry, Pivot does not exist. " << endl;
        exit(0);
    }
    
 
    // partitioning the array
    int p = Partition(start, finish);
 
    // Sorting the left part
    quickSort(start, p - 1);
 
    // Sorting the right part
    quickSort(p + 1, finish);
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish, bool setpivot/*=false*/)
{
    // calling the appropriate pivot based on choice

    // base case
    if (start > finish)
        return true;
        
    Journey pivot;
    if (choice == 1) {pivot = *choose_one(array, start, finish);}
    else if (choice == 2) {pivot = *choose_two(array, start, finish);}
    else if (choice == 3) {pivot = *choose_three(array, start, finish);}
    // else if (choice == 4) {pivot = *choose_four(array, start, finish);}

    bool found = false;
    for (int i=start; i<=finish; i++){
        if (array[i] == pivot){
            // cout << i << endl;
            swap(array[i], array[start]);
            found = true;
            break;
        }
    }

    if (!found){
        cout << "Sorry, Pivot does not exist. " << endl;
        exit(0);
    }
    int split = Partition(start, finish);
    // this->tree->printBST("");
    //cout << array[split].getJourneyCode() << endl;
    insertPivot(array[split].getJourneyCode(), array[split].getPrice());
    // create two new trees 
    // create new constructor suited to this declaration
    //SorterTree less(array, split - start + 1);
    //SorterTree more(array+split, finish - split);

    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    QuicksortWithBSTInsert(start, split-1);
    QuicksortWithBSTInsert(split+1, finish);
}

void SorterTree::printArray()
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
    delete [] array;
}
