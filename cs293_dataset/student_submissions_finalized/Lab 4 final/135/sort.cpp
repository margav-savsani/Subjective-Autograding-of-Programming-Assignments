#include "updated_sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->l = l;
    this->choice = choice;
    array = new Journey[l];
    tree = new BST;
    comparisons = 0;
    for(int i=0; i<l; i++){
        int journeycode, price;
        cin >> journeycode >> price;
        array[i] = Journey(journeycode, price);
    }
}

bool SorterTree::Quicksort(int start, int finish){
    // Call appropriate pivot function based on choice
    if(choice < 1 || choice > 3) return false;
    
    if(start > finish) return false;
    // cout << 2 << "\n";
    if(start == finish) return true;
    Journey pivot;
    switch (choice)
    {
    case 1:
        pivot = *choose_one(array, start, finish);
        break;
    
    case 2:
        pivot = *choose_two(array, start, finish);
        break;
    
    case 3:
        pivot = *choose_three(array, start, finish);
        break;
    
    default:
        break;
    }
    // Split into 2 parts based on pivot choice
    // cout << start << " " << finish << "\n";
    int i = start, j = finish;
    while(true){
        while(array[i] < pivot && i<finish){
            comparisons++;
            i++;
            // cout << "i " << i << "\n";
        }
        while(pivot < array[j] && j>start){
            comparisons++;
            j--;
            // cout << "j " << j << "\n";
        }
        if(i<=j){
            // cout << i << " " << j << "\n";
            Journey temp = array[j];
            array[j] = array[i];
            array[i] = temp;
            i++;
            j--;
        }
        else{
            break;
        }
    }
    // Recursively keep sorting
    Quicksort(start, j);
    Quicksort(i, finish);

    if(finish - start + 1 == l){
        cout << comparisons << "\n";
    }

    return true;

}

bool SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode, price);
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(choice < 1 || choice > 3) return false;

    if(start > finish) return false;
    // cout << 2 << "\n";
    if(start == finish){
        // cout << 1 << "\n";
        return true;
    }
    // Call appropriate pivot function based on choice
    Journey pivot;
    switch (choice)
    {
    case 1:
        pivot = *choose_one(array, start, finish);
        break;
    
    case 2:
        pivot = *choose_two(array, start, finish);
        break;
    
    case 3:
        pivot = *choose_three(array, start, finish);
        break;
    
    default:
        break;
    }
    // Split into 2 parts based on pivot choice
    // cout << "Start " << start << " " << finish << "\n";
    int i = start, j = finish;
    while(true){
        while(array[i] < pivot && i<finish){
            i++;
            comparisons++;
            // cout << "i " << i << "\n";
        }
        while(pivot < array[j] && j>start){
            j--;
            comparisons++;
            // cout << "j " << j << "\n";
        }
        if(i<=j){
            // cout << i << " " << j << "\n";
            Journey temp = array[j];
            array[j] = array[i];
            array[i] = temp;
            i++;
            j--;
        }
        else{
            // cout << "Part " << i << " " << j << "\n";
            break;
        }
    }
    // Recursively keep sorting
    QuicksortWithBSTInsert(start, j);
    // cout << "Later " << i << " " << finish << "\n";
    QuicksortWithBSTInsert(i, finish);
    // Insert chosen pivot into the tree appropriately
    insertPivot(pivot.getJourneyCode(), pivot.getPrice());

    if(finish - start + 1 == l){
        cout << "Total number of coparisions = " << comparisons << "\n";
    }

    return true;
}

bool SorterTree::printArray()
{   if(l=0) return false;
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

BST* SorterTree::getTree(){
    return tree;
}

SorterTree::~SorterTree(){
    cout << "Total Imbalance = " << getTree()->getImbalance() << "\n";
}