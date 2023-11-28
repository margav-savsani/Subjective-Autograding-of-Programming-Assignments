#include "sort.h"
#include <iostream>

//Destructor
SorterTree::~SorterTree()
{
    delete [] array;
}

// Constructor initializing variables
SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    comparisons = 0;
    tree = new BST();
}

//New function created to add records in the array
void SorterTree::addJourney(int code, int price, int idx)
{
    array[idx].JourneyCode = code;
    array[idx].price = price;
}

// Call appropriate pivot function based on choice
// Split into 2 parts based on pivot choice
// Recursively keep sorting
bool SorterTree::Quicksort(int start, int finish)
{
    if (start < finish){
        int pivot = Partition(start, finish);
        if (pivot == -1)
            return false;
        if(Quicksort(start, pivot-1)){
            if(Quicksort(pivot+1, finish))
                return true;
        }
    }
    else if(start == finish)
        return true;
    else 
        return false;
}
bool SorterTree::checkElem(Journey* x)
{
    if (x == nullptr)
        return false;
    for(int i=0; i < l; i++){
        if(array[i].getJourneyCode() == x->JourneyCode && array[i].getPrice() == x->price)
            return true;
    }
    return false;
}
// partitions the array, and returns the new pivot, also returns if the array is already sorted 
int SorterTree::Partition(int start, int finish)
{
    if(start < finish){
        Journey* x = NULL;
        switch(choice)
        {
            case 1:
                x = choose_one(array, start, finish);
                break;
            case 2:
                x = choose_two(array, start, finish);
                break;
            case 3:
                x = choose_three(array, start, finish);
                break;
        }
        if(!checkElem(x))
            return -1;
        int i = start - 1;
        int j =  finish + 1;
        while(true){
            do
            {
                j = j - 1;
                comparisons++;
            }
            while(array[j].getJourneyCode() > x->getJourneyCode() && (j > 0));
            do
            {
                i = i + 1;
                comparisons++; 
            }
            while(array[i].getJourneyCode() < x->getJourneyCode());

            if(i < j)
            {
                comparisons++;

                if(&(array[i]) == x)
                {
                    x = (&array[j]);
                }
                Journey temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
            else
            {
                comparisons++;
                Journey temp = array[i];
                array[i] = *x;
                *x = temp;
                return i;
            }
        }
    }
}

// Call appropriate pivot function based on choice
// Split into 2 parts based on pivot choice
// Recursively keep sorting
// Insert chosen pivot into the tree appropriately
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (start < finish){
        int pivot = Partition(start, finish);
        if (pivot == -1)
            return false;
        if(!(tree->find(array[pivot].getJourneyCode(), array[pivot].getPrice())))
            tree->insert(array[pivot].getJourneyCode(), array[pivot].getPrice());
        if(QuicksortWithBSTInsert(start, pivot-1)){
            if(QuicksortWithBSTInsert(pivot+1, finish))
                return true;
        }
    }
    else if(start == finish){
        if(!(tree->find(array[start].getJourneyCode(), array[start].getPrice())))
            tree->insert(array[start].getJourneyCode(), array[start].getPrice());
        return true;
    }
    else 
        return true;
}

//All the elements weren't being printed out in the BST, so wrote this to print out all of them
void SorterTree::insElem()
{
    for(int i = 0; i < l; i++){
        if(!(tree->find(array[i].getJourneyCode(), array[i].getPrice()))){
            tree->insert(array[i].getJourneyCode(), array[i].getPrice());
        }
    }
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}