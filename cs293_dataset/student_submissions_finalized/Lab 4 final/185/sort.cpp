#include "sort.h"
#include <iostream>
//#include"choose.h"
using namespace std;

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (choice == 1){
        pivot = choose_one(array, start, finish);
    }
    if (choice == 2){
        pivot = choose_two(array, start, finish);
    }
    if (choice == 3){
        pivot = choose_three(array, start, finish);
    }

    int i = start - 1;
    int j = finish + 1;
    while (true){
        do{
            i++;
            comparisons++;
        } 
        while (&array[i] < pivot && i < finish);

        do{
            j--;
            comparisons++;
        }
        while (pivot < &array[j] && j > start);

        if (left < right){
            Journey extra(array[i].getJourneyCode(), array[j].getPrice());
            array[i] = array[j];
            array[i] = extra;
            return true;
        }

        else if( i == j){
            if(i < finish){
                i++;
            }
            else if(j > start){
                j--;
            }
            return true;
        }
        else{
            return true;
        }
    }
    Quicksort(i, finish);
    Quicksort(start, j);
    return true;
}



bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if (choice == 1){
        pivot = choose_one(array, start, finish);
        tree->insert(pivot->JourneyCode, pivot->price);
    }
    if (choice == 2){
        pivot = choose_two(array, start, finish);
        tree->insert(pivot->JourneyCode, pivot->price);
    }
    if (choice == 3){
        pivot = choose_three(array, start, finish);
        tree->insert(pivot->JourneyCode, pivot->price);
    }
    int i = start - 1;
    int j = finish + 1;
    while (true){
        do{
            i++;
            comparisons++;
        }
        while (&array[i] < pivot && i < finish);

        do{
            j--;
            comparisons++;
        } while (pivot < &array[j] && j > start);

        if (i < j){
            Journey extra(array[i].getJourneyCode(), array[i].getPrice());
            array[i] = array[j];
            array[j] = extra;
            
            return true;
        }

        else if (i == j){
            if (i < finish){
                i++;
            }
            else if (j > start){
                j--;
            }
            return true;
        }
        else{
            return true;
        }
    }
    Quicksort(i, finish);
    Quicksort(start, j);
    return true;
}

bool SorterTree::printArray(){
    for (int i = 0; i < l; i++){
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
}

BST* SorterTree::getTree(){
    return tree;
}