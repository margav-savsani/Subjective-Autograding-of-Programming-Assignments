#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l,Journey* array)
{
    this->choice = choice;
    this->l=l;
    this->array=array;
    // array = new Journey[l];
    comparisons=0;
    tree = new BST();
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    quicksort(array,start,finish);
    return true;
}

void SorterTree::quicksort(Journey* arr,int start,int end)
{
    if(start<end)
    {
            int partition_index =partition(arr,start,end);
            partition(arr,start,partition_index-1);
            partition(arr,partition_index+1,end);
    }
    else
    {
        return;
    }

}

Journey* SorterTree::choose(Journey* arr,int start,int end)
{
    return &arr[end];
}

int SorterTree::partition(Journey* arr,int start,int end)
{
    Journey* pivot = choose(arr,start,end);
    int pivot_index;
    for(int i=start;i<end+1;i++)
    {
        if(pivot->getJourneyCode()==arr[i].getJourneyCode())
        {
            pivot_index=i;
            break;
        }
        else
        {
            continue;
        }
    }
    swap(arr,pivot_index,end);
    int i=start;
    int j=end-1;
    while(i<j)
    {
        while(arr[end] < arr[i] && i<end+1)
        {
            i++;
        }
        while(arr[j]<arr[end] && j>start-1)
        {
            j--;
        }
        if(i<j)
        {
            swap(arr,i,j);
        }
    }
    swap(arr,i,end);
    return pivot_index;
}

void SorterTree::swap(Journey* arr,int i,int j)
{
    Journey temp;
    temp = arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    int pivot_index=partition(array,start,finish);
    tree->insert(array[pivot_index].getJourneyCode(),array[pivot_index].getPrice());
    QuicksortWithBSTInsert(start,pivot_index-1);
    QuicksortWithBSTInsert(pivot_index+1,finish);
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

// bool SorterTree::insertPivot(int JourneyCode, int price)
// {

// }

// BST* SorterTree::getTree()
// {

// }
