#include "sort.h"
#include <iostream>
//Swaps contents of two journeys
void swap(Journey *j1,Journey *j2){
    int p=j1->getJourneyCode();
    int q=j1->getPrice();
    j1->change(j2->getJourneyCode(),j2->getPrice());
    j2->change(p,q);
}
// Code up the functions defined in sort.cpp
//Forms partition based on pivot choice
int SorterTree::partition(int start,int finish){
    Journey * pivot; 
    // Call appropriate pivot function based on choice
    if (choice==1){
        pivot=choose_one(array,start,finish);
    }
    else if(choice==2){
        pivot=choose_two(array,start,finish);
    }
    else if(choice==3){
        pivot=choose_three(array,start,finish);
    }
    else{
        std::cout<<"Enter Valid Choice!"<<std::endl;
    }
    int count=-1;
    //Stores former pivot index
    int fpIndex=-2;
    for (int i=start;i<=finish;i++){
        if (array[i]==*(pivot)){
            fpIndex=i;
        }
        if(array[i]<*(pivot) || array[i]==*(pivot)){
            comparisons++;
            count++;
        }
    }
    if (fpIndex==-2){
        return -1;
    }
    //Stores the index where the pivot should be
    int pIndex=start+count;
    //Swapping pivot to its right location
    swap(&array[pIndex],&array[fpIndex]);
    int i=start,j=finish;
    while (i<pIndex && j>pIndex){
        while(array[i]<*(pivot)){
            i++;
            comparisons++;
        }
        while((*(pivot)<array[j])){
            j--;
            comparisons++;
        }
        if (i<pIndex && j>pIndex){
            //Swapping
            swap(&array[i++],&array[j--]);
        }
    }
    //Returning the pivot index
    return pIndex;
}

bool SorterTree::Quicksort(int start, int finish)
{   
    
    if (start >= finish){
        return true;
    }
    // Split into 2 parts based on pivot choice
    int p=partition(start,finish);
    if (p==-1){
        return false;
    }
    Quicksort(start,p-1);
    Quicksort(p+1,finish);
    return true;
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{   
     
     // Split into 2 parts based on pivot choice
    if(start>=finish) return true;
   
    int p=partition(start,finish);
     if (p==-1){
        return false;
    }
     bool i=insertPivot(array[p].getJourneyCode(),array[p].getPrice());
    //Inserting the pivot
    bool j=QuicksortWithBSTInsert(start,p-1);
    bool k=QuicksortWithBSTInsert(p+1,finish);
    return true;
    
    // Recursively keep sorting

    // Insert chosen pivot into the tree appropriately
}
//Prints the array
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
//Inserts the pivot into the tree
bool SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode,price);
}
//Constructor
SorterTree::SorterTree(int ch, int len){
    choice=ch;
    l=len;
    tree=new BST();
    comparisons=0;
}
//Sets the array
void SorterTree::setArray(Journey* a){
    array=a;
}
//Default Destructor
SorterTree::~SorterTree(){
    array=nullptr;
    tree=nullptr;
}
//Returns the pointer to tree
BST* SorterTree::getTree(){
    return tree;
}
//Returns the no. of comparisons performed
int SorterTree::getcomparisons(){
    return comparisons;
}