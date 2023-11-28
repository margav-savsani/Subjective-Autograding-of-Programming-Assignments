#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int returnindex(Journey* A, int start, int end){
    //Function to return the index from where the partition is made.
    Journey x = A[end];
    int smaller = start-1;
    int larger = end +1;
    while(true){
        while(A[larger] <  x){
            larger--;
        }
        while(x < A[smaller]){
            smaller++;
        }
        if(smaller<larger){
            swap(A[smaller],A[larger]);
            return larger;
        }
    }
}
bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    int index;
    if(choice == 1){
        index = getindexofjourney(choose_one(array,start,finish));
    }
    if(choice == 2){
        index = getindexofjourney(choose_two(array,start,finish));
    }
    if(choice == 3){
        index = getindexofjourney(choose_three(array,start,finish));
    }
    if(choice == 4){
        index = getindexofjourney(choose_four(array,start,finish));
    }
    swap(array[index],array[finish]); //Exchanging the Array elements.
    if(start < finish){
        int indexofpart= returnindex(array,start,finish);
         Quicksort(start,indexofpart);
         Quicksort(indexofpart+1,finish);
    }
    return true;
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
int main(){
    SorterTree s();
}