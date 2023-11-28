#include "sort.h"
#include <iostream>

SorterTree::SorterTree(int choice, int l){      // Constructor
    array = new Journey[l];
    this->choice = choice;
    this->l = l;
    comparisons = 0;
    tree = new BST();
}

// Function to get number of comparisons
int SorterTree::comparisonsDone(){              
    return comparisons;
}

// Quick Sort
bool SorterTree::Quicksort(int start, int finish){      
    comparisons++;                                      // incrementing comparisons at each call of QuickSort
    int i = start, j = finish;
    Journey *pivot_journey;
    if(choice==1){                                      // Choosing pivot from the choose functions
        pivot_journey = choose_one(array,start,finish);
    }
    else if(choice==2){
        pivot_journey = choose_two(array,start,finish);
    }
    else if(choice==3){
        pivot_journey = choose_three(array,start,finish);
    }
    else if(choice==4){
        pivot_journey = choose_four(array,start,finish);
    }
    while(i <= j){                                      // Partitioning with respect to pivot
        while(*pivot_journey < array[j] && j < l){
            j = j - 1;
            comparisons++;
        }
        while(array[i] < *pivot_journey && i < l){
             i = i + 1;
             comparisons++;
        }
        if(i <= j){
            swapElements(&array[i],&array[j]);         
            i++;
            j--;
        }
    }
    if(start < j) Quicksort(start,j);
    if(i < finish) Quicksort(i,finish);
    return true;
}

// Function to perform Quick Sort along with inserting pivots into the BST
bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
    comparisons++;
    int i = start, j = finish;
    Journey *pivot_journey;
    if(choice==1){
        pivot_journey = choose_one(array,start,finish);
    }
    else if(choice==2){
        pivot_journey = choose_two(array,start,finish);
    }
    else if(choice==3){
        pivot_journey = choose_three(array,start,finish);
    }
    else if(choice==4){
        pivot_journey = choose_four(array,start,finish);
    }
    tree->insert(pivot_journey->getJourneyCode(),pivot_journey->getPrice());        // Insert the pivot data into BST
    while(i <= j){
        while(*pivot_journey < array[j] && j < l){
            j = j - 1;
            comparisons++;
        }
        while(array[i] < *pivot_journey && i < l){
             i = i + 1;
             comparisons++;
        }
        if(i <= j){
            swapElements(&array[i],&array[j]);
            i++;
            j--;
        }
    }
    if(start < j) QuicksortWithBSTInsert(start,j);
    if(i < finish) QuicksortWithBSTInsert(i,finish);
    return true;
}

// Function for swaping two journeys
void SorterTree::swapElements(Journey *elem1, Journey *elem2){
    Journey temp = *elem1;
    *elem1 = *elem2;
    *elem2 = temp;
}

// Get the array of Journeys
Journey *SorterTree::getJourney(){
    return array;
}

// Insering new Journey into the array of journeys
void SorterTree::insertNewJourney(Journey journey, int index){
    array[index] = journey;
}

// Print array of Journeys
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\t\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

BST* SorterTree::getTree(){
    return tree;
}

// Destructor
SorterTree::~SorterTree(){}
