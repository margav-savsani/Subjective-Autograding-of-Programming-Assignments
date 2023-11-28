#include "sort.h"
#include "choose.h"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.h

SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    counter=0;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start<finish){
        int pi;
        Journey* pivot;
        if(choice==1){pivot = choose_one(array,start,finish);}
        else if (choice==2){pivot=choose_two(array,start,finish);}
        else if (choice==3){pivot=choose_three(array,start,finish);}
        else if (choice==4){pivot=choose_four(array,start,finish);}
        int i=start-1;
        for(int j=start;j<=finish;j++){
            if(array[j]<*pivot){
                i++;
                Journey temp=array[j];
                array[j]=array[i];
                array[i]=temp;
            }
        }
        Journey temp=array[i+1];
        array[i+1]=*pivot;
        *pivot=temp;
        pi=i+1;
        Quicksort(start,pi-1);
        Quicksort(pi+1,finish);
    }
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

void SorterTree::insertElement(Journey j){
    array[counter]=j;
    counter+=1;
}