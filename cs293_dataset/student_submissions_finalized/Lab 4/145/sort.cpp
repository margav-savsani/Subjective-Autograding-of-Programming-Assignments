#include "sort.h"
#include <iostream>
// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int l,int choice){
    this->choice=choice;
    this->l=l;
    int code,price;
    array=new Journey[l];
    for (int i=0;i<l;i++){
        cin >> code >> price;
        array[i]=Journey(code,price);
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey* pivot;
    /*if (choice == 1) pivot = choose_one(array,start,finish);
    if (choice == 2) pivot = choose_two(array,start,finish);
    if (choice == 3) pivot = choose_three(array,start,finish);
    if (choice == 4) pivot = choose_four(array,start,finish);*/
    pivot = &(array[l-1]);
    int e=l-1,b=0;
    while (true){
        while(*pivot < array[e] && e > 0) e--;
        while(array[b] < *pivot && b < l) b++;
        if (b<e){
            Journey J = array[b];
            array[b] =array[e];
            array[e] = J;//exchanging the pivots; 
        }
    }
    Quicksort(0,b);
    Quicksort(e,l-1);
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    return false;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

SorterTree::~SorterTree(){
    ;
}