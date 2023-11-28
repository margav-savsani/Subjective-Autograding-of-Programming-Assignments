#include "sort.h"
#include <iostream>

//partition
int SorterTree::partition (Journey* arr, int low, int high ,Journey pivot) 
{  
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
    for (int j = low; j <= high - 1; j++) 
    { 
        comparisons++;
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 

            i++; // increment index of smaller element 
            Journey swap=arr[i];
            arr[i]=arr[j];
            arr[j]=swap;
        } 
    } 
    Journey swap=arr[high];
    arr[high]=arr[i+1];
    arr[i+1]=swap;  
    return (i + 1); 
} 
  
// Code up the functions defined in sort.cpp
bool SorterTree::Quicksort(int start, int finish)
{
    if (start < finish)
    {
        Journey *pivot;
        if (choice == 1)
        {
            pivot = choose_one(array, start, finish);
        }
        else if (choice == 2)
        {
            pivot = choose_two(array, start, finish);
        }
        else if (choice == 3)
        {
            pivot = choose_three(array, start, finish);
        }
        
        Journey x = *pivot;
        for (int i=0;i<l;i++) {
            if (array[i] == x) {
                Journey swap=array[i];
                array[i]=array[finish];
                array[finish]=swap;
                break;
            }
        }
        int p=partition(array,start,finish,array[finish]);
        
        Quicksort(start, p-1);
        Quicksort(p+1, finish);
        return true;
    }
    else return false;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if (start < finish)
    {
        Journey *pivot;
        if (choice == 1)
        {
            pivot = choose_one(array, start, finish);
        }
        else if (choice == 2)
        {
            pivot = choose_two(array, start, finish);
        }
        else if (choice == 3)
        {
            pivot = choose_three(array, start, finish);
        }
        
        Journey x = *pivot;
        tree->insert(x.getJourneyCode(),x.getPrice());
        for (int i=0;i<l;i++) {
            if (array[i] == x) {
                Journey swap=array[i];
                array[i]=array[finish];
                array[finish]=swap;
                break;
            }
        }
        int p=partition(array,start,finish,array[finish]);
        
        Quicksort(start, p-1);
        Quicksort(p+1, finish);
        return true;
    }
    else return false;
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
}

void SorterTree::insertjourney(int JourneyCode, int price) {
    Journey j(JourneyCode,price);
    array[i]=j;
    i++;
}
