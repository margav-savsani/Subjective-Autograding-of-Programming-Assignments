#include "sort.h"
#include "journey.h"
#include "choose.h"
#include <iostream>


// TODO
class Journey;

// Code up the functions defined in sort.cpp

int Partition(Journey* array, int start,int finish,int &cost){
    // TODO:
    int choice;
    Journey* x = new Journey();
    if(choice==1) x = choose_one(array,start,finish);
    else if(choice==2) x= choose_two(array,start,finish);
    else if(choice==3) x= choose_three(array,start,finish);
    else if (choice==4) x= choose_four(array,start,finish);
    int i = start-1;
    int j = finish +1;
    while(1){
        while(array[--j] < *x){cost++;}
        while(*x < array[++i]){cost++;}
        if(i<j){
            Journey* temp =new Journey();
            *temp = array[i];
            array[i] = array[j];
            array[j] = *temp;
        }
        else return j;
    }
}

bool SorterTree::Quicksort(int start, int finish){
    int cost =0;
    if(start<finish){
        int q = Partition(array,start,finish, cost);
        Quicksort(start,q);
        Quicksort(q+1,finish);
    }
     cout<<cost<<endl;   
}
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting


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
