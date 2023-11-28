#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l) : choice(choice), l(l){
    comparisons = 0;
    // codes = new int[l];
    array = new Journey[l];
    tree = new BST();
}

int partition(Journey* array, int p, int r){
    Journey x = array[r];
    int i = p -1;
    /*
    int j = r + 1;
    while (true){
        do {
            j-=1;
        }while(array[j] < x);
        do {
            i++;
        }while(x < array[i]);
        if (i<j){
            swap(array[i], array[j]);
        }
        else return array+j;
    }*/
    for (int j=p; j<r; j++){
        if (array[j]<x){
            i++;
            swap(array[j], array[i]);
        }
    }
    swap(array[i+1], array[r]);
    return i+1;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    Journey* pivot;
    switch (choice)
    {
    case 1:
        pivot = choose_one(array, start, finish);
        break;
    case 2:
        pivot = choose_two(array, start, finish);
        break;
    case 3:
        pivot = choose_three(array, start, finish);
        break;
    case 4:
        pivot = choose_four(array, start, finish);
        break;
    
    default:
        break;
    }
    // Split into 2 parts based on pivot choice
    // Swap the choice of pivot with the last journey in the array
    /*
    Journey last = array[l-1];
    array[l-1] = *pivot;
    pivot = &last;*/
    swap(*pivot, array[finish]);

    // Now need to go through the array and partition
    // this is the location of the pivot in the partitioned  array
    int head = partition(array, start, finish);

    // Recursively keep sorting
    Quicksort(start, head-1);
    Quicksort(head+1, finish);

}

TreeNode* build(TreeNode* head, int start, int finish, Journey* array, int choice){
    // Call appropriate pivot function based on choice
    Journey* pivot;
    switch (choice)
    {
    case 1:
        pivot = choose_one(array, start, finish);
        break;
    case 2:
        pivot = choose_two(array, start, finish);
        break;
    case 3:
        pivot = choose_three(array, start, finish);
        break;
    case 4:
        pivot = choose_four(array, start, finish);
        break;
    
    default:
        break;
    }
    // Split into 2 parts based on pivot choice
    // Swap the choice of pivot with the last journey in the array
    swap(*pivot, array[finish]);

    // Now need to go through the array and partition
    // this is the location of the pivot in the partitioned  array
    int h = partition(array, start, finish);
    TreeNode* pivotnode = new TreeNode(array[h], nullptr, nullptr, head);

    // Recursively keep sorting
    pivotnode->left = build(pivotnode, start, h-1, array, choice);
    pivotnode->right = build(pivotnode, h+1, finish, array, choice);

    // Insert chosen pivot into the tree appropriately
    return pivotnode;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    build(nullptr, start, finish, array, choice);
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
