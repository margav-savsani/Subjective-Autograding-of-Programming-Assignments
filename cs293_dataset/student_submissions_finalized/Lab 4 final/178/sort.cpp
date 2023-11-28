#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
int SorterTree::Partition(Journey *A , int start, int finish){
    Journey x=A[finish];
    int i = start-1;
    int j= finish +1;
    while(true){
    while(x<A[j]){
        j=j+1;
        comparisons++;
    }
    while(A[i]<x){
        i=i+1;
        comparisons++;
    }
    if(i<j){
        Journey t = A[i];
        A[i]=A[j];
        A[j]=t;
    }
    else return j;}
    
}

Journey* SorterTree::RandomPartition(Journey *A, int start, int finish){
if(choice==1){
Journey*p= choose_one(A,start,finish);}
if(choice==2){
Journey*p= choose_two(A,start,finish);}
if(choice==3){
Journey* p= choose_three(A,start,finish);}
 
 
     Journey a = A[finish];
       A[finish] =*p;
       p=a;
return &A[finish];
}

 
bool SorterTree::Quicksort(int start, int finish){
    if (start<finish){
        RandomPartition(array,start,finish);
        int  q=Partition(array,start,finish);
                Quicksort(start,q);
                Quicksort(q+1,finish);
    }
    return true;
} 
 
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting


bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    Journey* pivot=RandomPartition(array,start,finish);
tree->insert(pivot->getJourneyCode(),pivot->getPrice());
    return true ;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
