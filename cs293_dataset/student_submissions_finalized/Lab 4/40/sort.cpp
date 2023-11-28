#include "updated_sort.h"
#include <iostream>
#include <cstdlib>                                         //must to use rand()


// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{                                                               //we have array[N]
    int i = start - 1;                                          //these are our variable which are going to run through the loop
    int j = finish + 1;
    choice = rand()%4 + 1;                                  //this reflects the choice of function ot be used
    Journey* pivot;                                             //pivot 
    switch (choice) {                                           //initialising pivot based on output of rand()
        case 1:                                                 //use of switch to make life easy
        pivot = choose_one(array,start,finish);
        break;
        case 2:
        pivot = choose_two(array,start,finish);
        break;
        case 3:
        pivot = choose_three(array,start,finish);
        break;
        case 4:
        pivot = choose_four(array,start,finish);
        break;
    }
    while(true){                                    //basically incrementing and decrementing till the array is sorted about the partition
        while(array[j] > pivot){                    //implementation based on naveen sir's lecture
            j--;                            
        }
        while(array[i] < pivot){
            i++;
        }
        if(array[i] < array[j]){
            Journey* alpha = array[i];
            arraj[i] = arraj[j];
            arraj[j] = alpha;
        }
    }
    Quicksort(start,j);               //recursively sorting
    Quicksort(j+1,finish);            //recursively sorting
    return true;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    choice = rand()%4 + 1;                                  //this reflects the choice of function ot be used
    Journey* pivot;                                             //pivot 
    switch (choice) {                                           //initialising pivot based on output of rand()
        case 1:
        pivot = choose_one(array,start,finish);
        break;
        case 2:
        pivot = choose_two(array,start,finish);
        break;
        case 3:
        pivot = choose_three(array,start,finish);
        break;
        case 4:
        pivot = choose_four(array,start,finish);
        break;
    }
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriatelj
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
