#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice,int l){
    this->choice=choice;
    this->l=l;
    array =new Journey[l];
    comparisons=0;
    tree=new BST();
}

int SorterTree::getcomparisions(){
    return comparisons;
}

void SorterTree::add(int JourneyCode,int price,int i){
    array[i].update(JourneyCode,price);
}

int SorterTree::partition1(int start,int finish){

    Journey *pivot;

    if(choice==1)     { pivot=choose_one(array,start,finish);}
    else if(choice==2){ pivot=choose_two(array,start,finish);}
    else if(choice==3){ pivot=choose_three(array,start,finish);}

    int i=start-1,j=finish+1;

    int x=pivot->getJourneyCode();
    int y=pivot->getPrice();

    pivot->update(array[finish].getJourneyCode(),array[finish].getPrice());
    array[finish].update(x,y);

    while(true){
        do{
            j--;comparisons++;
        } while(array[j].getJourneyCode()>x && j>start);

        do{
            i++;comparisons++;
        } while(array[i].getJourneyCode()<x && i<finish);

        if(i<j){
            int m=array[j].getJourneyCode(),n=array[j].getPrice();
            array[j].update(array[i].getJourneyCode(),array[i].getPrice());
            array[i].update(m,n);
        }
        else {                    
            return j;
        }
    }
}

int SorterTree::partition2(int start,int finish){

    Journey *pivot;

    if(choice==1)     { pivot=choose_one(array,start,finish);}
    else if(choice==2){ pivot=choose_two(array,start,finish);}
    else if(choice==3){ pivot=choose_three(array,start,finish);}

    int i=start-1,j=finish+1;

    int x=pivot->getJourneyCode();
    int y=pivot->getPrice();
    tree->insert(x,y);

    pivot->update(array[finish].getJourneyCode(),array[finish].getPrice());
    array[finish].update(x,y);

    while(true){
        do{
            j--;comparisons++;
        } while(array[j].getJourneyCode()>x && j>start);

        do{
            i++;comparisons++;
        } while(array[i].getJourneyCode()<x && i<finish);

        if(i<j){
            int m=array[j].getJourneyCode(),n=array[j].getPrice();
            array[j].update(array[i].getJourneyCode(),array[i].getPrice());
            array[i].update(m,n);
        }
        else {                    
            return j;
        }
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    if(start==finish){
        return true;
    }
    int s=partition1(start,finish);

    if(s==finish){
        Quicksort(start,finish-1);
    }
    else {
    Quicksort(start,s); 
    Quicksort(s+1,finish);
    }
    return true;
    
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

    if(start>=finish){
        tree->insert(array[start].getJourneyCode(),array[start].getPrice());
        return true;
    }
    int s=partition2(start,finish);

    if(s==finish){
        QuicksortWithBSTInsert(start,finish-1);
    }
    else {
    QuicksortWithBSTInsert(start,s); 
    QuicksortWithBSTInsert(s+1,finish);
    }
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }

    return true;
}

BST *SorterTree::getTree(){
    return tree;
}

SorterTree::~SorterTree(){
    delete array;
    delete tree;
}