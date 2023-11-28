#include "sort.h"
#include <iostream>

using namespace std;

//Proper constructor 
//Initialise choice, num_entries(l)
//comparisons and counter to 0.
SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    tree = new BST();
    comparisons = 0;
    counter = 0;
}

//This function sets the array variable in SorterTree equal to the argument passed.
void SorterTree::setArray(Journey* array){
    this->array = array;
}

//This global function exchanges two Journey pointers namely pivot and finish.
void exchange(Journey* pivot, Journey* finish){
    Journey tmp(pivot->getJourneyCode(),pivot->getPrice());
    *pivot = *finish;
    *finish = tmp;
}

//Partitions Algorithm
//Partitions the array into two parts separated by a pivot.
//The left part has elements less than the pivot
//The right part has elements greater than the pivot.
int SorterTree::Partition(int start, int finish){
    Journey pivot(array[finish].getJourneyCode(),array[finish].getPrice()); //creating the pivot 
    int i = (start - 1); // Represents the right position of pivot found so far
    for (int j = start; j <= finish - 1; j++){ 
        // If current element is smaller than the pivot 
        comparisons++; //increment comparisons
        if (array[j] < pivot){
            i++; // increment index of smaller element 
            exchange(&array[i], &array[j]); //exchange the array elements
        } 
    } 
    exchange(&array[i + 1], &array[finish]); 
    return (i + 1); //return pos of pivot chosen at start.
}

//This function uses the choice functions defined in choice.cpp
//to generate a pivot. Everything on the whim of user.
Journey* getPivot(Journey* array, int start, int finish, int choice){
    Journey* pivot = new Journey();
    switch(choice){
        case 1: pivot = choose_one(array, start, finish);
                break;
        case 2: pivot = choose_two(array, start, finish);
                break;
        case 3: pivot = choose_three(array, start, finish);
    }
    return pivot;
}

bool SorterTree::Quicksort(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    //If start=finish then simply insertPivot and increment the counter,
    //because one pivot will be inserted.
    //Because a singleton set need not go through the large process below 
    //and simply inserting it would be much more better.
    if(start==finish){
        counter++;
    }

    //If start<finish generate pivot and partition the array.
    //Followed by recursively quicksorting the left and right parts.
    //Also increment the counter as one pivot has been inserted.
    if(start < finish){ 
        counter++;
        // pivot is partitioning element
        Journey* pivot = getPivot(array, start, finish, choice);
        if(pivot==nullptr) return false; //in case of abnormalities
        exchange(pivot, &array[finish]);
        int q = Partition(start, finish); 

        // Separately sort elements before 
        // partition and after partitioning pivot
        Quicksort(start, q-1); 
        Quicksort(q+1, finish); 
    }

    //When all elements have been added, then print the total number of comparisons
    //Once because the value of counter may be l for some time even after the first
    //l is achieved, that is because there may remain cases where start>finish are occuring
    //which don't affect counter. Hence we set once to false when the first time it enters if.
    if(counter==l and onceQS){
        onceQS = false;
        cout << "Total number of comparisons: " << comparisons << endl;
    }
    return true;
}

//This function simply inserts Pivot into the tree using the insert function.
bool SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode, price);
}

//Everything Same as QuickSort except for insertion of pivots into the tree
bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    if(start==finish){
        counter++;
        insertPivot(array[start].getJourneyCode(), array[start].getPrice());
    }

    if(start < finish){ 
        counter++;
        Journey* pivot = getPivot(array, start, finish, choice);
        if(pivot==nullptr) return false;
        exchange(pivot, &array[finish]);
        int q = Partition(start, finish); 

        insertPivot(array[q].getJourneyCode(), array[q].getPrice());
        QuicksortWithBSTInsert(start, q-1); 
        QuicksortWithBSTInsert(q+1, finish); 
    }

    if(counter==l and onceQSBST){
        onceQSBST = false;
        cout << "Total number of comparisons: " << comparisons << endl;
    }
    return true;
}

//Prints array
bool SorterTree::printArray(){
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

//Prints tree
bool SorterTree::printTree(){
    tree->printBST("");
    return true;
}

BST* SorterTree::getTree(){
    return tree;
}
