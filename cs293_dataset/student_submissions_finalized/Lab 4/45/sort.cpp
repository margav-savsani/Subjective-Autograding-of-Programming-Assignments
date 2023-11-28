#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice,int l){
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    for(int i=0;i<l;i++){
        unsigned int c,p;
        cin>>c>>p;
        array[i]=*(new Journey(c,p));
    }
    comparisons=0;
}

bool SorterTree::Quicksort(int start, int finish)
{
    if(start>finish){return false;}
    Journey pivot;
    if(choice==1){pivot=*choose_one(array,start,finish);}
    if(choice==2){pivot=*choose_two(array,start,finish);}
    if(choice==3){pivot=*choose_three(array,start,finish);}
    if(choice==4){pivot=*choose_four(array,start,finish);}
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    int i=start-1;
    for(int j=start;j<=finish;j++){
        if(array[j] < pivot){
            comparisons++;
            i++;
            swap(array[i],array[j]);
        }   000000000
    }
    swap(array[i+1],pivot);
    int prtn=i+1;
    Quicksort(start,prtn-1);
    Quicksort(prtn+1,finish);
    return true;
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
