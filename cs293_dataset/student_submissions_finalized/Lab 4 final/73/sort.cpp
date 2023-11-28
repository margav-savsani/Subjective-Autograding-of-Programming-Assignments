#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice,int l)
{   //default constructor
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    tree=new BST();
    num=0;
}
int SorterTree::partition(int start,int finish)
{       //code for partition
    Journey *node;      //getting node based on choice
    if (choice==1)
        node=choose_one(array,start,finish);
    if (choice==2)
        node=choose_two(array,start,finish);
    if (choice==3)
        node=choose_three(array,start,finish);
    int fh=start;   //starting from start
    int lh=finish;  //end will be length-1
    //tree->insert(node->getJourneyCode(),node->getPrice());
    while(true)
    {
        while(!(array[lh] <= *node))    //decr the lh until we found element <= node
        {
            lh--;
            comparisons++;  //comparitions decr
        }
        comparisons++;  //we missed the last comparition in above loop
        while(!(*node <= array[fh]))    //checking lower half to havae element >= node
        {
            fh++;
            comparisons++;
        }
        comparisons++;
        if (fh<lh)  //exchanging the elements
        {
            Journey dummy;
            dummy=(array[lh]);
            array[lh]=array[fh];
            array[fh]=dummy;
        }
        else       //completed the partition
            return lh;
    }
    return lh;
}
bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start > finish)
        return false;
    if (start < finish)
    {
        int pivot;
        //tree->insert(node->getJourneyCode(),node->getPrice());
        pivot=partition(start,finish);
        if (pivot<finish)   //code for quick sort
        {
            //tree->insert(node->getJourneyCode(),node->getPrice());
            QuicksortWithBSTInsert(start , pivot);
            QuicksortWithBSTInsert(pivot+1,finish);
        }
        else    //for pivot==finish
        {
            //tree->insert(node->getJourneyCode(),node->getPrice());
            QuicksortWithBSTInsert(start , pivot-1);
            QuicksortWithBSTInsert(pivot,finish);
        }
    }
    if (start==finish)
    {
        //tree->insert(node->getJourneyCode(),node->getPrice());
        int pivot=partition(start,finish);
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    Journey *node;  //choice for pivot
    if (choice==1)
        node=choose_one(array,start,finish);
    if (choice==2)
        node=choose_two(array,start,finish);
    if (choice==3)
        node=choose_three(array,start,finish);
    //cout<<"I am here"<<endl;
    if (start > finish)
        return false;
    if (start < finish)
    {
        int pivot;
        tree->insert(node->getJourneyCode(),node->getPrice());
        pivot=partition(start,finish);
        if (pivot<finish)   //code for quick sort
        {
            //tree->insert(node->getJourneyCode(),node->getPrice());
            QuicksortWithBSTInsert(start , pivot);
            QuicksortWithBSTInsert(pivot+1,finish);
        }
        else    //for pivot==finish
        {
            //tree->insert(node->getJourneyCode(),node->getPrice());
            QuicksortWithBSTInsert(start , pivot-1);
            QuicksortWithBSTInsert(pivot,finish);
        }
    }
    if (start==finish)
    {
        tree->insert(node->getJourneyCode(),node->getPrice());
        int pivot=partition(start,finish);
    }
    return true;
}

bool SorterTree::printArray() //printing the elements
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    tree->printBST("");
    return true;
}
bool SorterTree::printComparisons() //printing the number of comparitions
{
    std::cout<<"No of comparisons: "<<comparisons<<std::endl;
    return true;
}

bool SorterTree::makearray(int JourneyCode,int price)
{
    Journey *node=new Journey(JourneyCode,price);   //to add the elements to array
    for (int i=0;i<num;i++)
        if (*node == array[i])
        {
            comparisons++;  //== comparition
            return false;
        }
    num++;
    array[num-1]=*node;
    return true;
}
bool SorterTree::insertPivot(int JourneyCode,int price)
{
    if (!(tree->find(JourneyCode,price)))
        return false;
    tree->insert(JourneyCode,price); //inserting the pivot
    return true;
}