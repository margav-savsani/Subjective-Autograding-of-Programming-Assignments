#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int Choice,int L){
    array = new Journey[L];
    choice = Choice;
}

bool SorterTree::Quicksort(int start, int finish)
{   if(start>=finish){
       return true;
    }
    Journey* pivot;
    if(choice==1){pivot = choose_one(array,start,finish);}
    else if(choice==2){pivot = choose_two(array,start,finish);}
    else if(choice==3){pivot = choose_three(array,start,finish);}
    else if(choice==2){pivot = choose_four(array,start,finish);}
    else;
    int i=start;
    int j=finish;
    while (true){
        while (array[i]<pivot){
            i++;
        }
        while (array[j].Journeycode>=pivot->Journeycode){
            j--;
        }
        if(i<=j){
            int jtemp = array[j].Journeycode;
            int ptemp = array[j].price;
            array[j].Journeycode=array[i].Journeycode;
            array[j].price=array[i].price;
            array[i].Journeycode=jtemp;
            array[i].price=ptemp;
        }
        else break;
    }
    int pivotindex=i;
    Quicksort(start,pivotindex-1);
    Quicksort(pivotindex+1,finish);
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
