#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

void get_array(Journey* A, int l) {

    cout << "ADD DEL FIND PRINT" << endl;

    for (int i = 0; i < l; i++){
        int journeyCode;
        cin >> journeyCode;

        unsigned int price = 100;

        A[i] = new Journey(journeyCode, price);
    }

}

SorterTree::SorterTree(int choice, int l){

    array = new Journey[l];

    get_array(array, l);

    // choice is given here so we can choose pivots here, that means we should sort here itself

}

int partition(Journey* A, int start, int finish){

    Journey x = A[finish];
    int i = start;
    int j = finish;

    while (true){

        while (x < A[j]){
            j -= 1;
        }

        while (A[i] < x){
            i += 1;
        }

        if (i < j){

            Journey temp = A[j];

            A[j] = A[i];

            A[i] = temp;

        } else {

            return j;
        }

    }

}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    if (start < finish){
        int pivot = partition(array, start, finish);
        Quicksort(start, pivot);
        Quicksort(pivot+1, finish);
    }

    return true;

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    if (start < finish){
        int pivot = partition(array, start, finish);
        Quicksort(start, pivot);
        Quicksort(pivot+1, finish);
    }

    return true;

}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
