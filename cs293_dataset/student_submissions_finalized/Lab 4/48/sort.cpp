#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice,int l){
    choice=choice;
    l=l;
    array=new Journey[l];
    for(int i=0;i<l;i++){
        unsigned int c,p;
        cin>>c>>p;
        array[i] = *(new Journey(c,p));
    }
    comparisons=0;
}
int SorterTree::partition(Journey arr[],int low,int high){
    Journey* pivot;
    if(choice==1) pivot = choose_one(arr,low, high);
    if(choice==2) pivot = choose_two(arr,low, high);
    if(choice==3) pivot = choose_three(arr,low, high);
    if(choice==4) pivot = choose_four(arr,low, high);
    swap(*pivot,arr[high]);
    int j=low-1;
    for(int i=low;i<=high-1;i++){
        if(arr[i] < *pivot){
            comparisons++;
            j++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[j+1],arr[high]);
    return j+1;
}
bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start<finish){
        int q=partition(array,start,finish);
        Quicksort(start,q-1);
        Quicksort(q+1,finish);
        return true;
    }
    return false;
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
