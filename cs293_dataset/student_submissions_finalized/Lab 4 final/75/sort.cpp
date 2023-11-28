#include "sort.h"
#include "journey.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp
int SorterTree::Partition(Journey* array, int p, int r, int flag){
    
    Journey* x; // declaring the pivot journey
    if (choice==1){
        x =  choose_one(array, p, r); // x is the pivot wrt which partition will be done
    }
    else if (choice==2){
        x =  choose_two(array, p, r); // choose the pivot based on choice by the user
    }
    else if (choice==3){
        x =  choose_three(array, p, r);
    }
    
    // To insert into the tree if flag = 1;
    if (flag){
        
        tree->insert(x->getJourneyCode(), x->getPrice()); 
    }

    int i = p;
    int j = r;

    while(true){
        while (*x < array[j]){ // moving the right pointer to lower indices till it sees sorted array
            j--;
            comparisons++;
        }
        comparisons++;
        while (array[i] < *x){ // moving the left pointer to higher indices till it sees sorted array
            i++;
            comparisons++;
        }
        comparisons++; // to count when the conditions is false
        if(i<j){
            Journey temp = array[i]; // exchanging the Journeys if they are not in correct order
            array[i] = array[j];
            array[j] = temp;

        }
        else{
            return j;
        }
    }
}
bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // cout<<"Within the quicksort function"<<endl;
    int pivot = 0;
    //  cout<<"Printing the array:"<<endl;
    //  printArray();
    //  cout<<endl;
    //  cout<<" Start: "<<start<<" Finish: "<<finish<<endl;
    //  cout<<endl;

    pivot = Partition(array, start, finish,0); // the pivot based on which array will be partitioned


    if (start<finish){
        // cout<<"Pivot: "<<pivot<<" Start: "<<start<<" Finish: "<<finish<<endl;
        if (pivot!=finish){

            Quicksort(start, pivot);// recursively calling Quicksort to sort the first array
            Quicksort(pivot+1, finish);// recursively calling Quicksort to sort the second array
        }
        else{
            Quicksort(start, pivot-1);// recursively calling Quicksort to sort the first array
            Quicksort(pivot, finish);// recursively calling Quicksort to sort the second array
        }
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    int pivot = 0;

    pivot = Partition(array, start, finish,1); // the pivot based on which array will be partitioned

    if (start<finish){
        
        if (pivot!=finish){
            QuicksortWithBSTInsert(start, pivot);// recursively calling Quicksort to sort the first array
            QuicksortWithBSTInsert(pivot+1, finish);// recursively calling Quicksort to sort the second array
        }
        else{
            QuicksortWithBSTInsert(start, pivot-1);// recursively calling Quicksort to sort the first array
            QuicksortWithBSTInsert(pivot, finish);// recursively calling Quicksort to sort the second array
        }
    }
    return true;

}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

// defining the constructor for the class
SorterTree:: SorterTree(int choice, int l){
    this-> choice = choice;
    this-> l = l;

    // making a new array dynamically
    array = new Journey[l];
    tree = new BST;

    comparisons = 0;

}

Journey* SorterTree:: getArray(){
    return this->array;
}

SorterTree:: ~SorterTree(){
    delete [] array;
}

 BST* SorterTree:: getTree(){
    return tree;
 }

int SorterTree:: getComparisons(){
    return comparisons;
}

void SorterTree:: setComparisons(int i){
    comparisons = i;
}
