#include "sort.h"
#include <iostream>
#include "choose.h"
#include "journey.h"

// Code up the functions defined in sort.cpp

void g(Journey *a,int pi,int l){
    
}

void f(Journey *a,int pi,int l){

}

bool SorterTree::Quicksort(int start, int finish){
    Journey *p;
    p= new Journey();
    int pi=0;
    bool b=true;
    if(choice == 1){
        p=choose_one;
    }
    if(choice == 2){
        p=choose_two;
    }
    if(choice == 3){
        p=choose_three;
    }
    if(choice ==4){
        p=choose_four;
    }
    for(int i=0;i<l;i++){
        if(array[i] ==  p){
            pi=i;
            break;
        }
    }
    while(b == true){
        if(start>=0 && finish<=l-1){
            if(start == finish)b=false;
            else if(start < finish){
                f(array,pi,l);
            }

        }
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
