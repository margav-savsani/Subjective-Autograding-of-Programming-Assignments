#include <iostream>
#include "choose.h"
#include "sort.h"

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    array = new Journey [l];
    comparisons = 0;
}

void swap(Journey *Arr, int a, int b)
{
    Journey temp;
    temp = Arr[a];
    Arr[a] = Arr[b];
    Arr[b] = temp;
    return;
}

bool SorterTree::Quicksort(int start, int finish)
{
    if (start >= finish) return true;
    else if (start + 1 == finish) 
    {
        if (array[start] < array[finish]) 
        {
            comparisons++;
            return true;
        }
        else 
        {
            swap(array, start, finish);
            comparisons++;
            return true;
        }
    }
    else
    {

        Journey pivot;
        if (choice == 1)
        {
            pivot = *choose_one(array, start, finish);
        }
        else if (choice == 2)
        {
            pivot = *choose_two(array, start, finish);
        }
        else if (choice == 3)
        {
            pivot = *choose_three(array, start, finish);
        }
        
        cout << "Pivoted properly\n";

        int a = start, b = finish + 1;

        for (int i = a; i < b; i++)
        {
            if (array[i] < pivot)
            {
                comparisons++;
                continue;
            }
            else
            {
                for (int j = b; j >= i; j--)
                {
                    if (pivot < array[j]) 
                    {
                        comparisons++;
                        b--;
                    }
                    else 
                    {
                        comparisons++;
                        swap(array, i, j);
                        break;
                    }
                }
            }
        }
        Quicksort(start, b);
        Quicksort(b, finish);

    }
}


bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // if (start == finish)
    // Journey pivot;
    // if (choice == 1)
    // {
    //     pivot = *choose_one(array, start, finish);
    // }
    // else if (choice == 2)
    // {
    //     pivot = *choose_two(array, start, finish);
    // }
    // else if (choice == 3)
    // {
    //     pivot = *choose_three(array, start, finish);
    // }

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


void SorterTree::InsertJourney(Journey a, int i)
{
    if (i >= l) return;
    else 
    {
        array[i].setJourneyCode(a.getJourneyCode());
        array[i].setPrice(a.getPrice());
    }
}