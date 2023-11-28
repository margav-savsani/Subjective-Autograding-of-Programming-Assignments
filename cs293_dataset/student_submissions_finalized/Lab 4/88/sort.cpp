#include "sort.h"
#include "choose.h"
#include <iostream>

using namespace std;

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    if(start >= finish) return 1;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey *pivot;
    if(choice==1){
        pivot = choose_one(array, start, finish);
    }
    else if(choice==2){
        pivot = choose_two(array, start, finish);
    }
    else if(choice==3){
        pivot = choose_three(array, start, finish);
    }
    else if(choice==4){
        pivot = choose_four(array, start, finish);
    }
    cout << "chose pivot " << pivot->getJourneyCode() << endl;
    printArray();
    int curr=start-1;
    for(int i=0; i<l; i++){
        if (array[i] < *pivot){
            curr++;
            myswap(curr,i);
        }
        comparisons++;
    }
    printArray();
    return 1;
    Quicksort(start, curr);
    Quicksort(curr+1,finish);
    return 1;
}

void SorterTree::myswap(int idx1, int idx2){
    Journey temp = array[idx1];
    array[idx1] = array[idx2];
    array[idx2] = temp;
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

SorterTree::SorterTree(int choice, int l){
    comparisons = 0;
    SorterTree::l = l;
    SorterTree::choice = choice;
    array = new Journey[l];
    int code,price;
    for(int i=0; i<l; i++){
        std::cin>>code>>price;
        array[i]=Journey(code,price);
    }
}