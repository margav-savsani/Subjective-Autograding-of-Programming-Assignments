#include "sort.h"
#include "choose.cpp"
#include <iostream>

// Code up the functions defined in sort.cpp

// Defined valid constructor
SorterTree::SorterTree(int choice, int l) : choice(choice), l(l) {}

// Sort the array according to the stored values
bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start < finish){
        Journey* pivot;
        if(choice == 1)
            pivot = choose_one(array, start, finish);
        else if(choice == 2)
            pivot = choose_two(array, start, finish);
        else if(choice == 3)
            pivot = choose_three(array, start, finish);
        
        int leftptr = start-1;
        int rightptr = finish+1;

        while(true){
            do{
              rightptr--;  
            } while(*pivot < array[rightptr] && rightptr >= start);
            do{
                leftptr++;
            }while(array[leftptr] < *pivot && leftptr <= finish);
            if(leftptr < rightptr){
                Journey temp;
                temp = array[leftptr];
                array[leftptr] = array[rightptr];
                array[rightptr] = temp;
            } else{
                break;
            }
        }

        if(rightptr == finish)
            rightptr--;

        Quicksort(start, rightptr);
        Quicksort(rightptr+1, finish);

        return true;
    }

    return false;
}

// insert node corresponding to chosen 
bool SorterTree::insertPivot(int JourneyCode, int price){
        tree->insert(JourneyCode, price);
        return true;
}

// Sort the array according to the stored values and store nodes in BST
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(start == finish){
        insertPivot(array[start].getJourneyCode(), array[start].getPrice());
    }

    if(start < finish){
        Journey* pivot;
        if(choice == 1)
            pivot = choose_one(array, start, finish);
        else if(choice == 2)
            pivot = choose_two(array, start, finish);
        else if(choice == 3)
            pivot = choose_three(array, start, finish);
        insertPivot(pivot->getJourneyCode(), pivot->getPrice());
        
        int leftptr = start-1;
        int rightptr = finish+1;

        while(true){
            do{
              rightptr--;  
            } while(*pivot < array[rightptr] && rightptr >= start);
            do{
                leftptr++;
            }while(array[leftptr] < *pivot && leftptr <= finish);
            if(leftptr < rightptr){
                Journey temp;
                temp = array[leftptr];
                array[leftptr] = array[rightptr];
                array[rightptr] = temp;
            } else{
                break;
            }
        }

        if(rightptr == finish)
            rightptr--;


        QuicksortWithBSTInsert(start, rightptr);
        QuicksortWithBSTInsert(rightptr+1, finish);

        return true;
    }

    return false;
}

// returns pointer to the tree of pivots
BST* SorterTree::getTree() {
    return tree;
}

// prints the array
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

// Destructor
SorterTree::~SorterTree(){
    delete tree;
}