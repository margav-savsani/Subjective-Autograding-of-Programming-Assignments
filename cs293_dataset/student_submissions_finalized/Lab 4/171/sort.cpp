#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int partition(int A[],int start,int finish){
    int x=A[finish];
    int i=start-1;
    int j=finish+1;
    while(1){
        while(A[j]<=x){
            j=j-1;
        }
        while(A[i]>=x){
            i=i+1;
        }
        if(i<j){
            int k=A[i];
            A[i]=A[j];
            A[j]=k;
        }
        else
          return j;
          
    }
}

bool SorterTree::Quicksort(int start, int finish)
{    
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start<finish)
      q=partition(A,start,finish);
    SorterTree(start,q);
    SorterTree(q+1,finish);
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
