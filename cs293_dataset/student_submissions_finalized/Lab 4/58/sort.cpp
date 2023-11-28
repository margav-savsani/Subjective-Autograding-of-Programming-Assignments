#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice,int l){
    this->choice=choice;
    this->l=l;
    array =new Journey[l];
}

bool SorterTree::Quicksort(int start, int finish)
{
    Journey *pivot;

    if(choice==1){ pivot=choose_one(array,start,finish);}
    else if(choice==2){ pivot=choose_two(array,start,finish);}
    else if(choice==3){ pivot=choose_three(array,start,finish);}
    else if(choice==4){ pivot=choose_four(array,start,finish);}

    int i=start-1,j=finish+1;

    int x=pivot->getJourneyCode();

    while(true){
        do{
            j--;
        } while(array[j].getJourneyCode()<=x);

        do{
            i++;
        } while(array[i].getJourneyCode()>=x);

        if(i<j){
            return true;
        }
        else {
            array[i].update(array[j].getJourneyCode());
            array[j].update(array[i].getJourneyCode());
        }
    }
    
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
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
