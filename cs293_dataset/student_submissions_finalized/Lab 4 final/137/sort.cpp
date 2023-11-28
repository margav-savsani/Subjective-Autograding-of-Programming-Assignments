#include "sort.h"
#include <iostream>
#include <fstream>
#include <string>


// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){\
//Constructor
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    comparisons=0;
    tree = new BST();
}

int SorterTree::Partition(int start, int finish){
//Partition function
    Journey *x;
    if(choice == 1)
    {
        x = choose_one(array,start,finish);
    }
    else if(choice == 2)
    {
        x = choose_two(array,start,finish);
    }
    else if(choice == 3)
    {
        x = choose_three(array,start,finish);
    }
    int i = start-1;
    int j = finish+1;
    Journey temp = *x;                                      //Swaping the last element with the pivot
    *x = array[finish];
    array[finish] = temp;
    Journey y = array[finish];
    while(true)
    {
        do
        {
            j--;
            comparisons++;
        }
        while(y < array[j]);                                
        do
        {
            i++;
            comparisons++;
        }
        while(array[i] < y);
        if(i<j)
        {
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        else
        {
            return i;
        }
    } 
}

void SorterTree::Insert(Journey journey, int val){
//Function to insert journey elements into the array
    array[val] = journey;
    return;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start < finish)
    {
        int q = Partition(start,finish);
        bool left = Quicksort(start,q-1);
        bool right = Quicksort(q,finish);
        return true;
    }
    return false;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(start <= finish)
    {
        Journey *x;
        if(choice == 1)                                                      //Choosing a pivot
        {
            x = choose_one(array,start,finish);
        }
        else if(choice == 2)
        {
            x = choose_two(array,start,finish);
        }
        else if(choice == 3)
        {
            x = choose_three(array,start,finish);
        }
        if(!(tree->find(x->getJourneyCode(),x->getPrice())))
        {
            bool ins = insertPivot(x->getJourneyCode(),x->getPrice());        //Inserting the pivot into the BST
        }
        int k = -1;
        for(int i = 0; i<l; i++)
        {
            if(array[i] == *x)
            {
                k = i;
                break;
            }
        }
        if(k==-1)
        {
            return false;
        }
        int i = start-1;
        int j = finish+1;
        Journey temp = *x;                                      //Swaping the last element with the pivot
        *x = array[finish];
        array[finish] = temp;
        Journey y = array[finish];
        while(true)
        {
            do
            {
                j--;
            }
            while(y < array[j]);                                
            do
            {
                i++;
            }
            while(array[i] < y);
            if(i<j)
            {
                Journey temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
            else
            {
                break;
            }
        }
        if(start < finish)
        {
            bool left = QuicksortWithBSTInsert(start,i-1);
            bool right = QuicksortWithBSTInsert(i,finish);
        }
        return true;
    }
    return false;
}

void SorterTree::printTree(){
//Function to print tree
    tree->printBST("");
    return;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
//Function to insert pivot into BST
    return tree->insert(JourneyCode,price);
}

int SorterTree::getImbalance(){
//Function to get imbalance value
    return tree->getImbalance();
}

int SorterTree::getComparisons(){
//Function to get the number of comparisons
    return comparisons;
}

bool SorterTree::printArray()
//Function to print the array 
{
    if(array != NULL)
    {
        for (int i = 0; i < l; i++)
        {
            std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
        }
        return true;
    }
    return false;
}

SorterTree::~SorterTree(){
//Destructor
    delete[] array;
}
