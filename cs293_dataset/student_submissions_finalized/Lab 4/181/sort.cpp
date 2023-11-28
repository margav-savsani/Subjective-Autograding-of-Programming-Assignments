#include "sort.h"
#include <iostream>
// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choose, int l)
{
    choose = choose;
    array = new Journey[l];
    for (int i = 0; i < l, i++;)
    {
        int code;
        int price;
        cin >> code;
        cin >> price;
        array[i]=Journey(code,price);
    }
}
bool SorterTree::Quicksort(int start, int finish)
{ if(choice==1){
    Journey *partit = choose_one(array, start, finish);}
    if(choice==2){
    Journey *partit = choose_two(array, start, finish);}
    if(choice==3){
    Journey *partit = choose_three(array, start, finish);}
    if(choice==4){
    Journey *partit = choose_four(array, start, finish);}
    int i = start;
    int j = finish;
    if (i == j)
    {
        return true;
    }
    while (true)
    {
        if (i >= j)
        {
            break;
        }
        if ((*partit) < array[i] && array[j] < *partit)
        {
            Journey k = array[i];
            array[i] = array[j];
            array[j] = k;
        }
        if (!(*partit < array[i]))
        {
            i++;
        }
        if (!(array[j] < *partit))
        {
            j--;
        }
    }
    Quicksort(start, j);
    Quicksort(j + 1, finish);
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
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
