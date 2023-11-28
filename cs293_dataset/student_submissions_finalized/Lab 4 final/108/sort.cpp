#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int ch, int n, Journey a[]) : sz { n }, array { a }, comparisons { 0 } {
    switch (ch) {
    case 1:
        choice = choose_one;
        break;
    case 2:
        choice = choose_two;
        break;
    case 3:
        choice = choose_three;
        break;
    case 4:
        choice = choose_four;
        break;
    }

    tree = new BST {};
}

int SorterTree::partition(Journey* pivot, int start, int finish) {
    if (!pivot) return -1;

    // Check if the pivot is valid or not
    // Also if the pivot is in the array then put it at the end
    bool mx { true }, mn { true };
    for (int i=start; i<=finish; i++) {
        if (&array[i] == pivot) {
            std::swap(array[i], array[finish]);
            pivot = &array[finish];
            mn = false;
            mx = false;
        } else if (array[i] < *pivot) mn = false;
        else mx = false;
        comparisons++;
    }
    if (mx || mn) return -1;


    int i { start };  //  Index of the first element greater than pivot
    while (array[i] < *pivot) i++;
    comparisons += i-start+1;
    for (int j=i+1; j<=finish; j++) {
        // If the element is smaller than the pivot then swap it with the greater one
        if (array[j] < *pivot) std::swap(array[i++], array[j]);

        comparisons++;
    }

    // Put the pivot at its correct place
    if (pivot == &array[finish]) std::swap(array[finish], array[i]);

    return i;
}

bool SorterTree::Quicksort(int start, int finish, int k) {
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    if (start >= finish) return true;

    Journey* pivot = choice(array, start, finish);  // Get the pivot
    int i = partition(pivot, start, finish);  // Partition the array
    if (i == -1) {  // If the pivot chosen is incapable of dividing the array then abort
        std::cout << "Invalid pivot chosen\n";
        return false;
    }
    
    // Recursively sort the samller arrays
    if (!Quicksort(start, i-1)) return false;
    if (!Quicksort(i+(pivot == &array[i] ? 1:0), finish)) return false;
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish) {
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    if (start > finish) return true;

    Journey* pivot = choice(array, start, finish);  // Get the pivot
    int i = partition(pivot, start, finish);  // Partition the array
    if (i == -1) {  // If the pivot chosen is incapable of dividing the array then abort
        std::cout << "Invalid pivot chosen\n";
        return false;
    }
    tree->insert(pivot->JourneyCode, pivot->price);

    // Recursively sort the samller arrays
    if (!QuicksortWithBSTInsert(start, i-1)) return false;
    if (!QuicksortWithBSTInsert(i+(pivot == &array[i] ? 1:0), finish)) return false;
    return true;
}

// Returns the number of comparisons in sorting the array
int SorterTree::comp() {
    return comparisons;
}

// Returns the imbalance of the tree of pivots
int SorterTree::imbalance() {
    return tree->getImbalance();
}

void SorterTree::printArray() {
    for (int i = 0; i < sz; i++)
        std::cout << "Journey code: " << array[i].JourneyCode << "\tJourney Price:" << array[i].price <<std::endl;
}

void SorterTree::printTree() {
    tree->printBST("", false);
}