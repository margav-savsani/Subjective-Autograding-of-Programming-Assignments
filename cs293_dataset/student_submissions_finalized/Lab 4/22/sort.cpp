#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice=choice;
    this->l=l;
    this->comparisons=0;
}

int SorterTree::partition(int start, int finish, Journey* pivot)
{
    Journey x = *pivot;
    int i=start, j=finish;

    while(true)
    {
        while(array[i] < x)
        {
            i++;
            comparisons++;
        }

        while(!(array[j] < x))
        {
            j--;
            comparisons++;
        }

        if(i < j)
        {
            Journey tmp = array[i];
            array[i] = array[j];
            array[j]=tmp;
        }

        else return j;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start>finish) return false;

    Journey* pivot;

    if(this->choice == 1)pivot = choose_one(this->array, start, finish);
    else if(this->choice==2)pivot = choose_two(this->array, start, finish);
    else if(this->choice==3)pivot = choose_three(this->array, start, finish);
    else if(this->choice==4)pivot = choose_four(this->array, start, finish);

    int splitIndex = partition(start, finish, pivot);

    Quicksort(start, splitIndex);
    Quicksort(splitIndex+1, finish);

    return true;
    
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
