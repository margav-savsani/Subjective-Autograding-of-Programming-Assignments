#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->array = new Journey [l];
    int c, p;
    for (int i = 0; i < l; i++){
        std::cin >> c >> p;
        array[i] = Journey(c, p);
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    if (start == finish){
        return 1;
    }
    int i = start;
    int j = finish;
    Journey * A;
    if (choice == 1){
        A = choose_one(array, start, finish);
    }
    else if (choice == 2){
        A = choose_two(array, start, finish);
    }
    else if (choice == 3){
        A = choose_three(array, start, finish);
    }
    else if (choice == 4){
        A = choose_four(array, start, finish);
    }

    while (true){
        while (array[i] < *A){
            i++;
        }
        while (*A < array[j] || array+j == A){
            j--;
        }
        if (i < j){
            Journey J = array[i];
            array[i] = array[j];
            array[j] = J;
        } 
        else {
            break;
        }
    }
    Quicksort(start, j);
    Quicksort(i, finish);
    if (finish-start == l){
        printArray();
    }
}

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
