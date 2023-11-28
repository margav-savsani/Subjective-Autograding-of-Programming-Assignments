#include "sort.h"
// #include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
}

void SorterTree::insert(Journey* arr)
{
    for (int i = 0; i < l; i++)
    {
        array[i] = arr[i];
    }
    
}

int SorterTree::Partition(Journey* pivot, int start, int finish)
{
    //swap
    swap(pivot,array[finish]);
    Journey pivotElement = array[finish];

    int i = start - 1;
    int j = finish + 1;
    while(true)
    {
        do
        {   
            j--;
        } while( pivotElement < array[j] );
        do
        {
            i++;
        } while (array[i] < pivotElement );

        if(i < j)
        {
            swap(array[i],array[j]);
        }
        else
        {
            return j;
        }
        
        
    }
    return 0;

}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey* pivot;
    switch(this->choice)
    {
        case 1:
            pivot = choose_one(array,start,finish);
            break;
        case 2:
            pivot = choose_two(array,start,finish);
            break;
        case 3:
            pivot = choose_three(array,start,finish);
            break;
        case 4:
            pivot = choose_four(array,start,finish);
            break;
        default:
            return false;
    }

    std::cout<<pivot->getJourneyCode()<<" "<< pivot->getPrice()<<std::endl;
    // if(start > finish) return false;
    // else
    // {
    //     int mid = 


    // }
    return false;


}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    return 0;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return 0;
}
