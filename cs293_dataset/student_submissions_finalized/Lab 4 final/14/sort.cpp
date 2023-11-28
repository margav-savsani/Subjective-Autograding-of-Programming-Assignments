#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    tree = new BST();
    comparisons = 0;

    //to initialize taking inputs
    int w=0;
    while(w<l)
    {
        int code, journeyprice;
        cin >> code >> journeyprice;
        Journey jrny(code,journeyprice);
        array[w] = jrny;
        w++;
    }
}

int SorterTree::Partition(int start, int finish)
{
    Journey* x = new Journey(); // x is pivot

    switch(choice)
    {
        case 1:x = choose_one(array,start,finish);break;
        case 2:x = choose_two(array,start,finish);break;
        case 3:x = choose_three(array,start,finish);break;
        //case 4:x = choose_four(array,start,finish);break;
        //choose_four function is declared but not defined in the
        //code provided
        default:x = NULL;break;
    }

    if (x == nullptr) return 0;
    //exits gracefully

    int i = start, di;
    bool done = false;

    for (int j = start; j <= finish; j++)
    {
        if (array[j] < *x) {i++; comparisons++;}
        else if (array[j].getJourneyCode() == x->getJourneyCode() && 
                 array[j].getPrice() == x->getPrice()) 
        {
            di = j;
            done = true;
        }
    }

    if (!done) return -1;

    swap(array[i], array[di]);

    int s = start, f = finish;
    while (s < i && f > i)
    {
        while (array[s] < array[i]){s++;comparisons++;}
        while (array[i] < array[f]){f--;comparisons++;}
        if (s < i && i < f)
        {
            swap(array[s], array[f]);
            s++; f--;
        }
    }
    return i;
    
}
    

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    if(start > finish) return false;
    int q = Partition(start,finish);
    tree->insert(array[q].getJourneyCode(),array[q].getPrice());
    Quicksort(start,q-1);
    Quicksort(q+1,finish);
    return true;

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    Quicksort(start,finish);
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

BST* SorterTree::getTree()
{
  tree->printBST("",false);
  return NULL;
}

int SorterTree::getImbatroot()
{
    return tree->getImbalance();
}

