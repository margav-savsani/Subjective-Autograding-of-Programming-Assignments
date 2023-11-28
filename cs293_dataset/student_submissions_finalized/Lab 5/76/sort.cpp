#include "sort.h"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice,int l){
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    
}

void upgrade(int JourneyCode){

}


bool SorterTree::Quicksort(int start, int finish)

{

    Journey* pivot;
    p = pivot->JourneyCode;
    
    if(choice == 1)
    pivot = choose_one(array,start,finish);
    if(choice == 2)
    pivot = choose_two(array,start,finish);
    if(choice == 3)
    pivot = choose_three(array,start,finish);
    if(choice == 4)
    pivot = choose_four(array,start,finish);

 
    x=array[finish]->getJourneyCode;
    int i=start-1;
    int j=finish+1;
    array[i]->getJourneyCode=p;
    while(true){

        j=j-1;
        i=i+1;
        if((array[j]->getJourneyCode<=x)(array[i]->getJourneyCode>=x))
            break;
        if(i<j)


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
