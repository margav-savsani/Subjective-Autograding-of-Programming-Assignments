#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    array = new Journey[l];
    this->l = l;
    this->choice = choice;
    tree = new BST();
    elements=0;
    comparisons=0;
}
bool SorterTree::Quicksort(int start, int finish)
{
    Journey* pivot;
    if(start>=finish) return true;
    if(choice==1) pivot = new Journey(choose_one(array, start, finish)->getJourneyCode(),choose_one(array, start, finish)->getPrice());
    else if(choice==2) pivot = new Journey(choose_two(array, start, finish)->getJourneyCode(),choose_two(array, start, finish)->getPrice());
    else if(choice==3) pivot = new Journey(choose_three(array, start, finish)->getJourneyCode(),choose_three(array, start, finish)->getPrice());
    int left = start;
    int right = finish;
    while(true){
        comparisons+=2;
        while(array[left] < *pivot){comparisons++; left++;}
        while(*pivot < array[right]){comparisons++; right--;}
        if(left<right){
            Journey temp=array[left];
            array[left]=array[right];
            array[right]=temp;
        }
        else{
            break;
        }
    }
    if(left==right){
        QuicksortWithBSTInsert(start,right-1);
        QuicksortWithBSTInsert(right+1,finish);
    }
    else{
        QuicksortWithBSTInsert(start,right);
        QuicksortWithBSTInsert(left,finish);
    }
    delete pivot;
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    Journey* pivot;
    if(start>=finish) return true;
    if(choice==1) pivot = new Journey(choose_one(array, start, finish)->getJourneyCode(),choose_one(array, start, finish)->getPrice());
    else if(choice==2) pivot = new Journey(choose_two(array, start, finish)->getJourneyCode(),choose_two(array, start, finish)->getPrice());
    else if(choice==3) pivot = new Journey(choose_three(array, start, finish)->getJourneyCode(),choose_three(array, start, finish)->getPrice());
    tree->insert(pivot->getJourneyCode(),pivot->getPrice());
    int left = start;
    int right = finish;
    while(true){
        comparisons+=2;
        while(array[left] < *pivot){comparisons++; left++;}
        while(*pivot < array[right]){comparisons++; right--;}
        if(left<right){
            Journey temp=array[left];
            array[left]=array[right];
            array[right]=temp;
        }
        else{
            break;
        }
    }
    if(left==right){
        QuicksortWithBSTInsert(start,right-1);
        QuicksortWithBSTInsert(right+1,finish);
    }
    else{
        QuicksortWithBSTInsert(start,right);
        QuicksortWithBSTInsert(left,finish);
    }
    delete pivot;
    return true;
}
void SorterTree::printCost(){
    std::cout << comparisons << std::endl;
}
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
       std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    Journey new_journey(JourneyCode,price);
    array[elements] = new_journey;
    elements++;
    return true;
}

BST* SorterTree::getTree(){
    return tree;
}