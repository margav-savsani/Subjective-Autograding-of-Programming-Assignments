#include "sort.h"
#include <iostream>

SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    this->comparisons=0;
    this->array = new Journey[l];
    this->tree = new BST();

    //take inputs
    for(int i=0;i<l;i++){
        unsigned int jc, jp;
        cin>>jc>>jp;
        array[i]=Journey(jc,jp);
    }
}

SorterTree::~SorterTree(){
    delete[] array;
    delete tree;
}

BST* SorterTree::getTree(){//get tree ...
    return this->tree;
}

bool SorterTree::Quicksort(int start, int finish) //basic quicksort
{
    if (start==finish) return true;
    if (start>finish) return false;
    
    Journey* chosen;
    Journey the_pivot;
    switch (choice) { // Call appropriate pivot function based on choice
        case 1: {
            chosen= (choose_one(array, start, finish));
            break;
        }
        case 2: {
            chosen= (choose_two(array, start, finish));
            break;
        }
        case 3: {
            chosen= (choose_three(array, start, finish));
            break;
        }
        case 4:{
            chosen= (choose_four(array, start, finish));
        }
    }
    
    //is pivot is guaranteed to be within array/within range remove this
    if (!(chosen<=array+finish&&chosen>=array+start)){ // when pivot given is not in array
        int n;
        bool less=0,more=0;
        //to avoid non termination, given choose will be deterministic
        for(n=start;n<=finish||!(less&&more);n++){
            more=more||(!(array[n]<*chosen));
            less=less||(!(*chosen<array[n]));
        }
        if (n>finish) return false;
    }
    the_pivot = *chosen ;

    // Split into 2 parts based on pivot choice
    int i=start,j=finish;
    
    while(i<j){        
        //looking for indices to be swapped
        for(;array[i]<the_pivot&&(i<j);i++,comparisons++){}
        for(;the_pivot<array[j]&&(i<j);j--,comparisons++){}
        if (i<j){
            std::swap(array[i],array[j]);
        }
    }
    // Recursively keep sorting
    if (finish==i){ // to prevent infinite looping when pivot is last element
        Quicksort(start,finish-1);
        Quicksort(finish,finish);
    }
    else{ // general recursion
        Quicksort(start, i);
        Quicksort(i+1 ,finish);
    }
    return true;
}

// quicksort which also makes the BST simultaneously
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (start==finish) {
        insertPivot(array[start].getJourneyCode(),array[start].getPrice());
        return true;
    }
    if (start>finish) return false;
    
    Journey* chosen;
    Journey the_pivot;
    switch (choice) { // Call appropriate pivot function based on choice
        case 1: {
            chosen= (choose_one(array, start, finish));
            break;
        }
        case 2: {
            chosen= (choose_two(array, start, finish));
            break;
        }
        case 3: {
            chosen= (choose_three(array, start, finish));
            break;
        }
        case 4:{
            chosen= (choose_four(array, start, finish));
        }
    }
    if (chosen==nullptr) return false;
    //is pivot is guaranteed to be within array/within range remove this
    if (!(chosen<=array+finish&&chosen>=array+start)){ // when pivot given is not in array
        int n;
        bool less=0,more=0;
        //to avoid non termination, given choose will be deterministic
        for(n=start;n<=finish||!(less&&more);n++){
            if (array[n]<*chosen) less=1;
            if (*chosen<array[n]) more=1;
            else {
                insertPivot(array[n].getJourneyCode(),array[n].getPrice());
                break;
            }

        }
        if (n>finish) return false;
        insertPivot(chosen->getJourneyCode(),-1); //pivot inserted which doesnt correspond to actual array value
    }
    else{
        // Insert chosen pivot into the tree appropriately
        insertPivot(chosen->getJourneyCode(),chosen->getPrice());
    }
    the_pivot = *chosen ;


    // Split into 2 parts based on pivot choice
    int i=start,j=finish;
    
    while(i<j){        
        //looking for indices to be swapped
        for(;array[i]<the_pivot&&(i<j);i++,comparisons++){}
        for(;the_pivot<array[j]&&(i<j);j--,comparisons++){}
        if (i<j){
            std::swap(array[i],array[j]);
        }
    }
    // Recursively keep sorting
    if (finish==i){ // to prevent infinite looping when pivot is last element
        QuicksortWithBSTInsert(start,finish-1);
        QuicksortWithBSTInsert(finish,finish);
    }
    else{ // general recursion
        QuicksortWithBSTInsert(start, i);
        QuicksortWithBSTInsert(i+1 ,finish);
    }
    return true;
}

int SorterTree::getComparisons(){    
    return comparisons;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }

    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price)
{
    return tree->insert(JourneyCode,price);
}