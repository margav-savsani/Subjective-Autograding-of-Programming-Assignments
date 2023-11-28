#ifndef SORT_CPP
#define SORT_CPP

#include "sort.h"
#include <iostream>

using namespace std;

SorterTree::SorterTree(int c, int arrayL)
{
    choice = c;
    l = arrayL;
    tree = new BST();
    comparisons=0;
}

// Code up the functions defined in sort.cpp

Journey* SorterTree::getArray(){
    return array;
}

void SorterTree::inputArray()
{
    array = new Journey[l];
    int c, p;
    for (int i = 0; i < l; i++)
    {
        cin >> c;
        cin >> p;
        array[i].setParams(c, p);
    }
}

void swap(Journey *A, int a, int b)
{
    Journey temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

int SorterTree::Partition(Journey *A, int start, int finish)
{
    if(start == finish) {
        tree->insert(array[start].getJourneyCode(), array[start].getPrice());
        return start;
    }

    int jCode, pr;
    Journey* jour;
    if(choice == 1) {
         jour = choose_one(A, start, finish);
         jCode = jour->getJourneyCode();
         pr = jour->getPrice();
    }
    else if(choice == 2){
        jour = choose_two(A, start, finish);
        jCode = jour->getJourneyCode();
        pr = jour->getPrice();
    }
    else if(choice == 3) {
        jour = choose_three(A, start, finish);
        jCode = jour->getJourneyCode();
        pr = jour->getPrice();
    }
    
    int index = start;
    for (index; !(A[index].getJourneyCode() == jCode && A[index].getPrice() == pr) && (index<=finish); index++);
    if(index>finish){
        cout << "Choose function misbehaved!" << endl;
        cout << "Exiting Gracefully" << endl;
        exit(0);
    }

    if(start < index) swap(A, start, index);

    int i = start, j = finish;
    while (i != j)
    {
        comparisons++;
        while (A[i].getJourneyCode() < jCode && i!=j)
        {
            comparisons++;
            i++;
        }
        comparisons++;
        while (A[j].getJourneyCode() > jCode && i!=j)
        {
            comparisons++;
            j--;
        }
        if(i<j) swap(A, i, j);
    }
    tree->insert(array[i].getJourneyCode(), array[i].getPrice());
    return i;
}

bool SorterTree::Quicksort(int start, int finish)
{
    int p;
    if (start < finish)
    {
        p = Partition(array, start, finish);
        if(p-1 >= start) Quicksort(start, p-1);
        if(p+1 <= finish) Quicksort(p+1, finish);
        return true;
    }

    else
    {
        return false;
    }
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(start<=finish){
        int p = Partition(array, start, finish);
        if(p-1 >= start) QuicksortWithBSTInsert(start, p-1);
        if(p+1 <= finish) QuicksortWithBSTInsert(p+1, finish);
        return true;
    }
    else{
        return false;
    }

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
}

void SorterTree::printTree(){
    tree->inOrder(tree->getRoot());
}

BST* SorterTree::getTree(){
    return tree;
}

SorterTree::~SorterTree(){}




#endif