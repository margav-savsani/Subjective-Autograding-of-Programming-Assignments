#include "sort.h"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){                // Define valid constructor
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    comparisons=0;
    tree = new BST();         
  };

int SorterTree::part(int start, int finish){
    Journey a=array[finish];
    int i=start;
    int j=finish;
    for(int k=start; k<j; k++){
        comparisons++;
        if(array[k].getJourneyCode() < a.getJourneyCode()){
            Journey temp=array[i];
            array[i]=array[k];
            array[k]=temp;
            i++;
        }
    }
    Journey temp=array[i];
    array[i]=array[j];
    array[j]=temp;
    return(i);
}

int SorterTree::choices(int start, int finish){
    Journey* pivot;
    if(choice==1){pivot=choose_one(array,start,finish);}
    if(choice==2){pivot=choose_two(array,start,finish);}
    if(choice==3){pivot=choose_three(array,start,finish);}

    Journey temp=*pivot;
    *pivot=array[finish];
    array[finish]=temp;

    return part(start,finish);

}

void SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    if(start>finish) return;
    int p=choices(start,finish);
    Quicksort(start,p-1);
    Quicksort(p+1,finish);

}

void SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    if(start>finish) return;
    int p=choices(start,finish);
    insertPivot(array[p].getJourneyCode(), array[p].getPrice());
    QuicksortWithBSTInsert(start,p-1);
    QuicksortWithBSTInsert(p+1,finish);
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

