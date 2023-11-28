#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey*p;
    if(choice==1){
        p=choose_one(array,  start, finish);

    }
    if(choice==2){
        p=choose_two(array,  start, finish);
    }
    if(choice==3){
        p=choose_three(array,  start, finish);
    }
    if(choice==4){
        p=choose_four(array,  start, finish);
    }
    if (start < finish)  

    {  

        /* pi is partitioning index, arr[p] is now  

        at right place */

        int pi = partition(p, start, finish);  

  

        // Separately sort elements before  

        // partition and after partition  

        Quicksort( start, pi );  

        Quicksort( pi + 1, finish);  

    }
}
int SorterTree::partition(Journey* p,int low,int high){
    int i= low ; int j =high ;
    while(true){
        while(*p < array[j]){j=j-1;}
        while(array[i]< *p){i=i+1;}
        if (i<j){Journey k1 =array[i];Journey k2 =array[j];
        array[i]=k2;array[j]=k1;}
        else return j;
    }
}
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
