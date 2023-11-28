#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey*p;
    if(choice==1){
        p=choose_one(array,  start, finish);

    }
    if(choice==2){
        p=choose_two(array,  start, finish);
    }
    if(choice==3){
        p=choose_three(array,  start, finish);
    }
    if(choice==4){
        p=choose_four(array,  start, finish);
    }
    if(start<finish){
        int q=partition(start,p,finish);
        Quicksort(start,q);
        Quicksort(q+1,finish);
        return true;
    }
    else return false

}
int SorterTree::partition(int start,Journey*j,int finish){

    int p=start-1;
    int q=finish+1;
    while(true){
        while(true){
            q=q-1;
            if(array[q]<*j) break;
        }
        while(true){
            p=p+1;
            if(array[p]>*j) break;
        }
        if(p<q){
            Journey e=array[p];
            array[p]=array[q];
            array[q]=e;          
        }
        else return q

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
