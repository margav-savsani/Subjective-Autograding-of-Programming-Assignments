#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int s,int length){
    choice=s;
    l=length;
    Journey *A=new Journey[l];
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start<finish){
        int q=partition(A[],start,finish);
        Quicksort(start,q);
        Quicksort(q+1;finish);
    }
}

int SorterTree::partition(A[], int p,int r){
        int x=A[r];
        int i=p-1;
        int j=r+1;
        while(true){
            while(A[j]<=x){
                j=j-1;
            }
            while(A[i]>=x){
                i=i+1;
            }
            if(i<j){
                int temp;
                temp=A[i];
                A[i]=A[j];
                A[j]=temp;
            }
            else {return j;}
        }
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