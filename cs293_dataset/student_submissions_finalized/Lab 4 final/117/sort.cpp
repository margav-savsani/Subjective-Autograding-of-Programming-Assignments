#include "sort.h"
// #include "choose.h"
#include <iostream>

using namespace std;

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    comparisons = 0;
    tree = new BST();
    array = new Journey[l];
    for(int i = 0; i < l; i++){
        int JourneyCode, price;
        cin >> JourneyCode >> price;
        Journey* newJourney = new Journey(JourneyCode, price);
        array[i].store(newJourney);
        delete(newJourney);
    }
}

//start and finish are array index, therefore we start with start=0 and finish = l-1
bool SorterTree::Quicksort(int start, int finish){
    // Call appropriate pivot function based on choice
    if(start == finish || start == finish +1) return true;
    if(start > finish+1) return false;
    Journey pivot;
    if(choice == 1) pivot = *choose_one(array, start, finish);
    else if(choice == 2) pivot = *choose_two(array, start, finish);
    else if(choice == 3) pivot = *choose_three(array, start, finish);
    else pivot = *choose_four(array, start, finish);
    int i = start, j = finish;
    
    if(start +1 == finish){
        if(array[start] < array[finish]) return true;
        else{
            Journey temp = array[start];
            array[start] = array[finish];
            array[finish] = temp;
        }
    }

    // Split into 2 parts based on pivot choice
    while(i < j){
        while(array[i]<pivot){
            comparisons++;
            i++;
        }
        
        comparisons++;
        while(pivot< array[j]){
            comparisons++;
            j--;
        }
        
        comparisons++;
        if(i == j){
            // cout << pivot.getJourneyCode();
            // cout << j;
            // printArray();
            return (Quicksort(start, j-1) && Quicksort(j+1, finish));
        }// pivot in array
        if(i > j){ 
            // cout << pivot.getJourneyCode();
            // cout << j << i;
            // printArray();
            return (Quicksort(start, i-1) && Quicksort(j+1, finish));
            
        }// pivot not in array
        Journey temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    
    // Recursively keep sorting
    
    return true;
    
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
    // Call appropriate pivot function based on choice
    if(start == finish)insertPivot(array[start].getJourneyCode(), array[start].getPrice());
    else if(start == finish +1) return true;
    else if(start > finish+1) return false;
    Journey pivot;
    if(choice == 1) pivot = *choose_one(array, start, finish);
    else if(choice == 2) pivot = *choose_two(array, start, finish);
    else if(choice == 3) pivot = *choose_three(array, start, finish);
    else pivot = *choose_four(array, start, finish);
    int i = start, j = finish;
    


    if(start +1 == finish){
        if(array[start] < array[finish]);
        else{
            Journey temp = array[start];
            array[start] = array[finish];
            array[finish] = temp;
        }
        insertPivot(array[start].getJourneyCode(), array[start].getPrice());
        insertPivot(array[finish].getJourneyCode(), array[finish].getPrice());

        return true;
    }

    insertPivot(pivot.getJourneyCode(), pivot.getPrice());

    // Split into 2 parts based on pivot choice
    while(i < j){
        while(array[i]<pivot){
            comparisons++;
            i++;
        }
        
        comparisons++;
        while(pivot< array[j]){
            comparisons++;
            j--;
        }
        
        comparisons++;

        if(i == j){
            // cout << pivot.getJourneyCode();
            // cout << j;
            // printArray();
            return (QuicksortWithBSTInsert(start, j-1) && QuicksortWithBSTInsert(j+1, finish));
        }// pivot in array
        if(i > j){ 
            // cout << pivot.getJourneyCode();
            // cout << j << i;
            // printArray();
            return (QuicksortWithBSTInsert(start, i-1) && QuicksortWithBSTInsert(j+1, finish));
            
        }// pivot not in array
        Journey temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    
    // Recursively keep sorting
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    tree->insert(JourneyCode, price);
    return true;
}

BST* SorterTree::getTree(){
    tree->printBST("");
    cout << tree->getImbalance()<<"\n";
    return tree;
}

bool SorterTree::printArray(){
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    cout << comparisons << "\n";
    return true;
}


SorterTree::~SorterTree(){};