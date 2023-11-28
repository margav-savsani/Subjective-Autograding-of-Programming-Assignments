#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l) {
    this->choice=choice;
    this->l=l;
    Journey temp_array[l];
    this->array=temp_array;
    for(int theta=0; theta<l; theta++) {
        this->array[theta]=Journey(0, 0, true);
    }
    this->comparisons=0;
    tree=new BST();
}


bool SorterTree::insertPivot(int JourneyCode, int price) {
    tree->insert(JourneyCode, price); return true;
    //if(tree->insert(JourneyCode, price)) return true;
    //else return false;
}

int SorterTree::Quicksort_partition(int start, int finish) {

    Journey* cur_pivot;
    if(choice==1) {
        cur_pivot=choose_one(array, start, finish);
    }
    if(choice==2) {
        cur_pivot=choose_two(array, start, finish);
    }
    if(choice==3) {
        cur_pivot=choose_three(array, start, finish);
    }
    if(choice==4) {
        cur_pivot=choose_four(array, start, finish);
    }

    Journey temp_swap;

    temp_swap=array[start];
    array[start]=*cur_pivot;
    *cur_pivot=temp_swap;

    while(true) {
        while(start<finish && array[start]<*cur_pivot) {
            start+=1;
            comparisons+=1;
        }
        while(finish>start && *cur_pivot<array[finish]) {
            finish-=1;
            comparisons+=1;
        }
        if(finish<=start) break;
        else {
            temp_swap=array[start];
            array[start]=array[finish];
            array[finish]=temp_swap;
        }
    }

    temp_swap=array[finish];
    array[finish]=*cur_pivot;
    *cur_pivot=array[finish];

    return finish;

}

int SorterTree::Quicksort_partition_BST(int start, int finish) {

    Journey* cur_pivot;
    if(choice==1) {
        cur_pivot=choose_one(array, start, finish);
    }
    if(choice==2) {
        cur_pivot=choose_two(array, start, finish);
    }
    if(choice==3) {
        cur_pivot=choose_three(array, start, finish);
    }
    if(choice==4) {
        cur_pivot=choose_four(array, start, finish);
    }

    insertPivot(cur_pivot->getJourneyCodeNew(), cur_pivot->getPrice());

    Journey temp_swap;

    temp_swap=array[start];
    array[start]=*cur_pivot;
    *cur_pivot=temp_swap;

    while(true) {
        while(start<finish && array[start]<*cur_pivot) {
            start+=1;
            comparisons+=1;
        }
        while(finish>start && *cur_pivot<array[finish]) {
            finish-=1;
            comparisons+=1;
        }
        if(finish<=start) break;
        else {
            temp_swap=array[start];
            array[start]=array[finish];
            array[finish]=temp_swap;
        }
    }

    temp_swap=array[finish];
    array[finish]=*cur_pivot;
    *cur_pivot=array[finish];

    return finish;

}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    
    if(start<finish) {
        int pivot_index=Quicksort_partition(start, finish);
        Quicksort(start, pivot_index-1);
        Quicksort(pivot_index+1, finish);
    }

    return true;

}

void SorterTree::Quicksort_new() {
    Quicksort(0, l-1);
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    if(start<finish) {
        int pivot_index=Quicksort_partition_BST(start, finish);
        QuicksortWithBSTInsert(start, pivot_index-1);
        QuicksortWithBSTInsert(pivot_index+1, finish);
    }

    return true;
}

void SorterTree::QuicksortWithBSTInsert_new()
{
    QuicksortWithBSTInsert(0, l-1);
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCodeNew()<<"\t"<<"Journey Price:"<<array[i].getPriceNew()<<std::endl;
    }
}

int SorterTree::getComparisons() {
    return comparisons;
}
