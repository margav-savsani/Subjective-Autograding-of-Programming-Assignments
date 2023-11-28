#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

void SorterTree::insertJourney(unsigned int code,unsigned int price, int index)
{
    array[index].JourneyCode = code;
    array[index].price = price;
    return;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    comparisons=0;

    if (start == finish) return true;

    Journey* pivot;
    Journey temp;

    if ( choice == 1 ) pivot = choose_one(array,start,finish);
    else if ( choice == 2 ) pivot = choose_two(array,start,finish);
    else if ( choice == 3 ) pivot = choose_three(array,start,finish);

    int i = start, j= finish;
    while ( array[i]<*pivot ) i++;
    while ( *pivot<array[j] ) j++;
    if (i<j)
    {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        comparisons++;
    }
    else return (Quicksort(start, i-1) && Quicksort(j+1, finish));

    return false;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    comparisons=0;

    if (start == finish) return true;
    
    Journey* pivot;
    Journey temp;

    if ( choice == 1 ) pivot = choose_one(array,start,finish);
    else if ( choice == 2 ) pivot = choose_two(array,start,finish);
    else if ( choice == 3 ) pivot = choose_three(array,start,finish);
    cout<<"2"<<endl;
    tree->insert(pivot->JourneyCode,pivot->price);
    cout<<"1"<<endl;
    int i = start, j= finish;
    while ( array[i].JourneyCode<pivot->JourneyCode ) i++;
    while ( pivot->JourneyCode<array[j].JourneyCode ) j++;
    cout<<"3"<<endl;
    if (i<j)
    {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        comparisons++;
    }
    else return (Quicksort(start, i-1) && Quicksort(j+1, finish));

    return false;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].JourneyCode<<"\tJourney Price:"<<array[i].price<<std::endl;
    }
}
