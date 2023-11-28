#include <iostream>
using namespace std;
#include "choose.h"
#include "sort.h"

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(Journey *A, int choice , int l){
    this->choice = choice;
    array = A;
    this->l = l;
    comparisons = 0;
    tree = new BST();
}

SorterTree::~SorterTree(){}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    // Only executed if start < finish
    if(start < finish)
    {    
        Journey* pivot;

        //Choosing pivot function based on choice
        if(choice == 1) {
            pivot = choose_one(array, start, finish);

        }
            else if(choice == 2) {
                pivot = choose_two(array, start, finish);
            }
                else if(choice == 3) {
                    pivot = choose_three(array, start , finish);
                }


        int i = start-1, j = finish+1;

        // Arranging element of array in place such that pivot's left elements are smaller and right elements are larger. and Keeping count of comparisons
        while(true)
        {
            do {
                j--;
                comparisons++;
            } while((*pivot) < array[j]);

            do {
                i++;
                comparisons++;
            } while(array[i] < (*pivot));

            if(i<j)
            {
                Journey temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
            else break;
        }

        // Above loop exist when j>i  and j is our pivot 
        int pivotIndex = j;

        // Recursively sorting left and right subtree rooted at root
        bool leftSorted = SorterTree::Quicksort(start, pivotIndex-1);
        bool rightSorted = SorterTree::Quicksort(pivotIndex+1 , finish);
        return true;
    }
    else return false; 

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    // Only executed if start < finish
    if(start < finish)
    {
        Journey* pivot;
         //Choosing pivot function based on choice
        if(choice == 1) {
            pivot = choose_one(array, start, finish);

        }
            else if(choice == 2) {
                pivot = choose_two(array, start, finish);
            }
                else if(choice == 3) {
                    pivot = choose_three(array, start , finish);
                }

        int i = start-1, j = finish+1;

        // Arranging element of array in place such that pivot's left elements are smaller and right elements are larger. and Keeping count of comparisons
        while(true)
        {
            do {
                j--;
            } while((*pivot) < array[j]);

            do {
                i++;
            } while(array[i] < (*pivot));

            if(i<j)
            {
                Journey temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
            else break;
        }
          int pivotIndex = j;
        assert(pivotIndex >=start && pivotIndex <=finish);

        // Inserting the pivot journey data into BST
        bool insert = tree->insert(array[pivotIndex].getJourneyCode(), array[pivotIndex].getPrice());
        
        // Recursively sorting left and right subtree rooted at root
        bool leftSorted = SorterTree::QuicksortWithBSTInsert(start, pivotIndex-1);
        bool rightSorted = SorterTree::QuicksortWithBSTInsert(pivotIndex+1 , finish);

        return (insert && leftSorted && rightSorted);
    }
    else return false; 

}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"; Journey Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

// Returns total comparisons done
int SorterTree::totalComparisons()
{
    return comparisons;
}

// Return root of BST
BST* SorterTree::getTree(){
    return tree;
}