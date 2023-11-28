#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int SorterTree::Partition(Journey* array,int start,int finish){
    int i,j;
    i=start;
    j=finish;
    Journey *x;
    if(choice==1){
        x=choose_one(array,start,finish);
    }
    else if(choice==2){
        x=choose_two(array,start,finish);
    }
    else if(choice==3){
        x=choose_three(array,start,finish);
    }
    if(n==1){
    //QuicksortWithBSTInsert(x->getJourneyCode(),x->getPrice());
    tree->insert(x->getJourneyCode(),x->getPrice());
    }
    while(true){
        while(*x<array[j]){
            j=j-1;
            comparisons++;
        }
        comparisons++;
        while(array[i]<*x){
            i=i+1;
            comparisons++;
        }
        comparisons++;
        if(i<j){
            Journey c=array[i];
            array[i]=array[j];
            array[j]=c;
        }
        else{
            return j;
        }
    }
}/*
int SorterTree::Partition1(Journey* array,int start,int finish){
    int i,j;
    i=start;
    j=finish;
    Journey *x;
    if(choice==1){
        x=choose_one(array,start,finish);
        tree->insert(x->getJourneyCode(),x->getPrice());
    }
    else if(choice==2){
        x=choose_two(array,start,finish);
        tree->insert(x->getJourneyCode(),x->getPrice());
    }
    else if(choice==3){
        x=choose_three(array,start,finish);
        tree->insert(x->getJourneyCode(),x->getPrice());
    }
    while(true){
        while(*x<array[j]){
            j=j-1;
            comparisons++;
        }
        comparisons++;
        while(array[i]<*x){
            i=i+1;
            comparisons++;
        }
        comparisons++;
        if(i<j){
            Journey c=array[i];
            array[i]=array[j];
            array[j]=c;
        }
        else{
            return j;
        }
    }
}
*/
bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    int q;
    q=Partition(array,start,finish);
    if(start<finish){
        if(q!=finish){
            Quicksort(start,q);
            Quicksort(q+1,finish);
            return true;
        }
        else{
            q=q-1;
            Quicksort(start,q);
            Quicksort(q+1,finish);
            return true;
        }}
    else{
        return false;
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    //tree->insert(start,finish);
    /*
    int q;
    q=Partition(array,start,finish);
    //tree->insert(array[q].getJourneyCode(),array[q].getPrice());
    if(start<finish){
        if(q!=finish){
            //tree->insert(array[q].getJourneyCode(),array[q].getPrice());
            QuicksortWithBSTInsert(start,q);
            QuicksortWithBSTInsert(q+1,finish);
        }
        else{
            q=q-1;
            QuicksortWithBSTInsert(start,q);
            QuicksortWithBSTInsert(q+1,finish);
        }}*/
    n=1;
    int q;
    q=Partition(array,start,finish);
    n=0;
    if(start<finish){
        if(q!=finish){
            QuicksortWithBSTInsert(start,q);
            QuicksortWithBSTInsert(q+1,finish);
            return true;
        }
        else{
            q=q-1;
            QuicksortWithBSTInsert(start,q);
            QuicksortWithBSTInsert(q+1,finish);
            return true;
        }}
    else{
        return false;
    }
    return true;
    
}
bool SorterTree::printArray()
{
    for (int i=0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    tree->printBST(" ");
    cout<<tree->getImbalance()<<endl;
    return true;
}
