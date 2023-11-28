#include "sort.h"
#include <iostream>
// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice,int l){
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    comparisons=0;
    tree=new BST();
}
void SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey pivot;
    if(choice==1) pivot = *choose_one(array,start,finish);
    if(choice==2) pivot = *choose_two(array,start,finish);
    if(choice==3) pivot = *choose_three(array,start,finish);
    int i=start;
    int j= finish;
    while(i<=j){
        while (array[i].getJourneyCode() < pivot.getJourneyCode()) {
            i++; 
            comparisons++;
        }
        while (array[j].getJourneyCode() > pivot.getJourneyCode()) {
            j--;
            comparisons++;
        }
        if (i<=j)
        {
            Journey temp=array[i];
            array[i]=array[j];
            array[j]=temp;
            i++;
            j--;
        }
    }
    if (start<j) Quicksort (start, j);
    if (i<finish) Quicksort( i, finish);
}
bool SorterTree::insertPivot(unsigned int JourneyCode,unsigned int price){
    bool value=tree->insert(JourneyCode,price);
    return value;
}
void SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    Journey pivot;
    if(choice==1) pivot = *choose_one(array,start,finish);
    if(choice==2) pivot = *choose_two(array,start,finish);
    if(choice==3) pivot = *choose_three(array,start,finish);
    insertPivot(pivot.getJourneyCode(),pivot.getPrice());
    int i=start;
    int j= finish;
    while(i<=j){
        while (array[i].getJourneyCode() < pivot.getJourneyCode()) {
            i++; 
            comparisons++;
        }
        while (array[j].getJourneyCode() > pivot.getJourneyCode()) {
            j--;
            comparisons++;
        }
        if (i<=j)
        {
            Journey temp=array[i];
            array[i]=array[j];
            array[j]=temp;
            i++;
            j--;
        }
    }
    if (start<j) QuicksortWithBSTInsert(start, j);
    if (i<finish) QuicksortWithBSTInsert( i, finish);
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
    return true;
}
Journey* SorterTree::getArray(){
    return array;
}
int SorterTree::getcomp(){
    return comparisons;
}