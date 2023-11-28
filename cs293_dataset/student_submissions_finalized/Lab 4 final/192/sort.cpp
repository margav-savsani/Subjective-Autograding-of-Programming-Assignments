#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree :: SorterTree(int choice, int l){
    //Constructor for the Sorter Tree

    this->choice = choice;
    this->l = l;

    //allocate memory for BST and array
    this->array = new Journey[l];
    this->tree = new BST();

    
}
//insert the Journey in the array of Sorter Tree
bool SorterTree::insertArray(int JourneyCode, int price){
    if (inserted == l) return false;
    else {
        Journey b(JourneyCode, price);
        array[inserted] = b;
        inserted++;
        return true;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    
    int front = start;
    int end = finish;
    Journey *pivot;
    

    
    if (this->choice == 1){
        pivot = choose_one(array, start, finish);
    } else if (this->choice == 2){
         pivot = choose_two(array, start, finish);
    } else if (this->choice == 3){
         pivot = choose_three(array, start, finish);
    }
    



    
    // if start > finish then sorting meaningless
    if (start > finish) return false;

    //start == finish means already sorted
    if (start = finish) return true;
    
    Journey temp = array[end];
    array[end] = *pivot;
    *pivot = temp;
    temp = array[end];
 
    while (front < end){

        if (!(temp < array[front])){
            front++;
            comparisons++;
        } else if (temp < array[end]) {
            end--;
            comparisons++;
        } else {
            //replace the first element greater than pivot and the first element less than equal to the pivot
            Journey rtemp = array[end];
            array[end] = array[front];
            array[front] = rtemp;

            
        }

    }


    //recursively sort the array
    this->Quicksort(start, front - 1);
    this->Quicksort(end, finish);


    return true;
}



bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    int front = start;
    int end = finish;
    Journey * pivot;
    

    //choose the pivot based on choice
   if (this->choice == 1){
        pivot = choose_one(array, start, finish);
    } else if (this->choice == 2){
        pivot = choose_two(array, start, finish);
    } else if (this->choice == 3){
        pivot = choose_three(array, start, finish);
    }
    
    //if front is more than end then sorting is meaningless

    if (front > end) return false;
    //insert the pivot element inside the BST
    tree->insert(pivot->getJourneyCode(), pivot->getPrice());

    //if already sorted then return
    if (front == end) return true;


    
    //swap the pivot with the last element
    Journey temp = array[end];
    array[end] = *pivot;
    *pivot = temp;
    temp = array[end];
 

    //swapping the values to the left and to the right of the pivot
    while (front < end){

        if (!(temp < array[front])){
            comparisons++;
            front++;
        } else if (temp < array[end]) {
            comparisons++;
            end--;
        } else {
            Journey rtemp = array[end];
            array[end] = array[front];
            array[front] = rtemp;

            
        }

    }

    //recursively sort the array
    this->QuicksortWithBSTInsert(start, front - 1);
    this->QuicksortWithBSTInsert(end, finish);

    return true;


    
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"   \tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

BST* SorterTree::getTree(){
    //return the address of the tree.
    return this->tree;
}

int SorterTree::getComparisons(){
    //return the number of comparisons made by Quicksort
    return comparisons;
}

