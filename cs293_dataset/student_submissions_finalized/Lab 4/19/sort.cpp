#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    comparisons = 0;  // what the fuck it does??
}

void SorterTree::exchangethem(Journey *a, Journey *b){
    Journey* s;
    s = a; a = b; b = s;
}

int SorterTree::partition(Journey* array, int start, int finish){
    Journey* x;
    x =  &array[finish];
    int i = start -1;
    int j = finish +1;
    while(true){
        while(&array[j] < x){
            j = j-1;
        }
        while(&array[i] > x){
            i = i+1;
        }
        if (i < j){
            exchangethem(&array[i], &array[j]);
        }
        else
            return j;
    }
}

void SorterTree::Quicksortit(Journey* array, int start, int finish){
    int q;
    if (start < finish){
        q = partition(array, start, finish);
        Quicksortit(array, start, q);
        Quicksortit(array, q+1, finish);
    }
}

bool SorterTree::Quicksort(int start, int finish){
    
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray(){
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
