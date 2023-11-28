#include "sort.h"

#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l)
{
    tree=new BST();
    this->choice = choice;
    this->l = l;
    comparisons=0;
}

void swap(Journey *a, Journey *b)
{
    Journey temp = *a;
    *a = *b;
    *b = temp;
}

bool SorterTree::Quicksort(int start, int finish)
{

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey *pivot;

    if (choice == 1) pivot = choose_one(array, start, finish);
    else if (choice == 2) pivot = choose_two(array, start, finish);
    else if (choice == 3) pivot = choose_three(array, start, finish);

    // if the choose function returns nulptr or if the pivot is not a part of the array, then return false
    if (pivot == nullptr || !(pivot >= &array[start] && pivot <= &array[finish])) return false;

    swap(pivot,&array[finish]);

    int p = start - 1;
    for (int i = start; i < finish; i++)
    {
        if (array[i] < array[finish])
        {
            p++;
            swap(&array[i], &array[p]);
        }
        comparisons++;
    }
    p++;
    swap(&array[finish], &array[p]);

    Quicksort(start, p - 1);
    Quicksort(p + 1, finish);

    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey *pivot;

    if (choice == 1) pivot = choose_one(array, start, finish);
    else if (choice == 2) pivot = choose_two(array, start, finish);
    else if (choice == 3) pivot = choose_three(array, start, finish);
    
    // if the choose function returns nulptr or if the pivot is not a part of the array, then return false
    if (pivot == nullptr || !(pivot >= &array[start] && pivot <= &array[finish])) return false; 
    
    insertPivot(pivot->getJourneyCode(), pivot->getPrice());

    swap(pivot,&array[finish]);

    int p = start - 1;
    for (int i = start; i < finish; i++)
    {
        if (array[i] < array[finish])
        {
            p++;
            swap(&array[i], &array[p]);
        }
        comparisons++;
    }
    p++;
    swap(&array[finish], &array[p]);

    QuicksortWithBSTInsert(start, p - 1);
    QuicksortWithBSTInsert(p + 1, finish);

    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    if(tree->find(JourneyCode,price)) return false;
    tree->insert(JourneyCode,price);
    return true;
}

BST* SorterTree::getTree(){
    return tree;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return 1;
}
void SorterTree::getArray(Journey* arr){
    array=arr;
}
void SorterTree::getComparisons(){
    cout<<"No. of comparisons: "<<comparisons<<endl;
}