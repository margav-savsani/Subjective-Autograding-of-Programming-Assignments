#include "sort.h"
#include <iostream>


// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
        if (start < finish) {
        // pi is partitioning index, 
        // arr[p] is now at right place
        partition_r(array,start,finish);
        int pi = partition(array, start, finish);
  
        // Separately sort elements before
        // partition and after partition
        SorterTree::Quicksort( start, pi);
        SorterTree::Quicksort( pi + 1, finish);
    }
    return 1;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish,Journey arr[])
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if (start < finish){
       Journey* pivot=partition_r(arr,start,finish);
tree->insert(pivot->getJourneyCode(),pivot->getPrice());
int pi = partition(arr, start, finish);
cout<<"3"<<endl;
SorterTree::QuicksortWithBSTInsert(start,pi,arr);
SorterTree::QuicksortWithBSTInsert(pi+1,finish,arr);
}
    return 1;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return 1;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
tree->insert(JourneyCode,price);
return 1;
}
 int SorterTree::partition(Journey arr[], int low, int high)
{
    Journey pivot = arr[low];
    int i = low - 1, j = high + 1;
  
    while (true) {
  
        // Find leftmost element greater than
        // or equal to pivot
        while (arr[i] < pivot){
            i++;
            comparisons++;
        }
  
        // Find rightmost element smaller than
        // or equal to pivot
        while (arr[j] > pivot) {
            j--;
            comparisons++;
        } 
  
        // If two pointers met
        if (i >= j)
            return j;
  
        swap(arr[i], arr[j]);
    }
    }
    Journey* SorterTree::partition_r(Journey A[], int low, int high)
{
    // Generate a random number in between
    // low .. high
    Journey* p;
    if(choice==1){
p= choose_one(A,low, high);}
if(choice==2){
p= choose_two(A,low, high);}
if(choice==3){
p= choose_three(A,low, high);}
swap(*p,A[low]);
return &A[low];
}
