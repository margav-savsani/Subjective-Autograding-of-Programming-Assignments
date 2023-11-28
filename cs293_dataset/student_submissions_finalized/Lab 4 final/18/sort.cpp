#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    tree=new BST;
}
//not including the finish index in sorting using quicksort
bool SorterTree::Quicksort(int start, int finish)
{
    if(start>finish) return false;
    
    Journey *pivot=new Journey;
    if(choice==1) pivot = choose_one(array, start, finish);
    if(choice==2) pivot = choose_two(array, start, finish);
    if(choice==3) pivot = choose_three(array, start, finish);

    int N=finish-start+1;
    if(N==1) return true;
    if(pivot==NULL) return false;
    int index=start;
    //cout<<finish<<endl;
    //cout<<pivot<<endl;
    for(int i=start; i<=finish; i++){
        if(array[i]<*pivot){
            Journey t=array[i];
            array[i]=array[index];
            array[index]=t;
            index++;
        }
        comparisons++;
}
    Journey t=array[finish];
    array[finish]=array[index];
    array[index]=t;
    bool a = Quicksort(start,index-1);
    bool b = Quicksort(index+1,finish);
    cout<<comparisons<<endl;
    if(a&&b) return true;
    return false;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(start>finish) return false;
    
    Journey *pivot=new Journey;
    if(choice==1) pivot = choose_one(array, start, finish);
    if(choice==2) pivot = choose_two(array, start, finish);
    if(choice==3) pivot = choose_three(array, start, finish);

    tree->insert(pivot->getJourneyCode(), pivot->getPrice());

    int N=finish-start+1;
    if(N==1) return true;
    if(pivot==NULL) return false;
    int index=start;
    //cout<<finish<<endl;
    //cout<<pivot<<endl;
    for(int i=start; i<=finish; i++){
        if(array[i]<*pivot){
            Journey t=array[i];
            array[i]=array[index];
            array[index]=t;
            index++;
        }
        comparisons++;
}
    Journey t=array[finish];
    array[finish]=array[index];
    array[index]=t;
    bool a = QuicksortWithBSTInsert(start,index-1);
    bool b = QuicksortWithBSTInsert(index+1,finish);
    cout<<comparisons<<endl;
    if(a&&b) return true;
    return false;
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

struct BST* SorterTree::getTree(){
    return tree;
}

