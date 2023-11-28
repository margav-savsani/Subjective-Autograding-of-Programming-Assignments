#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    array = new Journey[l];
    this->choice = choice;
    this->l = l;
    comparisons=0;
    tree = new BST;
}

bool SorterTree::initializeArray(int index, unsigned int code, unsigned int price){
    if(index < 0 || index >= l)return false;
    Journey J(code, price);
    array[index]=J;
    return true;
}

int SorterTree::Partition(int start, int finish){
    Journey *pivJy;
    if(choice == 1)pivJy= choose_one(array,start,finish);
    else if(choice == 2)pivJy= choose_two(array,start,finish);
    else if(choice == 3)pivJy= choose_three(array,start,finish);
    if(pivJy < array+start || pivJy > array+finish){
        cout<<"Choose function returned a pointer not in the bouds\n";
        cout<<"Exiting the program\n";
        exit(0);
    }
    swap(*pivJy,array[start]);
    Journey *pivRevised=&array[start];
    int cnt=0;
    for(int i=start+1; i<=finish; i++){
        if(array[i] < *pivRevised)cnt++;
        comparisons++;
    }
    int pivotIndex=start+cnt;
    swap(array[pivotIndex],array[start]);
    int i=start;int j=finish;
    while (i < pivotIndex && j > pivotIndex) {
        while(array[i] < array[pivotIndex]) {
            comparisons++;
            i++;
        }
        while(array[pivotIndex] < array[j]) {
            comparisons++;
            j--;
        }
        if(i < pivotIndex && j > pivotIndex) {
            swap(array[i], array[j]);
            i++;j--;
        }
    }
    return pivotIndex;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start > finish)return false;
    else{
        int piv = Partition(start, finish);
        Quicksort(start,piv-1);
        Quicksort(piv+1,finish);
    }
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
     return tree->insert(JourneyCode,price);
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(start > finish)return false;
    else{
        int piv = Partition(start, finish);
        insertPivot(array[piv].getJourneyCode(),array[piv].getPrice());
        QuicksortWithBSTInsert(start,piv-1);
        QuicksortWithBSTInsert(piv+1,finish);
    }
    return true;
}

bool SorterTree::printArray()
{
    std::cout<<"Comparisions: "<<comparisons<<endl;
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    tree->printBST(" ");
    std::cout<<"Imbalance at the root :"<<tree->getImbalance()<<endl;
    return true;
}
