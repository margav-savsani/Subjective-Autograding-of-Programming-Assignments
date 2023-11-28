#include "sort.h"
#include "choose.h"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice,int l){
    this->choice=choice;
    this->l=l;
    unsigned int jcode,price;
    array=new Journey[l];
    for(int i=0;i<l;i++){
        cin>>jcode>>price;
        array[i]=Journey(jcode,price);
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    Journey* pivot;
    switch(choice){
        case 1: pivot=choose_one(array,start,finish);break;
        case 2: pivot=choose_two(array,start,finish);break;
        case 3: pivot=choose_three(array,start,finish);break;
        case 4: pivot=choose_four(array,start,finish);break;
    }

    if(!(start==finish)){
        int mid=getMidIndex(pivot,start,finish);
        Quicksort(start,mid+1);
        Quicksort(mid,finish);
    }
}

int SorterTree::getMidIndex(Journey* pivot,int start,int finish){
    for(int i=start;i<=finish;i++){
        
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
        cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<endl;
    }
}
