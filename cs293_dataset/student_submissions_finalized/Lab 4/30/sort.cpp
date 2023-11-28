#include "sort.h
"#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int ch, int len){
    choice = ch;
    l = len;
}


bool SorterTree::Quicksort(int start, int finish)
{
    //ensure start and finish are within their possible bounds
    if((start >= 0)&&(finish <= l-1)&&(start <= finish)){           

    int piv;
    
    // Call appropriate pivot function based on choice
    if(choice == 1){
        piv = choose_one(array, start, finish);
    }
    else if(choice == 2){
        piv = choose_two(array, start, finish);
    }
    else if(choice == 3){
        piv = choose_three(array, start, finish);
    }
    else if(choice == 4){
        piv = choose_four(array, start, finish);
    }

    // Split into 2 parts based on pivot choice
    partition(array, start, finish){
        Journey* pivot = array[piv];
        int i= start - 1;
        for(int j = start; j<=high; j++){
            if(array[j] < pivot){
                
            }
        }
    }
    // Recursively keep sorting
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
