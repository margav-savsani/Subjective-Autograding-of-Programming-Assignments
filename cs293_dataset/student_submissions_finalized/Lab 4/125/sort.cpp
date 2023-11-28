#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    array = new Journey[l];
    this->l = l;
    this->choice = choice;
    tree = new BST();
}
bool SorterTree::Quicksort(int start, int finish)
{
    Journey* pivot;
    if(start>=finish) return true;
    if(choice==1) pivot = choose_one(array, start, finish);
    else if(choice==2) pivot = choose_two(array, start, finish);
    else if(choice==3) pivot = choose_three(array, start, finish);
    else if(choice==4) pivot = choose_four(array, start, finish);
    int pivot_point;
    int left = start;
    int right = finish;
    while(true){
        while(array[left]<*pivot){
            left++;
        }
        while(*pivot<array[right]){
            right--;
        }
        if(left<right){
            Journey temp=array[left];
            array[left]=array[right];
            array[right]=temp;
        }
        else{
            pivot_point = right;
            break;
        }
    }
    Quicksort(start,right-1);
    Quicksort(right,finish);
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    Journey* pivot;
    if(start>=finish) return true;
    if(choice==1) pivot = choose_one(array, start, finish);
    else if(choice==2) pivot = choose_two(array, start, finish);
    else if(choice==3) pivot = choose_three(array, start, finish);
    else if(choice==4) pivot = choose_four(array, start, finish);
    tree->insert(pivot->getJourneyCode(),pivot->getPrice());
    int pivot_point;
    int left = start;
    int right = finish;
    while(true){
        while(array[left]<*pivot){
            left++;
        }
        while(*pivot<array[right]){
            right--;
        }
        if(left<right){
            Journey temp=array[left];
            array[left]=array[right];
            array[right]=temp;
        }
        else{
            pivot_point = right;
            break;
        }
    }
    Quicksort(start,right-1);
    Quicksort(right,finish);
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}