#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    tree=new BST;
    array=new Journey[l];
    comparisons=0;
    end=0;
}
bool SorterTree::insert_Journey(int jc, int jp){
    if(end==l) return false;
    array[end]=*new Journey(jc,jp);
    end++;
    return true;
}
void SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting 
    Journey pivot;
    if(choice==1) pivot=*choose_one(array,start,finish);
    if(choice==2) pivot=*choose_two(array,start,finish);
    if(choice==3) pivot=*choose_three(array,start,finish);

    if(start==finish) return;
    
    int less=start;
    int high=finish;
    while(array[less] < pivot){
        comparisons++;
        less++;
    }
    comparisons++;
    while(pivot < array[high]){
        comparisons++;
        high--;
    }
    comparisons++;
    while(less<high){
        Journey temp=array[less];
        array[less]=array[high];
        array[high]=temp;
        less++;
        high--;
        while(array[less] < pivot){
            comparisons++;
            less++;
        }
        comparisons++;
        while(pivot < array[high]){
            comparisons++;
            high--;
        }
        comparisons++;
    }
    if(less>start){
        Quicksort(start,less-1);
        Quicksort(less,finish);
    }
    else{
        Quicksort(start,less);
        Quicksort(less+1,finish);
    }
}
bool SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode,price);
}
void SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    Journey pivot;
    if(choice==1) pivot=*choose_one(array,start,finish);
    if(choice==2) pivot=*choose_two(array,start,finish);
    if(choice==3) pivot=*choose_three(array,start,finish);

    tree->insert(pivot.getJourneyCode(),pivot.getPrice());

    if(start==finish) return;

    int less=start;
    int high=finish;
    while(array[less] < pivot){
        comparisons++;
        less++;
    }
    comparisons++;
    while(pivot < array[high]){
        comparisons++;
        high--;
    }
    comparisons++;
    while(less<high){
        Journey temp=array[less];
        array[less]=array[high];
        array[high]=temp;
        less++;
        high--;
        while(array[less] < pivot){
            comparisons++;
            less++;
        }
        comparisons++;
        while(pivot < array[high]){
            comparisons++;
            high--;
        }
        comparisons++;
    }
    if(less>start){
        QuicksortWithBSTInsert(start,less-1);
        QuicksortWithBSTInsert(less,finish);
    }
    else{
        QuicksortWithBSTInsert(start,less);
        QuicksortWithBSTInsert(less+1,finish);
    }
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

BST* SorterTree::getTree(){
    return tree;
}

int SorterTree::get_comparisons(){
    return comparisons;
}
void SorterTree::print_BST(){
    tree->printBST("");
}
