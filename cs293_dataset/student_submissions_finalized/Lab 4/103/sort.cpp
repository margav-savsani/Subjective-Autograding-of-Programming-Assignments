#include "sort.h"
#include "choose.cpp"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l) : choice(choice), l(l) {}

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
        else if(choice == 4)
            pivot = choose_four(array, start, finish);
        
        int leftptr = start-1;
        int rightptr = finish+1;

        while(true){
            do{
              rightptr--;  
            } while(*pivot < array[rightptr]);
            do{
                leftptr++;
            }while(array[leftptr] < *pivot);
            if(leftptr < rightptr){
                Journey temp;
                temp = array[leftptr];
                array[leftptr] = array[rightptr];
                array[rightptr] = temp;
            } else{
                break;
            }
        }

        Quicksort(start, rightptr);
        Quicksort(rightptr+1, finish);

        return true;
    }

    return false;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
        tree->insert(JourneyCode, price);
        return true;
}

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
        else if(choice == 4)
            pivot = choose_four(array, start, finish);
        insertPivot(pivot->getJourneyCode(), pivot->getPrice());
        
        int leftptr = start-1;
        int rightptr = finish+1;

        while(true){
            do{
              rightptr--;  
            } while(*pivot < array[rightptr]);
            do{
                leftptr++;
            }while(array[leftptr] < *pivot);
            if(leftptr < rightptr){
                Journey temp;
                temp = array[leftptr];
                array[leftptr] = array[rightptr];
                array[rightptr] = temp;
            } else{
                break;
            }
        }

        QuicksortWithBSTInsert(start, rightptr);
        QuicksortWithBSTInsert(rightptr+1, finish);

        return true;
    }

    return false;
}

BST* SorterTree::getTree() {
    return tree;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

SorterTree::~SorterTree(){

}