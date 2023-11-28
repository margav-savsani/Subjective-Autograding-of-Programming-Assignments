#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l) {
    this->choice = choice;
    this->l = l;
    comparisons = 0;
    array = new Journey[l];
    tree = new BST();
    getArray();
}

void SorterTree::getArray() {
    unsigned int code,price;
    for(int i=0; i<l; i++) {
        cin >> code >> price;
        array[i] = Journey(code, price);
    }
}

void swapj(Journey &a, Journey &b) {
    Journey temp = a;
    a = b;
    b = temp;
    return;
}

bool SorterTree::pivotPresent(Journey* pivot) {
    for(int i=0; i<l; i++) {
        comparisons++;
        if(array[i] == *pivot)
            return true;
    }
    return false;
}

int SorterTree::partition(int start, int finish) {
    Journey *pivot;
    switch(choice) {
        case 1: pivot = choose_one(array, start, finish); break;
        case 2: pivot = choose_two(array, start, finish); break;
        case 3: pivot = choose_three(array, start, finish); break;
        case 4: pivot = choose_four(array, start, finish); break;
    }
    // pivot = &(array[start]);
    
    if (!pivotPresent(pivot))
        return -3;
    swapj(*pivot, array[finish]);
    pivot = &(array[finish]);
    
    int i=start-1;
    for(int j=start; j<finish; j++)
    {
        if (array[j] < *pivot) {
            comparisons++;
            i++;
            swapj(array[i], array[j]);
        }
    }
    swapj(array[i+1], array[finish]);
    return i+1;
}

int SorterTree::Quicksort(int start, int finish)
{
    if(finish < start)
        return -1;
    else {
        int part = partition(start, finish);
        if (part == -3)
            return 0;
        bool a = Quicksort(start, part-1);
        bool b = Quicksort(part+1, finish);
        if (!(a && b))
            return 0;
        return 1;
    }
}

int SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(finish < start)
        return -1;
    else {
        int part = partition(start,finish);
        if (part == -3)
            return 0;
        insertPivot(array[part].getJourneyCode(), array[part].getPrice());

        bool a = QuicksortWithBSTInsert(start, part-1);
        bool b = QuicksortWithBSTInsert(part+1, finish);
        if (!(a && b))
            return 0;
        return 1;
    }
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price) 
{
    tree->insert(JourneyCode, price, comparisons);
    return true;
}

int SorterTree::getComparisons() {
    return comparisons;
}

BST* SorterTree::getTree() {
    return tree;
}
