#include "sort.h"
//#include "choose.h" //added , not sure if we had to
#include <iostream>
#include <cassert>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    // initializing the array
    array = new Journey[l];
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    // now that we have been given the choice of the function to call for choosing the pivot,
    // we have to call the corresponding function , it would return an pointer to the Journey
    // that is to be used as an pivot for quick sort
    assert(choice <= 4 && choice >= 1);
    assert(start <= finish);
    assert(start >= 0);
    assert(finish <= l-1);

    Journey pivot = array[finish];

    if (choice == 1){pivot = choose_one(array, start, finish);}
    else if (choice == 2){pivot = choose_two(array, start, finish);}
    else if (choice == 3){pivot = choose_three(array, start, finish);}
    else{pivot = choose_four(array, start, finish);}

    //switching the pivot and the last element of the array
    int pivot_jc = pivot.getJourneyCode();
    (pivot) | array[l-1];

    int i = start-1;
    int j = finish+1;

    while(i<j){
        do{
            i=i+1;
        }
        while (array[i].getJourneyCode() >= pivot_jc);
        do{
            j = j-1;
        }
        while(array[j].getJourneyCode() <= pivot_jc);
        array[i] | array[j];
    }
    Quicksort(start,j);
    Quicksort(j+1,finish);
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
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
}
 int main(){

 }