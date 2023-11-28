#include "sort.h"
#include <iostream>
#include <cassert>

// Code up the functions defined in sort.cpp

void swap(Journey * a, Journey *b){                       //swap two entries
    Journey temp = *a;
    *a = *b;
    *b = temp;
    return;
}

SorterTree::SorterTree(int choice, int l){                 //constructor
    this->choice = choice;
    tree=new BST();
    this->l = l;
    array = new Journey[l];
    comparisons=0;
}

bool SorterTree::Quicksort(int start, int finish)                    //quicksort function
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    //cout <<"start = " <<start << "finish = " << finish << endl;
    if(start > finish){
        return false;
    }

    if(start==finish){
        return true;
    }
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey* pivot;
    if(choice == 1){
        pivot = choose_one(array,start,finish);
    }
    else if(choice == 2){
        pivot = choose_two(array,start,finish);
    }
    else if(choice == 3){
        pivot = choose_three(array,start,finish);
    }
    swap(&array[finish],pivot);
    pivot=&array[finish];
    int front = start - 1;
    for(int i=start; i < finish;i++){
        if(array[i] < *pivot){
            front++;
            swap(&array[front],&array[i]);
        }
        comparisons ++;          
    }
    swap(&array[front+1],&array[finish]);
    front++;
    Quicksort(start,front-1);
    Quicksort(front+ 1,finish);
    return true;
}



void SorterTree::insertelem(int jc , int p,int i){               //insert function
    array[i]= Journey(jc,p);
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)          //quicksort with BST
{
   if(start > finish){
        return false;
    }

    if(start==finish){
        return true;
    }
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey* pivot;
    if(choice == 1){
        pivot = choose_one(array,start,finish);
    }
    else if(choice == 2){
        pivot = choose_two(array,start,finish);
    }
    else if(choice == 3){
        pivot = choose_three(array,start,finish);
    }
    /*else if(choice == 4){
        pivot = choose_four(array,start,finish);
    }*/
    tree->insert(pivot->getJourneyCode(),pivot->getPrice());
    swap(&array[finish],pivot);
    pivot=&array[finish];

    int front = start - 1;
    for(int i=start; i < finish;i++){
        if(array[i] < *pivot){
            front++;
            swap(&array[front],&array[i]);
        }
        comparisons ++;          
    }
    swap(&array[front+1],&array[finish]);
    front++;
    QuicksortWithBSTInsert(start,front-1);
    QuicksortWithBSTInsert(front+ 1,finish);
    return true;
}
