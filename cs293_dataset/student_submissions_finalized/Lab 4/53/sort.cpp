#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice,int l){
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    comparisons=0;
}


bool SorterTree::Quicksort(int start, int finish)
{   
    if(start<finish){
        Journey* pivot;
        if (choice == 1) pivot = choose_one(array,)
        else if (choice == 2) pivot = choose_two()
        else if (choice == 3) pivot = choose_three()
        else pivot = choose_four()

        int left = start-1;
        int right = finish +1;
        int x;
        while true{
            do
            {
                right--;
            } while (
                A[right]<=x;
            )
            do
            {
                left++;
            } while (
                A[left] >=x;
            )
            if (left < right){
                journey temp;
                temp = A[left];
                A[left] = A[right];
                A[right] = temp;
            }
            else {
                x = right;
                break;
            }
        }
            Quicksort(array,start,x);
            Quicksort(array,x+1,finish);
            return true;
    }
    return false;





    left = start-1;
    

    return true;
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
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
