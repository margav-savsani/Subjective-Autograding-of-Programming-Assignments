#include <iostream>
#include "choose.h"
#include "sort.h"

// Code up the functions defined in sort.cpp

// partition function for quicksort
int SorterTree::partition(int start, int end, Journey* pivot){
    Journey p = *pivot;
    int i = start-1;
    int j = end+1;
    while(true){
        do{
            j = j-1;
            comparisons++;
        }while(p < array[j]);

        do{
            i = i+1;
            comparisons++;
        }while(array[i] < p);

        if(i<j){
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        else{
            return j;
        }
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    if(start <= finish){
        Journey* pivot;
        switch(choice){
            case 1:
                pivot = choose_one(array, start, finish);
                break;
            case 2:
                pivot = choose_two(array, start, finish);
                break;
            case 3:
                pivot = choose_three(array, start, finish);
                break;
            case 4:
                pivot = choose_four(array, start, finish);
                break;
            default:
                pivot = choose_one(array, start, finish);
                break;
        }

        if(pivot == nullptr){
            cout << "ERROR: NULL pivot generated" << endl;
            return false;
        }

        bool found = 0;
        for (int i = 0; i < l; i++)
        {
            if(array[i].getJourneyCode() == pivot->getJourneyCode() && array[i].getPrice() == pivot->getPrice()){
                pivot = &array[i];
                found = 1;
                break;
            }
        }
        if(!found){
            cout << "ERROR: Pivot outside array generated" << endl;
            return false;
        }

        int i = SorterTree::partition(start, finish, pivot);
        if(i == finish){ // avoids infinite recursion
            if(!Quicksort(start, i-1)) return false;
        }
        else{
            if(!Quicksort(start, i)) return false;
        }

        if(!Quicksort(i+1, finish)) return false;
    }

    return true;
}


bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(start <= finish){
        Journey* pivot;
        switch(choice){
            case 1:
                pivot = choose_one(array, start, finish);
                break;
            case 2:
                pivot = choose_two(array, start, finish);
                break;
            case 3:
                pivot = choose_three(array, start, finish);
                break;
            case 4:
                pivot = choose_four(array, start, finish);
                break;
            default:
                pivot = choose_one(array, start, finish);
                break;
        }

        if(pivot == nullptr){
            cout << "ERROR: NULL pivot generated" << endl;
            return false;
        }

        bool found = 0;
        for (int i = 0; i < l; i++)
        {
            if(array[i].getJourneyCode() == pivot->getJourneyCode() && array[i].getPrice() == pivot->getPrice()){
                pivot = &array[i];
                found = 1;
                break;
            }
        }
        if(!found){
            cout << "ERROR: Pivot outside array generated" << endl;
            return false;
        }
        

        SorterTree::insertPivot(pivot->getJourneyCode(), pivot->getPrice());

        int i = SorterTree::partition(start, finish, pivot);
        if(i == finish){ // avoids infinite recursion
            if(!QuicksortWithBSTInsert(start, i-1)) return false;
        }
        else{
            if(!QuicksortWithBSTInsert(start, i)) return false;
        }

        if(!QuicksortWithBSTInsert(i+1, finish)) return false;
    }

    return true;

}

// Prints array of journeys
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "     Journey Price:"<<array[i].getPrice()<<std::endl;
    }

    return 1;
}

// constructor
SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    this->array = new Journey[l];
    this->index = 0;
    this->tree = new BST;
    this->comparisons = 0;
}

// destructor
SorterTree::~SorterTree(){
    delete[] array;
}

// insert function for getting journeys input
bool SorterTree::insert(unsigned int journeyCode, unsigned int price){
    Journey j(journeyCode, price);
    
    array[index++] = j;

    return 1;
}

// insert node corresponding to chosen pivot in BST
bool SorterTree::insertPivot(int JourneyCode, int price){
    return this->tree->insert(JourneyCode, price);
}

// prints BST, number of comparisions and imbalance
void SorterTree::printResults(){
    tree->printBST(""); 
    cout << endl << "Number of comparisons: " << comparisons << endl;
    cout << "Imbalance in BST: " << tree->getImbalance() << endl;
  }