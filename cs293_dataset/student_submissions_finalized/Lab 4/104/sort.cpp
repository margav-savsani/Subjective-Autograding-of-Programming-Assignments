#include "sort.h"
#include "choose.h"
#include <iostream>

SorterTree::SorterTree(int choice, int l){
    // this->l = l;
    // this->choice = choice;
    // this->comparisons = 0;

    // array = new Journey[l];


    // for(int i=0; i<l; ++i){
    //     int jc;
    //     int prc;
    //     std::cin >> jc >> prc;
    //     array[i].setJourneyCode(jc);
    //     array[i].setPrice(prc);
    // }

    //tree = new BST;
}

// Code up the functions defined in sort.cpp

// int SorterTree::partition(int start, int finish){
//     Journey x = array[finish];
//     int i = start-1;
//     int j = finish+1;

//     while(true){
//         do{
//             j = j-1;
//             comparisons++;
//         }
//         while(array[j] < x);

//         do{
//             i = i+1;
//             comparisons++;
//         }
//         while(array[i] > x);

//         if(i<j){
//             Journey temp = array[i];
//             array[i] = array[j];
//             array[j] = temp;
//         }
//         else{
//             return j;
//         }
//     }
// }

//  int SorterTree::newPartition(int start, int finish){
//     Journey *i;
//     if(choice == 1){
//         i = choose_one(array, start, finish);
//     }
//     if(choice == 2){
//         i = choose_two(array, start, finish);
//     }
//     if(choice == 3){
//         i = choose_three(array, start, finish);
//     }
//     if(choice == 4){
//         i = choose_four(array, start, finish);
//     }

//     Journey temp = *i;
//     *i = array[finish];
//     array[finish] = temp;

//     return partition(start, finish);
//  }

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    // if(start < finish){
    //     int q = newPartition(start, finish);
    //     Quicksort(start, q);
    //     Quicksort(q+1, finish);
    // }
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