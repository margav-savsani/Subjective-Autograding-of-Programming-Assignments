#ifndef SORT_CPP
#define SORT_CPP

#include "sort.h"
// #include "journey.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    //printArray();
    if(start >= finish){return true;}

    Journey* pivot;
    if(choice == 1){
        pivot = choose_one(array, start, finish);
    }

    else if(choice == 2){
        pivot = choose_two(array, start, finish);
    }

    else if(choice == 3){
        pivot = choose_three(array, start, finish);
    }
    

    
    if(pivot - array < 0 || pivot - array >= l){
        pivot = array + finish;
        cout << "out of range pivot, continuing sort with default"<<endl;
    }

    //push pivot to end of array
    Journey end_element = array[finish];
    array[finish] = *pivot;
    *pivot = end_element;
    pivot = array + finish;
    //cout<< pivot->getJourneyCode() << " " << pivot->getPrice()<<endl;

    int i = start;
    for( int j = start; j<finish ; j++){
        if(array[j] <= *pivot){
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            comparisons++;
        }
    }

    Journey temp = array[i];
    array[i] = *pivot;
    *pivot = temp;

    // int i = start;
    // int j = finish;
    // while( true ){
    //     //cout << "entered partition loop"<<endl;
    
    //     while ( array[i] <= *pivot ){
    //         //cout<<"increment left"<<endl;
    //         i++;
    //     }
    //     while ( !(array[j] < *pivot) ){
    //         //cout<<"increment right"<<endl;
    //         j--;
    //     }
    //     //cout << i << " " << j << endl;

    //     if(i >= j){
    //         //cout<<"breaking partition loop"<<endl;
    //         break;
    //     }
    //     Journey temp = array[i];
    //     array[i] = array[j];
    //     array[j] = temp;
    //     //cout<< "swapped"<<endl;
    // }
    //cout<< "exited aprtition loop"<<endl;

    // cout << i << " " << j <<endl;
    Quicksort(start, i-1);
    Quicksort(i+1, finish);
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursivel y keep sorting
    // Insert chosen pivot into the tree appropriately




    Journey* pivot;
    if(choice == 1){
        pivot = choose_one(array, start, finish);
    }

    else if(choice == 2){
        pivot = choose_two(array, start, finish);
    }

    else if(choice == 3){
        pivot = choose_three(array, start, finish);
    }
    //cout<<"selected pivot"<<endl;

    
    if(pivot - array < 0 || pivot - array >= l){
        pivot = array + finish;
        //cout << "out of range pivot, continuing sort with default"<<endl;
    }
    //cout<<start<<" "<<finish<<endl;
    if(start > finish){return false;}
    else if(start == finish){
        //cout<< "inserting into tree"<< pivot->getJourneyCode()<<" " << pivot->getPrice()<<endl;
        tree->insert(pivot->getJourneyCode(), pivot->getPrice()); 
        //cout<< tree->root->shortestPathLength << " " << tree->root->longestPathLength<<endl;
        //tree->printBST("");       
        return true;
    }

    //push pivot to end of array
    Journey end_element = array[finish];
    array[finish] = *pivot;
    *pivot = end_element;
    pivot = array + finish;
    //cout<< pivot->getJourneyCode() << " " << pivot->getPrice()<<endl;

    int i = start;
    for( int j = start; j<finish ; j++){
        if(array[j] <= *pivot){
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
        }
        comparisons++;
    }

    Journey temp = array[i];
    array[i] = *pivot;
    *pivot = temp;
    pivot = array + i;

    // int i = start;
    // int j = finish;
    // while( true ){
    //     //cout << "entered partition loop"<<endl;
    
    //     while ( array[i] <= *pivot ){
    //         //cout<<"increment left"<<endl;
    //         i++;
    //     }
    //     while ( !(array[j] < *pivot) ){
    //         //cout<<"increment right"<<endl;
    //         j--;
    //     }
    //     //cout << i << " " << j << endl;

    //     if(i >= j){
    //         //cout<<"breaking partition loop"<<endl;
    //         break;
    //     }
    //     Journey temp = array[i];
    //     array[i] = array[j];
    //     array[j] = temp;
    //     //cout<< "swapped"<<endl;
    // }
    //cout<< "exited aprtition loop"<<endl;

    // cout << i << " " << j <<endl;
    //printArray();
    //cout<< "inserting into tree"<< pivot->getJourneyCode()<<" " << pivot->getPrice()<<endl;
    tree->insert(pivot->getJourneyCode(), pivot->getPrice());

    //cout<< tree->root->shortestPathLength << " " << tree->root->longestPathLength<<endl;
    //tree->printBST("");

    //cout<<i<<endl;
    QuicksortWithBSTInsert(start, i-1);
    QuicksortWithBSTInsert(i+1, finish);
    //tree->printBST("");
    //cout<< comparisons<<endl;
    //cout<< tree->getImbalance()<<endl;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price: "<<array[i].getPrice()<<std::endl;
    }
}



#endif