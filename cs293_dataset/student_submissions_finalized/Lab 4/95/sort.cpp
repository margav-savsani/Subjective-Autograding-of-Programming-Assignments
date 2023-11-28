#include "sort.h"
#include <iostream>


// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice,int l){
    this->choice=choice;
    this->l=l;
    this->comparisons=0;
Journey *array=new Journey[l];

}
int partition(int start,int finish,Journey array[],int choice){
int pivot_element;
if(choice==1){
    pivot_element=choose_one(array,start,finish)->getJourneyCode();
}
else if(choice==2){
    pivot_element=choose_two(array,start,finish)->getJourneyCode();
}
else if(choice==3){
    pivot_element=choose_three(array,start,finish)->getJourneyCode();
}
else {
    pivot_element=choose_four(array,start,finish)->getJourneyCode();
}
    int x=pivot_element;
    int i=start-1;
    int j=finish+1;
    while(true){
        while(array[j].getJourneyCode()<=x){
            j=j-1;
        }
        while(array[i].getJourneyCode()>=x){
            i=i+1;
        }
        if(i<j){
            Journey a=array[i];
            array[i]=array[j];
            array[j]=a;

        }
        else {
            return j;
        }
    }
}
bool SorterTree::Quicksort(int start, int finish)
{  if(start<finish){
 int q=partition(start,finish,array,choice);
 tree->insert(array[q].getJourneyCode(),array[q].getPrice());
SorterTree(start,q);
SorterTree(q+1,finish);
}
return true;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
if(start<finish){
 int q=partition(start,finish,array,choice);
 
SorterTree(start,q);
SorterTree(q+1,finish);
}
return true;
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
    return true;
}
