#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{   
    Journey * pivot; 
    // Call appropriate pivot function based on choice
    if (choice==1){
        pivot=choose_one(array,start,finish);
    }
    else if(choice==2){
        pivot=choose_two(array,start,finish);
    }
    else if(choice==3){
        pivot=choose_three(array,start,finish);
    }
    else if(choice==4){
        pivot=choose_four(array,start,finish);
    }
    int i=start,j=finish;
    while(true){
        while(*(pivot)<array[i] || *(pivot)==array[i]){
            i++;
        }
        while(array[j]<*(pivot) || array[j]==*(pivot)){
            j--;
        }
        if(i<j){
            Journey temp;
            temp=array[i];
            array[i]=array[j];
            array[j]=temp;
        }
        else{
            break;
        }
    }
    // Split into 2 parts based on pivot choice
    Quicksort(start,i);
    Quicksort(i+1,finish);
    return true;
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    Journey * pivot;
    if (choice==1){
        pivot=choose_one(array,start,finish);
    }
    else if(choice==2){
        pivot=choose_two(array,start,finish);
    }
    else if(choice==3){
        pivot=choose_three(array,start,finish);
    }
    else if(choice==4){
        pivot=choose_four(array,start,finish);
    }
    // Call appropriate pivot function based on choice
    int i=start,j=finish;
    while(true){
        while(*(pivot)<array[i] || *(pivot)==array[i]){
            i++;
        }
        while(array[j]<*(pivot) || array[j]==*(pivot)){
            j--;
        }
        if(i<j){
            Journey temp;
            temp=array[i];
            array[i]=array[j];
            array[j]=temp;
        }
        else{
            break;
        }
    }
    // Split into 2 parts based on pivot choice
    Quicksort(start,i);
    Quicksort(i+1,finish);
    return insertPivot(pivot->getJourneyCode(),pivot->getPrice());
    // Recursively keep sorting

    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
bool SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode,price);
}