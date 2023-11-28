#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
}

bool SorterTree::Quicksort(int start, int finish)
{
    Journey *pivot=new Journey;
    if(choice==1) pivot = choose_one(array, start, finish);
    if(choice==2) pivot = choose_two(array, start, finish);
    if(choice==3) pivot = choose_three(array, start, finish);
    if(choice==4) pivot = choose_four(array, start, finish);
    //Journey *left=new Journey[];
    int left_count=0;
    //Journey *right=new Journey[];
    int right_count=0;
    Journey *B = new Journey[l];
    int j=0;
    for(int i=0; i<l; i++){
        if(array[i]<pivot) {
            B[j]=array[i];
            j++;
            //left[left_count]=array[i];
            left_count++;
        }
        else {
            //right[right_count]=array[i];
            right_count++;
        }
    }
    int k=left_count;
    for(int i=0; i<l; i++){
        if(array[i]>=pivot){
            B[k]=array[i];
            k++;
            //right[right_count]=array[i];
        }
    }
    array=B;
    bool a = Quicksort(0,left_count-1);
    bool b = Quicksort(left_count,right_count);
    if(a&&b) return true;
    return false;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    bool a = Quicksort(start,finish);
    
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
