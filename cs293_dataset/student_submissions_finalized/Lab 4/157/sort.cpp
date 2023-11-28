#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
int SorterTree::Partition(Journey *arr,int low, int high, Journey *pivotloc){
    int i = low;
    int j = high;
    Journey pivot1 = *pivotloc;
    while (i < j) {
        while (arr[i]<pivot1)
            i++;
        while (pivot1 < arr[j])
            j--;
        if (i < j){
            Journey temp=arr[j];
            arr[j]=arr[i];
            arr[i]=temp;
        }
    }
    Journey temp=arr[j];
    arr[j]=pivot1;
    *pivotloc=temp;
    return j;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey *pivot;

    if(choice==1){pivot=choose_one(array,start, finish);}
    else if (choice==2){pivot=choose_two(array,start, finish);}
    else if (choice==3){pivot=choose_three(array,start, finish);}
    else{pivot=choose_four(array,start, finish);}

    if(start < finish){
        int pivotind=Partition(array,start,finish,pivot);
        Quicksort(start, pivotind - 1);
        Quicksort(pivotind + 1, finish);
    }
    return 1;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    Journey *pivot;

    if(choice==1){pivot=choose_one(array,start, finish);}
    else if (choice==2){pivot=choose_two(array,start, finish);}
    else if (choice==3){pivot=choose_three(array,start, finish);}
    else{pivot=choose_four(array,start, finish);}
    
    if(start < finish){
        int pivotind=Partition(array,start,finish,pivot);
        QuicksortWithBSTInsert(start, pivotind - 1);
        QuicksortWithBSTInsert(pivotind + 1, finish);
    }
    return 1;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
