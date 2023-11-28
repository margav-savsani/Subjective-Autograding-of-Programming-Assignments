#include "sort.h"
#include <iostream>
SorterTree::SorterTree(int choice,int l)
{
    if(l>0)
    {
        array = new Journey[l];   
    }
    else
    {
        array=NULL;
    }
    tree=new BST;
    this->choice=choice;
    this->l=l;
    comparisons=0;
}

void SorterTree::interchange(Journey* A1,Journey* A2)
{
    unsigned int JrnyC,pri;
    JrnyC=A1->JourneyCode;
    pri=A1->price;
    A2->JourneyCode=A1->JourneyCode;
    A2->price=A1->price;
    A1->JourneyCode=JrnyC;
    A1->price=pri;
}

bool SorterTree::Quicksort(int start, int finish)
{
    Journey* pivot;
    if(choice==1)
    {
        pivot=choose_one(array,start,finish);
    }
    else if(choice==2)
    {
        a=choose_two(Journey* x, int start, int finish);
    }
    else if(choice==3)
    {
        a=choose_three(Journey* x, int start, int finish);
    }
    else if(choice==4)
    {
        a=choose_four(Journey* x, int start, int finish);
    }
    interchange(array[finish],array[pivot]);
    i=start;
    j=finish;
    unsigned int pivot_value=array[finish]->JourneyCode;
    while(i<j)
    {
        while(array[i]->JourneyCode < pivot_value)
        {
            i++;
        }
        while(array[j]->JourneyCode > pivot_value)
        {
            j++;
        }
        interchange(array[i],array[j]);
    }
    if(pivot->JourneyCode)
    {

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
