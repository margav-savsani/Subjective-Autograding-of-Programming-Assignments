#include "sort.h"
#include <iostream>

#include "choose.h" //Sure?
// Code up the functions defined in sort.cpp

SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    array = new Journey[l]; //check!

    comparisons = 0; //check!
}

void exchange(Journey* &pivot, Journey* &finish){
    Journey* tmp = new Journey;
    pivot = finish;
    finish = tmp;
    delete tmp; //check syntax.
}

int Partition(Journey* &array, int start, int finish){
    int i = start - 1, j = finish + 1;
    Journey pivot(array[finish].getJourneyCode,array[finish].getPrice);
    while(true){
        while(!(array[j] < pivot))
            j = j-1;
        while(array[j] < pivot)
            i = i+1;
        if(i<j)
            exchange(&array[i],&array[j]);
        else return j;
    }
}

int Blackbox_Partition(Journey* &array, int start, int finish, int choice){
    Journey* pivot = new Journey();
    switch(choice){
        case 1: pivot = choose_one(array, start, finish);
                break;
        case 2: pivot = choose_two(array, start, finish);
                break;
        case 3: pivot = choose_three(array, start, finish);
                break;
        case 4: pivot = choose_four(array, start, finish);
    }
    // int pivot_index = pivot - array; //check! Works in Programiz
    exchange(pivot, &array[finish]);
    return Partition(array, start, finish);
}

bool SorterTree::Quicksort(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    
    // CHECK! Journey* pivot = get_pivot(array, start, finish, choice);
    if(start<finish){
        int q = Blackbox_Partition(array,start, finish);
        Quicksort(A,start,q);
        Quicksort(A,q+1,finish);
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    
    
}

bool SorterTree::printArray(){
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
