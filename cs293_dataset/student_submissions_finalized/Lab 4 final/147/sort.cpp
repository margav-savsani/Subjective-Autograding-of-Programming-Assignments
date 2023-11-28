#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp

Journey *SorterTree::getPivot(int start, int finish) const{
    switch (choice)
    {
        case 1: return choose_one(array, start, finish);
        case 2: return choose_two(array, start, finish);
        case 3: return choose_three(array, start, finish);
        case 4: return choose_four(array, start, finish);
        default: return nullptr;
    }
}

void swap(Journey &a, Journey &b){
    const Journey tmp = a;
    a = b;
    b = tmp;
}

// two partition functions. Both will return (possibly) different but correct subarrays for the same input. They have different but similar(both two pointer) implementations.

// clrs - the wall idea. Yet to thoroughly test.
int partition(Journey *array, Journey *pivot, int start, int finish){

    swap(*pivot, array[finish]); // get pivot to be the last element.
    Journey *x = &array[finish];

    int i = start-1; // it is just behind the "wall == the first element >= pivot"
    // run through each element of the subarray in order
    for (int j = start; j < finish; j++){
        if (array[j] < *x){
            swap(array[j], array[i+1]); // array[i+1] is the wall ie >= pivot. swap it with array[j] < pivot.
            i++; // move i forward.
        }
    }
    swap(array[i+1], array[finish]); // finally get array[finish] = pivot before all the elements >= pivot.
    return i + 1; // the final location of the pivot.
}

// slides - the left-right pointers idea. Tested.
int partition2(Journey *array, Journey *pivot, int start, int finish){
    swap(*pivot, array[finish]);
    Journey *x = &array[finish];
    finish--; // set finish to be just before the new location of the pivot.
    while(true){
        while(array[start] < *x) start++;
        while(!(array[finish] < *x)) finish--; // using !< for >=.
        if (start > finish){
            swap(array[start], *x); // start is guaranteed to be <= finish_original since array[finish_original] = *x is = pivot >= pivot. And array[start] is >= pivot else start would have been incremented.
            return start; // or return finish + 1.
        }
        swap(array[start], array[finish]);
    }
}

bool SorterTree::Quicksort(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    if (start >= finish) return true; // empty and one-element arrays are sorted.

    Journey *pivot = getPivot(start, finish);
    if (!pivot || pivot - array < start || pivot - array > finish){
        writeToConsole(pivot, start, finish);
        return false; // getPivot returned a wrong pivot location.
    }

    // std::cout << pivot->getJourneyCode() << " " << pivot->getPrice() << std::endl;
    int pivot_updated = partition2(array, pivot, start, finish);
    // std::cout << pivot_updated << std::endl;
    // printArray();   
    return Quicksort(start, pivot_updated - 1)
    && Quicksort(pivot_updated + 1, finish);
    // we return true iff both quicksort calls returned true(ie sorted correctly).
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish, TreeNode *parent, bool left){
    // Call appropriate pivot function based on choice, split into 2 parts based on pivot choice, recursively keep sorting.
    // We insert chosen pivot into the tree appropriately - notice this insertion is faster since we straightaway know the location to insert, all we have to do is update the shortedt and longest path length variables for each node on the path to the newly inserted node.

    if (start > finish) return true; // empty arrays are sorted.
    
    if (start == finish){
        tree->insert(array[start].getJourneyCode(), array[start].getPrice(), parent, left); // one element subarray is sorted, but we must insert the element into tree.
        return true;
    }

    Journey *pivot = getPivot(start, finish);
    
    if (!pivot || pivot - array < start || pivot - array > finish){
        writeToConsole(pivot, start, finish);
        return false; // getPivot returned a wrong pivot location.
    }
    
    int pivot_updated = partition2(array, pivot, start, finish);
    TreeNode * pivotLocInTree = tree->insert(array[pivot_updated].getJourneyCode(), array[pivot_updated].getPrice(), parent, left);
    
    // printBST(); std::cout << std::endl;
    // std::cout << getTreeImbalance() << std::endl;
    
    return QuicksortWithBSTInsert(start, pivot_updated - 1, pivotLocInTree, true)
    && QuicksortWithBSTInsert(pivot_updated + 1, finish, pivotLocInTree, false);
    // we return true iff both quicksort calls returned true(ie sorted correctly).
}

void SorterTree::printArray() const{
    for (int i = 0; i < l; i++){
        std::cout << "Journey code: " << array[i].getJourneyCode() <<
        "\t\tJourney Price: " << array[i].getPrice() <<std::endl;
    }
}
void SorterTree::printBST() const{
    assert(tree);
    tree->printBST("");
}
int SorterTree::getNumComparisons() const{ return Journey::howManyComparisons(); }

void SorterTree::load(std::ifstream &in){
    array = new Journey[l];
    for (int i = 0; i < l; i++){
        unsigned int journeyCode, journeyPrice;
        in >> journeyCode >> journeyPrice;
        array[i] = Journey(journeyCode, journeyPrice);
    }
}

void SorterTree::writeToConsole(Journey *pivot, int start, int finish) const{
    std::cout << "Given pivot: " << pivot << std::endl;
    std::cout << "Expected pivot: One of \n";
    for (int i = start; i <= finish; i++)
        std::cout << array + i << " ";
    std::cout << std::endl;
}