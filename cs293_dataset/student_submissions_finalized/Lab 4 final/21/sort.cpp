#include "sort.h"
#include <iostream>


// Code up the functions defined in sort.cpp



SorterTree::SorterTree(int choice, int l, Journey* array){
    tree = new BST();
    this->choice = choice;
    this->l = l;
    this->array = array;
    comparisons=0;
}


bool SorterTree::Quicksortcall(int start, int finish){
    int i = start;
    int j = finish;
    Journey *pivot;

    switch(choice) {
    case 1:
        pivot = choose_one(array,start,finish);
        break;
    case 2:
        pivot = choose_two(array,start,finish); 
        break;
    case 3:
        pivot = choose_three(array,start,finish); 
        break;
    default:
        cout << "Invalid code";
    }
    
    while(j>=i){
        while(array[i] < *pivot) {
            i++; comparisons++ ;
        }
        comparisons++;
        while(*pivot < array[j]){
            j--; comparisons++;
        } 
        comparisons++;

        if( j>= i){
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }

    // cout << comparisons << endl;

        if(start < j) Quicksortcall(start,j);
        if(finish > i) Quicksortcall(i,finish);

        
        
    return true;

    }
void SorterTree::getcomp(){
    cout << "No of comparisons = ";
    cout << comparisons <<endl;
}

bool SorterTree::Quicksort(int start, int finish){
    // cout<< comparisons << "st" << endl;

    Quicksortcall(start,finish);
    cout<< comparisons << endl;
    }

bool SorterTree::insertPivot(int JourneyCode, int price){
    return (tree->insert(JourneyCode,price));
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    
    int i = start;
    int j = finish;
    Journey *pivot;
    switch(choice) {
    case 1:
        pivot = choose_one(array,start,finish);
        break;
    case 2:
        pivot = choose_two(array,start,finish); 
        break;
    case 3:
        pivot = choose_three(array,start,finish); 
        break;
    default:
        cout << "Invalid code";
    }

    //delete this part of code
    insertPivot((*pivot).getJourneyCode(),(*pivot).getPrice());
    
    while(j>=i){
        while(array[i] < *pivot) {
            i++; comparisons++ ;
        }
        comparisons++;
        while(*pivot < array[j]){
            j--; comparisons++;
        } 
        comparisons++;

        if( j>= i){
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }

    // cout << comparisons << endl;

        if(start < j) QuicksortWithBSTInsert(start,j);
        if(finish > i) QuicksortWithBSTInsert(i,finish);

    
        
        
    return true;

    }

BST* SorterTree::getTree(){
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


