#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp

int SorterTree::Partition(int start,int finish,int &cost){
    // TODO:
    Journey* x = new Journey();
    if(choice==1) x = choose_one(array,start,finish);
    else if(choice==2) x= choose_two(array,start,finish);
    else if(choice==3) x= choose_three(array,start,finish);
    if(x>array+finish || x<array+start) exit(0);    //this aborts the program when any pivot outside the array is given
    int i = start-1;
    int j = finish +1;
    Journey* temp =new Journey();
            *temp = *x;
            *x = array[start];
            array[start] = *temp;
            delete temp;
    while(1){
        do{
            j--;
        }
        while(x->JourneyCode < array[j].JourneyCode);
        do{
            i++;
        }
        while(x->JourneyCode > array[i].JourneyCode);
        cost +=2;
        if(i<j){
            Journey* temp =new Journey();
            *temp = array[i];
            array[i] = array[j];
            array[j] = *temp;
        }
        else return j;
    }
}

void SorterTree::addarray(unsigned int JourneyCode,unsigned int price){
    array[i].JourneyCode = JourneyCode;
    array[i].price= price;
    i++;
}


int SorterTree::Partition2(int start,int finish,int &cost,Journey* x){
    // TODO:
    int i = start-1;
    int j = finish +1;
    Journey* temp =new Journey();
            *temp = *x;
            *x = array[start];
            array[start] = *temp;
            delete temp;
    while(1){
        do{
            j--;
        }
        while(x->JourneyCode < array[j].JourneyCode);
        do{
            i++;
        }
        while(x->JourneyCode > array[i].JourneyCode);
        if(i<j){
            Journey* temp =new Journey();
            *temp = array[i];
            array[i] = array[j];
            array[j] = *temp;
        }
        else return j;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start<finish){
        int q = Partition(start,finish, cost);
        Quicksort(start,q);
        Quicksort(q+1,finish);
        return true;
    }
    return false;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    Journey* x = new Journey();
    if(choice==1) x = choose_one(array,start,finish);
    else if(choice==2) x= choose_two(array,start,finish);
    else if(choice==3) x= choose_three(array,start,finish);
    if(x>array+finish || x<array+start) exit(0);    //this aborts the program when any pivot outside the array is given
    tree->insert(x->JourneyCode,x->price);
    if(start<finish){
        int q = Partition2(start,finish,cost,x);
        QuicksortWithBSTInsert(start,q);
        QuicksortWithBSTInsert(q+1,finish);
        return true;
    }
    return false;
}

void SorterTree::printtree(){
    tree->printBST("");
}

BST* SorterTree:: getTree(){
    return tree;
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}