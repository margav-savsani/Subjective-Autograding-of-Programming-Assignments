#include "sort.h"   
#include "choose.h"
#include <iostream>
#include <cassert>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    comparisons = 0;
    next = 0;
    tree = new BST();
}
SorterTree::~SorterTree(){
    delete[] array;
}
int SorterTree::partition(Journey* arr, int start, int finish, Journey* pivot){
    int i = start;
    int j = finish;
    Journey piv = *pivot;
    while(true){
        comparisons++;
        while(arr[i]<piv){
            i++;
            comparisons++;
        }
        comparisons++;
        while(arr[j]>piv){
            comparisons++;
            j--;
        }
        if(i<j){
            Journey temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        else{
            if(j==start-1)
                return start;
            if(j==finish)
                return finish-1;
            else return j;
        }  
    }
}
bool SorterTree::Quicksort(int start, int finish)
{
    if(start>=finish)
        return true;
    Journey* pivot = array+start;
    if(choice==1) pivot = choose_one(array, start, finish);
    else if(choice==2) pivot = choose_two(array, start, finish);
    else if(choice==3) pivot = choose_three(array, start, finish); 
    int k = partition(array, start, finish, pivot);
    Quicksort(start, k);
    Quicksort(k+1, finish);
    return true;
}

bool SorterTree::QuicksortWithBSTInsertCore(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(start>=finish)
        return true;
    Journey* pivot = array+start;
    if(choice==1) pivot = choose_one(array, start, finish);
    if(choice==2) pivot = choose_two(array, start, finish);
    if(choice==3) pivot = choose_three(array, start, finish); 
    if(choice==4) pivot = choose_four(array, start, finish);
    tree->insert(pivot->getJourneyCode(), pivot->getJourneyCode());
    // printArray();
    // cout<<"start: "<<start<<"  finish: "<<finish<<"  pivot: "<<(pivot-array)<<endl;
    int k = partition(array, start, finish, pivot);
    QuicksortWithBSTInsertCore(start, k);
    QuicksortWithBSTInsertCore(k+1, finish);
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
    QuicksortWithBSTInsertCore(start, finish);
    tree->printBST("");
    cout<<"Imbalance: "<<tree->getImbalance()<<endl;
    cout<<"comparisons: "<<comparisons<<endl;
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
