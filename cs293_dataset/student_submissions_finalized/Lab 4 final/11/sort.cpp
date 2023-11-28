#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int n){
    this->choice = choice;
    this->n = n;
    this->array = new Journey[n];
    this->tree = new BST() ; 
    comparisons=0;
    i = 0 ;
}


bool SorterTree::Quicksortcall(int l, int r){
    int i = l;
    int j = r;
    Journey pivot;
    switch(choice) {
    case 1:
        pivot = *choose_one(array,l,r);
        break;
    case 2:
        pivot = *choose_two(array,l,r); 
        break;
    case 3:
        pivot = *choose_three(array,l,r); 
        break;
    case 4:
        pivot = *choose_four(array,l,r); 
        break;
    default:
        cout << "Invalid code";
        exit(0);
    } 
    
    tree->insert(pivot.getJourneyCode() , pivot.getPrice()) ;     
    while(j>=i){
        while( i < n && array[i] < pivot ) {
            i++; comparisons++ ;
        }
        comparisons++;
        while( j < n && pivot < array[j]){
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
        if(l < j) Quicksortcall(l,j);
        if(r > i) Quicksortcall(i,r);
    return true;
}


bool SorterTree::Quicksort(int l, int r){
    Quicksortcall(l,r);
    cout<< "Comparision : " << comparisons << endl;
    return true ;
}

bool SorterTree::QuicksortWithBSTInsert(int l, int r)
{
   return Quicksort(l,r);
}



bool SorterTree::printArray()
{
    for (int i = 0; i < n; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
   
