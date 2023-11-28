#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start>=finish)return true;
    Journey *j,temp;
    int pivot;
    if(choice==1)j=choose_one(array,start,finish);
    if(choice==2)j=choose_two(array,start,finish);
    if(choice==3)j=choose_three(array,start,finish);
    if(choice==4)j=choose_four(array,start,finish);
    for(int i=start;i<finish;i++){
        if(array[i].getJourneyCode()==j->getJourneyCode()){
            pivot=i;
            break;
        }
    }
    temp=array[pivot];
    array[pivot]=array[finish];
    array[finish]=temp;

    Journey x=array[finish];
    int init=start-1,last=finish+1;
    while(1){
        do{last-=1;}while(!(x<array[last]));
        do{init+=1;}while(!(array[init]<x));
        if(init<last){
            temp=array[init];
            array[init]=array[last];
            array[last]=temp;
        }    
        else break;
    }

    return(Quicksort(start,last) && Quicksort(last+1,finish));

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(start>=finish)return true;
    Journey *j,temp;
    int pivot;
    if(choice==1)j=choose_one(array,start,finish);
    if(choice==2)j=choose_two(array,start,finish);
    if(choice==3)j=choose_three(array,start,finish);
    if(choice==4)j=choose_four(array,start,finish);
    tree->insert(j->getJourneyCode(),j->getPrice());
    for(int i=start;i<finish;i++){
        if(array[i].getJourneyCode()==j->getJourneyCode()){
            pivot=i;
            break;
        }
    }
    temp=array[pivot];
    array[pivot]=array[finish];
    array[finish]=temp;

    Journey x=array[finish];
    int init=start-1,last=finish+1;
    while(1){
        do{last-=1;}while(!(x<array[last]));
        do{init+=1;}while(!(array[init]<x));
        if(init<last){
            temp=array[init];
            array[init]=array[last];
            array[last]=temp;
        }    
        else break;
    }

    return(Quicksort(start,last) && Quicksort(last+1,finish));


}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
