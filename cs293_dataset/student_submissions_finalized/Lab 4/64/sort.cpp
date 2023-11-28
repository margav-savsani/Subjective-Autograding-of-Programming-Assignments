#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    for(int i=0; i<l; i++){
        unsigned int c, p;
        cin>>c>>p;
    }
}

int SorterTree::Partition(Journey* A, int start, int finish, Journey *pivot){
    Journey x = *pivot;
    int i=start-1;
    int j=finish+1;
    while(true){
        while(!(A[j]<x)){
            j--;
        }
        while(!(A[i]<x)){
            i++;
        }
        if(i<j){
            Journey temp = A[i];
            A[i]=A[j];
            A[j]=temp;
        }else{
            return j;
        }
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey* pivot;
    if(choice==1){
        pivot=choose_one(array, start, finish);
    }
    if(choice==1){
        pivot=choose_one(array, start, finish);
    }
    if(choice==1){
        pivot=choose_one(array, start, finish);
    }
    if(choice==1){
        pivot=choose_one(array, start, finish);
    }
    if(start<finish){
        int q = Partition(array, start, finish, pivot);
        bool a = Quicksort(start, q);
        bool b = Quicksort(q+1, finish);
    }

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    Journey* pivot;
    if(choice==1){
        pivot=choose_one(array, start, finish);
    }
    if(choice==1){
        pivot=choose_one(array, start, finish);
    }
    if(choice==1){
        pivot=choose_one(array, start, finish);
    }
    if(choice==1){
        pivot=choose_one(array, start, finish);
    }
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
