#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int SorterTree::Journey_ins(int JourneyCode, int price, int index)
{
    Journey a(JourneyCode, price);
    array[index] = a;
    return index + 1;
}
SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    comparisons = 0;
    tree = new BST();
}
int SorterTree::randompartition(int start, int finish)
{   if (start>finish) return -1;
    Journey *p;
    if (choice == 1)
    {
        p = choose_one(array, start, finish);
    }

    if (choice == 2)
    {
        p = choose_two(array, start, finish);
    }

    if (choice == 3)
    {
        p = choose_three(array, start, finish);
    }

    Journey t = array[finish];
    array[finish] = *p;
    *p = t;
    return Partition(start, finish);
}

int SorterTree::Partition(int start, int finish)
{
    Journey x = array[finish];
    int i = start;
    int j = finish;
    while (true)
    {
        while (x < array[j])
        {
            j = j - 1;
            comparisons++;
        }
        while (array[i] < x)
        {
            i = i + 1;
            comparisons++;
        }
        if (i < j)
        {
            Journey temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }

        else return j;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    if (start < finish)
    {
        int q= randompartition(start, finish);
        if (q==finish){Quicksort(start,q-1); return true;}
        Quicksort(start, q);
        Quicksort(q + 1, finish);
        return true;
    }
    else return false;
    
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{ 
    int q;
    if (start<finish)
    {
        q = randompartition(start, finish);
        if (q==finish){QuicksortWithBSTInsert(start, q-1); return true;}
        QuicksortWithBSTInsert(start, q); 
        QuicksortWithBSTInsert(q + 1, finish); 
        if (start<=q && q<=finish){
            Journey pivot=array[q];
            tree->insert(pivot.getJourneyCode(),pivot.getPrice());
        }
        return true;
    }
    else return false;
}

 BST* SorterTree::getTree(){return tree;}
 void SorterTree::pastetree()
 {  
    tree->printBST("");
    return;
 }

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
}
int SorterTree::imbalance(){
    return tree->imbalance();
}