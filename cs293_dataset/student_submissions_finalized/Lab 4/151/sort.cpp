#include "sort.h"
#include <iostream>



void swap(Journey* j1, Journey* j2){
    Journey* temp;
    temp = j1;
    j1 = j2;
    j2 = temp;
    delete temp;
    return;
}


// Code up the functions defined in sort.cpp


SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;

    array = new Journey[l];
    tree = new BST();
}


// insert node corresponding to chosen pivot in BST
bool SorterTree::insertPivot(int JourneyCode, int price){
    bool flag;
    flag = tree->insert(JourneyCode, price);
}

// returns pointer to the tree of pivots
BST* SorterTree::getTree(){
    return tree;
}



bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    Journey* pivot;

    switch(choice){
        case 1:
            pivot = choose_one(array, start, finish);
            break;
        case 2:
            pivot = choose_two(array, start, finish);
            break;
        case 3:
            pivot = choose_three(array, start, finish);
            break;
        case 4:
            pivot = choose_four(array, start, finish);
            break;
    }

    // Swap pivot with the last element of array
    swap(&array[finish], pivot);


    // Split into 2 parts based on pivot choice
    
    int i = start - 1;

    for(int j = start; j < finish; j++){

        if(array[j] < *pivot){
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i+1], pivot);

    int pivot_pos = i+1;

    // Recursively keep sorting

    Quicksort(start, pivot_pos - 1);
    Quicksort(pivot_pos + 1, finish);


}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately


    // Call appropriate pivot function based on choice
    Journey* pivot;

    switch(choice){
        case 1:
            pivot = choose_one(array, start, finish);
            break;
        case 2:
            pivot = choose_two(array, start, finish);
            break;
        case 3:
            pivot = choose_three(array, start, finish);
            break;
        case 4:
            pivot = choose_four(array, start, finish);
            break;
    }

    // Swap pivot with the last element of array
    swap(&array[finish], pivot);


    // Split into 2 parts based on pivot choice
    
    int i = start - 1;

    for(int j = start; j < finish; j++){

        if(array[j] < *pivot){
            i++;
            swap(&array[i], &array[j]);
        }
    }

    int pivot_pos = i+1;
    swap(&array[pivot_pos], pivot);



    // ADD PIVOT INTO THE TREE
    insertPivot(pivot->JourneyCode, pivot->price);


    // Recursively keep sorting

    Quicksort(start, pivot_pos - 1);
    Quicksort(pivot_pos + 1, finish);
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
