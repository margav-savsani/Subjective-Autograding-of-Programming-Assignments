#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    array = NULL;
    tree = new BST;
    this->choice = choice;
    this->l = l;
    comparisons = 0;
}

int SorterTree::returnComparisions(){
    return comparisons;
}

int SorterTree::Partition(Journey *pivot, int start, int finish){
    int finishstore = finish;
    start--;
    finish++;
    while(true){
        while(finish > 0 && *pivot < array[--finish]){ // or !(array[finish] >= pivot)
            comparisons++;
        }
        while(start < finishstore && array[++start] < *pivot){
            comparisons++;
        }
        comparisons+=2;
        if(finish == finishstore && start == finishstore){ //this is if pivot it last and largest element
            return finish-1;
        }
        else if(start < finish){
            Journey var = array[start];
            array[start] = array[finish];
            array[finish] = var;
        }
        /*else if(start == finish){
            return finish+1;
        }*/
        else{
            //for(int i=start; i<=finish; i++)
            //    cout << i << ":" << array[i].getJourneyCode() << "  ";
            //cout << endl;
            return finish;
        }
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start < finish){
        Journey* pivot = new Journey();
        if(choice==1)
            pivot = choose_one(array, start, finish);
        if(choice==2)
            pivot = choose_two(array, start, finish);
        if(choice==3)
            pivot = choose_three(array, start, finish);
        int index = Partition(pivot, start, finish);
        if(pivot==NULL)
            return false;
        Quicksort(start, index);
        Quicksort(index+1, finish);
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if (start < finish){
        Journey* pivot = new Journey;
        if(choice==1)
            pivot = choose_one(array, start, finish);
        if(choice==2)
            pivot = choose_two(array, start, finish);
        if(choice==3)
            pivot = choose_three(array, start, finish);
        
        int index = Partition(pivot, start, finish);

        tree->insert(pivot->getJourneyCode(), pivot->getPrice());
        Quicksort(start, index);
        Quicksort(index+1, finish);
    }
    return true;
}

BST* SorterTree::getTree(){
    return tree;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
