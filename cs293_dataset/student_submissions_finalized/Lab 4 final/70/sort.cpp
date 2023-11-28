#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l=l;
}
BST* SorterTree::getTree(){
    return tree;
}
bool SorterTree::insertPivot(int JourneyCode, int Price){
    return tree->insert(JourneyCode, Price);
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(finish-start <= 0) return;
    Journey* pivot;
    switch(choice){
        case 1:
            pivot = choose_one(array, start, finish);
        case 2:
            pivot = choose_two(array, start, finish);
        case 3:
            pivot = choose_three(array, start, finish);
    }
    int saveFin = finish;
    int saveBeg = start;
    int mean = 0;
    for(int i = start; i <= finish; i++){
        mean+=array[i].getJourneyCode();
    }
    mean=mean/(finish+1-start);
    while (true){
        //cout<<"he"<<endl;
        while (array[start] < *pivot && start<(*pivot).getJourneyCode()){
            start++;
        }
        while (*pivot < array[finish] && finish>(*pivot).getJourneyCode()){
            finish--;
        }
        if(start < finish){
            Journey temp = array[start];
            array[start] = array[finish];
            array[finish] = temp;
            //cout<<"h"<<endl;
        }
        else break;
    }
    Quicksort(saveBeg, start);
    Quicksort(start+1, saveFin);
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(finish-start <= 0) return;
    Journey* pivot;
    switch(choice){
        case 1:
            pivot = choose_one(array, start, finish);
        case 2:
            pivot = choose_two(array, start, finish);
        case 3:
            pivot = choose_three(array, start, finish);
    }
    insertPivot(pivot->getJourneyCode(),pivot->getPrice());
    int saveFin = finish;
    int saveBeg = start;
    int mean = 0;
    for(int i = start; i <= finish; i++){
        mean+=array[i].getJourneyCode();
    }
    mean=mean/(finish+1-start);
    while (true){
        //cout<<"he"<<endl;
        while (array[start] < *pivot && start<(*pivot).getJourneyCode()){
            start++;
        }
        while (*pivot < array[finish] && finish>(*pivot).getJourneyCode()){
            finish--;
        }
        if(start < finish){
            Journey temp = array[start];
            array[start] = array[finish];
            array[finish] = temp;
            //cout<<"h"<<endl;
        }
        else break;
    }
    QuicksortWithBSTInsert(saveBeg, start);
    QuicksortWithBSTInsert(start+1, saveFin);
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
