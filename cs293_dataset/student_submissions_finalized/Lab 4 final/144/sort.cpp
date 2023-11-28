#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    this->tree = new BST();
    this->comparisons = 0;
    array = new Journey[l];
    for(int i = 0; i < l; i++){
        unsigned int journeyCode, price;
        std::cin >> journeyCode >> price;
        array[i] = Journey(journeyCode, price);
    }

}

SorterTree::~SorterTree(){
    delete[] array;
    delete tree;
}

void myswap(Journey* journey1, Journey* journey2){
    Journey temp = *journey1;
    *journey1 = *journey2;
    *journey2 = temp;
}

int SorterTree::Partition(int start, int end,  Journey* pivot){
    if(start < end){
        //Replace pivot with last element
        myswap(pivot, &array[end]);
        //i + 1 represents position of pivot 
        int i = start - 1;

        for(int j = start; j < end; j++){
            //If element is less than pivot, swap it with array[i+1]
            if(array[j] < array[end]){
                i++;
                myswap(&array[j], &array[i]);
            }
            comparisons++;
        }
        //Swapping last element with i+1th element
        myswap(&array[i+1], &array[end]);
        return i + 1;
    }

    else return -1;
}

bool SorterTree::Quicksort(int start, int finish)
{
    if(start < finish){
        Journey* pivot;
        switch (choice)
        {
        case 1:
            {
                pivot = choose_one(array, start, finish);
                break;
            }
        case 2:
            {
                pivot = choose_two(array, start, finish);
                break;
            }
        case 3:
            {
                pivot = choose_three(array, start, finish);
                break;
            }
        
        default:
            break;
        }
        //Checking if pivot is inside array
        bool found = false;
        for(int i = start; i <= finish; i++){
            if (pivot == &array[i]){
                found = true;
                break;
            }
        }

        if(!found){
            std::cout << "Pivot outside array! Choosing last element as pivot" << std::endl;

            pivot = &array[finish];
        }
        int index = Partition(start, finish, pivot); //Partitioning 
        Quicksort(start, index - 1); //Recursive calls
        Quicksort(index + 1, finish);
    }

    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(start < finish){
        Journey* pivot;
        switch (choice)
        {
        case 1:
            {
                pivot = choose_one(array, start, finish);
                break;
            }
        case 2:
            {
                pivot = choose_two(array, start, finish);
                break;
            }
        case 3:
            {
                pivot = choose_three(array, start, finish);
                break;
            }
        
        default:
            break;
        }

        bool found = false;
        for(int i = start; i <= finish; i++){
            if (pivot == &array[i]){
                found = true;
                break;
            }
        }

        if(!found){
            std::cout << "Pivot outside array! Choosing last element as pivot" << std::endl;

            pivot = &array[finish];
        }

        tree->insert(pivot->getJourneyCode(), pivot->getPrice());
        
        int index = Partition(start, finish, pivot);
        QuicksortWithBSTInsert(start, index - 1);
        QuicksortWithBSTInsert(index + 1, finish);
    }

    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }

    return true;
}

void SorterTree::printComparisions(){
    std::cout << "Total Comparisions: " << comparisons << std::endl;
}

void SorterTree::printTree(){
    tree->printBST("");
}

void SorterTree::printImbalance(){
    std::cout << "Imabalance in tree: " << tree->getImbalance() << std::endl;
}