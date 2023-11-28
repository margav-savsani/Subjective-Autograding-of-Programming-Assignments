#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp

Journey *SorterTree::getPivot(int start, int finish) const{
    switch (choice)
    {
        case 1: return choose_one(array, start, finish);
        case 2: return choose_two(array, start, finish);
        case 3: return choose_three(array, start, finish);
        case 4: return choose_four(array, start, finish);
        default: return nullptr;
    }
}

void swap(Journey &a, Journey &b){
    const Journey tmp = a;
    a = b;
    b = tmp;
}

int partition(Journey *array, Journey *pivot, int start, int finish){
    // while(true){
    //     // leave alone entries that are already on the right side of the partition.
    //     while(array[start] < *pivot) start++;
    //     while(!(array[finish] < *pivot)) finish--; // while(*finish >= *pivot) essentially.
    //     if (start >= finish) return ;

    //     std::cout << array[start].getJourneyCode() << std::endl;
    //     std::cout << array[finish].getJourneyCode() << std::endl;
    //     // swap the entries that are on opposite sides of the partition. 
    //     Journey const tmp = array[start];
    //     array[start] = array[finish];
    //     array[finish] = tmp;
    // }

    swap(*pivot, array[finish]); // get pivot to be the last element.
    Journey x = array[finish];

    int i = start-1; // it is just behind the "wall == the first element >= pivot"
    // run through each element of the subarray in order
    for (int j = start; j < finish; j++){
        if (array[j] < x){
            swap(array[j], array[i+1]); // array[i+1] is the wall ie >= pivot. swap it with array[j] < pivot.
            i++; // move i forward.
        }
    }
    swap(array[i+1], array[finish]); // finally get array[finish] = pivot before all the elements >= pivot.
    return i + 1; // the final location of the pivot.
}

bool SorterTree::Quicksort(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start >= finish) return true;

    Journey *pivot = getPivot(start, finish);
    std::cout << pivot->getJourneyCode() << " " << pivot->getPrice() << std::endl;
    int pivot_updated = partition(array, pivot, start, finish);
    printArray();
    Quicksort(start, pivot_updated - 1);
    Quicksort(pivot_updated + 1, finish);
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
    for (int i = 0; i < l; i++){
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price: "<<array[i].getPrice()<<std::endl;
    }
}

void SorterTree::load(std::ifstream &in){
    array = new Journey[l];
    for (int i = 0; i < l; i++){
        unsigned int journeyCode, journeyPrice;
        in >> journeyCode >> journeyPrice;
        array[i] = Journey(journeyCode, journeyPrice);
    }
}
