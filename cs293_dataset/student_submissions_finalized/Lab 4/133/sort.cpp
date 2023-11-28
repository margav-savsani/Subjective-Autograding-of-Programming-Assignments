#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l,Journey* array){
    this->choice = choice; 
    this->l = l;
    this->array = array;    
}

int SorterTree::partition(int p,int q){
    int i=p-1;
    int j=q+1;
    Journey J;
    if(choice == 1) &J = choose_one(array, p, q);
    else if(choice == 2) &J = choose_one(array, p, q);
    else if(choice == 3) &J = choose_one(array, p, q);
    else &J = choice_one(array,p,q);
    while(true){
        do{
            j=j-1;
        } while(array[j] < J);

        do{
            i=i+1;
        }while(array[i] > J);

        if(i < j){
            Joureny temp;
            temp=array[i];
            array[i]=array[j];
            array[j]=temp;
        }
        else return j;
    }
}

bool SorterTree::Quicksort(int start=0, int finish=l-1)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start<finish){
        int q = partition(start,finish);
        Quicksort(start,q);
        Quicksort(q+1,finish);
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
