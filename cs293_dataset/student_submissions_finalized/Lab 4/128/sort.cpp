#include "sort.h"
#include "journey.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start == finish){return true;}
    Journey* pivot;
    if(choice == 1){
        pivot = choose_one(array, start, finish);
    }

    else if(choice == 2){
        pivot = choose_two(array, start, finish);
    }

    else if(choice == 3){
        pivot = choose_three(array, start, finish);
    }

    else if(choice == 4){
        pivot = choose_four(array, start, finish);
    }

    

    int i = start;
    int j = finish;

    while( true ){
        while ( array[i] < *pivot ){
            i++;
        }
        while ( !(array[j] <  *pivot) ){
            j--;
        }
        if(j > i){break;}
        Journey temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    
    Quicksort(start, j);
    Quicksort(i, finish);
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursivel y keep sorting
    // Insert chosen pivot into the tree appropriately

    if(start == finish){return true;}
    Journey* pivot;
    if(choice == 1){
        pivot = choose_one(array, start, finish);
    }

    else if(choice == 2){
        pivot = choose_two(array, start, finish);
    }

    else if(choice == 3){
        pivot = choose_three(array, start, finish);
    }

    else if(choice == 4){
        pivot = choose_four(array, start, finish);
    }
    
    

    int i = start;
    int j = finish;

    while( true ){
        while ( array[i] < *pivot ){
            i++;
        }
        while ( !(array[j] <  *pivot) ){
            j--;
        }
        if(j > i){break;}
        Journey temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    
    Quicksort(start, j);
    Quicksort(i, finish);
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
