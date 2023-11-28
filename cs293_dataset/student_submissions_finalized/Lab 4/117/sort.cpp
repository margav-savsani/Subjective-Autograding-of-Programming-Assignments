#include "sort.h"
#include "choose.h"
#include <iostream>

using namespace std;




// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    comparisons = 0;
    array = new Journey[l];
    for(int i = 0; i < l; i++){
        int JourneyCode, price;
        cin >> JourneyCode >> price;
        Journey* newJourney = new Journey(JourneyCode, price);
        array[i].store(newJourney);
        delete(newJourney);
    }
}

//start and finish are array index, therefore we start with start=0 and finish = l-1
bool SorterTree::Quicksort(int start, int finish){
    // Call appropriate pivot function based on choice
    Journey* pivot;
    if(choice == 1) pivot = choose_one(array, start, finish);
    else if(choice == 2) pivot = choose_two(array, start, finish);
    else if(choice == 3) pivot = choose_three(array, start, finish);
    else pivot = choose_four(array, start, finish);
    int i = start, j = finish;


    // Split into 2 parts based on pivot choice
    if(start == finish || start == finish +1) return true;
    if(start > finish+1) return false;
    while(i < j){
        while(array[i]<*pivot){
            comparisons++;
            i++;
        }
        while(*pivot< array[j]){
            comparisons++;
            j--;
        }
        if(i == j) break;
        Journey temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    // Recursively keep sorting
    return (Quicksort(start, i-1) && Quicksort(j+1, finish));
    
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray(){
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    cout << comparisons << "\n";
    return true;
}


SorterTree::~SorterTree(){};