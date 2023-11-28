#include "sort.h"
#include<fstream>
#include <iostream>
SorterTree::SorterTree(int choice,int l)
{
    if(l>0)
    {
        array = new Journey[l];   
    }
    else
    {
        array=NULL;
    }
    tree=new BST;
    this->choice=choice;
    this->l=l;
    comparisons=0;
    no_of_journeys=0;
}

void SorterTree::interchange(Journey* A1,Journey* A2)
{
    //interchanging the 2 journeys
    if(A1==A2)
    {
        return;
    }
    int JrnyC,pri;
    JrnyC=A1->JourneyCode;
    pri=A1->price;
    A1->JourneyCode=A2->JourneyCode;
    A1->price=A2->price;
    A2->JourneyCode=JrnyC;
    A2->price=pri;
    return;//copying to local variable and then interchanging
}

bool SorterTree::Quicksort(int start, int finish)
{
    if(start>finish)//error actually
    {
        return true;
    }
    if(start==finish)//if array has only one element
    {
        return true;
    }
    Journey* pivot;
    if(choice==1)//choosing first function
    {
        pivot=choose_one(array,start,finish);
    }
    else if(choice==2)//choosing second function
    {
        pivot=choose_two(array,start,finish);
    }
    else if(choice==3)
    {
        pivot=choose_three(array,start,finish);
    }
    else if(choice==4)
    {
        pivot=choose_four(array,start,finish);
    }
    int pivot_value=pivot->JourneyCode;
    interchange(&array[finish],pivot);
    int i=start;
    int j=finish;
    while(i<j)
    {
        comparisons++;
        while(array[i].JourneyCode < pivot_value)
        {
            i++;
            comparisons++;
        }
        comparisons++;
        while(array[j].JourneyCode > pivot_value)
        {
            comparisons++;
            j--;
        }
        if(i<j)
        {
            interchange(&array[i],&array[j]);
            i++;
            j--;
        }
    }
    bool a;
    if(i==finish)
    {
        a=Quicksort(start,i-1);
        return true;//because in my function, i can't be start 
    }
    else
    {
        a=Quicksort(start,i);
        a=Quicksort(i,finish);
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(start>finish)
    {
        bool z=insertPivot(array[start].JourneyCode,array[start].price);
        return true;
    }
    if(start==finish)
    {
        bool z=insertPivot(array[start].JourneyCode,array[start].price);
        return true;
    }
    Journey* pivot;
    if(choice==1)
    {
        pivot=choose_one(array,start,finish);
    }
    else if(choice==2)
    {
        pivot=choose_two(array,start,finish);
    }
    else if(choice==3)
    {
        pivot=choose_three(array,start,finish);
    }
    else if(choice==4)
    {
        pivot=choose_four(array,start,finish);
    }
    insertPivot(pivot->JourneyCode,pivot->price);
    int pivot_value=pivot->JourneyCode;
    interchange(&array[finish],pivot);
    int i=start;
    int j=finish;
    while(i<j)
    {
        comparisons++;
        while(array[i].JourneyCode < pivot_value)
        {
            i++;
            comparisons++;
        }
        comparisons++;
        while(array[j].JourneyCode > pivot_value)
        {
            comparisons++;
            j--;
        }
        if(i<j)
        {
            interchange(&array[i],&array[j]);
            i++;
            j--;
        }
    }
    bool a;
    if(i==finish)
    {
        a=QuicksortWithBSTInsert(start,i-1);
        a=QuicksortWithBSTInsert(i,finish);//because it may forget to add the finish journey to the tree
    }
    else
    {
        a=QuicksortWithBSTInsert(start,i);//because in my function, i can't be start at the end of function
        a=QuicksortWithBSTInsert(i,finish);
    }
    return true;
}

BST* SorterTree::getTree()
{
    return tree;
}

bool SorterTree::insertPivot(int JourneyCode,int price)
{
    bool a=tree->insert(JourneyCode,price);
    return a;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

bool SorterTree::insertelement(int JourneyCode,int price)
{
    array[no_of_journeys].JourneyCode=JourneyCode;
    array[no_of_journeys].price=price;
    no_of_journeys++;
    return true;
}