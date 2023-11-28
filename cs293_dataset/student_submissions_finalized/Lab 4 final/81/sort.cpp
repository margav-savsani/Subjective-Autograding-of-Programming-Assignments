#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
int SorterTree::getComparisions(){
    return comparisons;
}
int SorterTree::Partition(int start, int finish)
{   
    // Call appropriate pivot function based on choice
    Journey *pivot;
    if(choice==1){
        pivot = (choose_one(array, start, finish)); 
    }
    if(choice==2){
        pivot = (choose_two(array, start, finish));
    }
    if(choice==3){
        pivot = (choose_three(array, start, finish)); 
    }
    int i=start;
    int j=finish;
    while(true){
        while(!(array[j]<=(*pivot))){j--;comparisons++;}
        while(!((*pivot)<=array[i])){i++;comparisons++;}
        comparisons = comparisons+2;
        if(i<j) {
            Journey J;
            J=array[i];
            array[i]=array[j];
            array[j]=J;
        }
        else return j;}
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}
int SorterTree::Partition_insert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    Journey*  pivot;
    if(choice==1){
        pivot = (choose_one(array, start, finish)); 
    }
    if(choice==2){
        pivot = (choose_two(array, start, finish));
    }
    if(choice==3){
        pivot = (choose_three(array, start, finish)); 
    }
    tree->insert(pivot->getJourneyCode(),pivot->getPrice());
    int i=start;
    int j=finish;
    while(true){
        while(!(array[j]<=(*pivot))){j--;}
        while(!(array[i]<=(*pivot))){i++;}
        if(i<j) {
            Journey J;
            J=array[i];
            array[i]=array[j];
            array[j]=J;
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
               }
         else return j;}
}
bool SorterTree::Quicksort(int start, int finish)
{
if (start<finish){
    int q;
    q=Partition(start,finish);
if(q<finish){
    Quicksort(start,q);
    Quicksort(q+1,finish);}
else{
    Quicksort(start,q-1);
    Quicksort(q,finish);
}
}
return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (start<finish){
    int q;
    q=Partition_insert(start,finish);
if(q<finish){
    QuicksortWithBSTInsert(start,q);
    QuicksortWithBSTInsert(q+1,finish);}
else{
    QuicksortWithBSTInsert(start,q-1);
    QuicksortWithBSTInsert(q,finish);
}
}
if(start == finish){int q=Partition_insert(start,finish);}
return true;
}
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
BST* SorterTree::getTree(){
    return tree;
}
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
