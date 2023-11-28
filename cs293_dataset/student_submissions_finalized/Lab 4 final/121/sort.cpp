#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    this->l=l;
    this->choice=choice;
    array = new Journey [l];
    tree= new BST;
    num_journeys=0;
}

SorterTree::~SorterTree(){   
    // delete tree;
    // delete []array;
}

int SorterTree::compares(){return comparisons;}
int SorterTree::partition(int start, int finish,Journey* pivot){
    if(start>=finish) {
        comparisons++;
        return start;
    }
    Journey j = array[finish];
    array[finish] = *pivot;
    *pivot = j;
    int i = start-1;
    for (int j=start; j<=finish-1; j++){
        comparisons++;
        if(array[j].getJourneyCode()<=array[finish].getJourneyCode()){
            i++;
            comparisons++;
            //exchange arr[i] with arr[j]
            Journey temp=array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    //exchange arr[i+1] with pivot
    Journey temp=array[i+1];
    array[i+1] = array[finish];
    array[finish] = temp;
    return i+1;
}

bool SorterTree::Quicksort(int start, int finish)
{   
    if(start>=finish) return true;

    Journey* pivot;
    // Call appropriate pivot function based on choice
    if(choice==1) pivot=choose_one(array,start,finish);
    else if(choice==2) pivot=choose_two(array,start,finish);
    else if(choice==3) pivot=choose_three(array,start,finish);
    else return false;
    
    // Split into 2 parts based on pivot choice
    int mid = partition(start,finish,pivot);

    // Recursively keep sorting
    Quicksort(start, mid-1);
    Quicksort(mid+1, finish);
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(start<finish){
        comparisons++;
        // Call appropriate pivot function based on choice
        Journey* pivot;
        if(choice==1) pivot=choose_one(array,start,finish);
        else if(choice==2) pivot=choose_two(array,start,finish);
        else if(choice==3) pivot=choose_three(array,start,finish);
        else return false;
        // Split into 2 parts based on pivot choice
        int mid = partition(start, finish, pivot);
        assert(mid>=0);
        assert(mid<l);
    
        //insert into BST
        tree->insert(array[mid].getJourneyCode(), array[mid].getPrice());
        // Recursively keep sorting
        QuicksortWithBSTInsert(start, mid-1);
        QuicksortWithBSTInsert(mid+1, finish);
        
        return true;
    }
    return true;
}

bool SorterTree::insertJourney(int JC, int P){
    if(num_journeys==l){comparisons++;return false;}
    if(num_journeys>=0) {comparisons++;array[num_journeys]=Journey(JC,P);num_journeys++;}
    return true;
}

void SorterTree::printBST(){
    tree->printBST("");
}

bool SorterTree::printArray(){
    for (int i = 0; i < l; i++){
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}