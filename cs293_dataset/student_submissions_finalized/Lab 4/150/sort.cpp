#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
Sortertree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
}

bool SorterTree::Quicksort(int start, int finish)
{  
    Journey* mypivot ;
    if (choice == 1){
        mypivot = choice_one(array,start,finish);
    }
    else if (choice == 2){
        mypivot = choice_two(array,start,finish);
    }
    else if (choice == 3){
        mypivot = choice_three(array,start,finish);
    }
    else if (choice == 4){
        mypivot = choice_four(array,start,finish);
    }
   
    inr i=0;
    int j=0;
    for (int i=start,j=start;i<final;i++){
       if (array[i] > choice) {
          i++;
       }
       else
       if (array[i] < choice) {
          swap( array[i], array[j]);
       }




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
