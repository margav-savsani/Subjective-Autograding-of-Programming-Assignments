#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice,int l){
    this->choice = choice;
    this->l = l;
    comparisons = 0;
    array = new Journey [l];
    tree = new BST;
}
int SorterTree::partition(int start,int finish){
    Journey * x;
    if( choice == 1){
        x = choose_one(array,start,finish);
    }
    else if( choice == 2){
        x = choose_two(array,start,finish);
    }
    else if( choice == 3){
        x = choose_three(array,start,finish);
    }
    int i = start ;
    int j = finish ;
    while(true){
        while(!(array[j] <= *x)){
            comparisons++;
            j = j - 1;
        }
        while(!(*x <= array[i])){
            i = i + 1;
            comparisons++;
        }
        comparisons=comparisons+2;
        if(i < j){
            Journey k = array[i];
            array[i] = array[j];
            array[j] = k; 
        }
        else return j;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start < finish){    
        int p = partition(start,finish);
        if(p<finish){
            Quicksort(start,p);
            Quicksort(p+1,finish);
        }
        else{
            Quicksort(start,p-1);
            Quicksort(p,finish);
        }
    }
    return true;

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    Journey * x;
    if( choice == 1){
        x = choose_one(array,start,finish);
    }
    else if( choice == 2){
        x = choose_two(array,start,finish);
    }
    else if( choice == 3){
        x = choose_three(array,start,finish);
    }
    if(start < finish){
        insertPivot(x->getJourneyCode(),x->getPrice());   
        int p = partition(start,finish);
        if(p<finish){
            QuicksortWithBSTInsert(start,p);
            QuicksortWithBSTInsert(p+1,finish);}
        else{
            QuicksortWithBSTInsert(start,p-1);
            QuicksortWithBSTInsert(p,finish);
        }
    }
    if(start == finish){ insertPivot(x->getJourneyCode(),x->getPrice());}
    return true;
}

bool SorterTree::makeArray(int i,Journey J){
    if(i>=0 && i < l){
        array[i] = J;
        return true;
    }
    else return false;
}
void SorterTree::printTree(){
    tree->printBST("");
    cout << "Comparisons: " << comparisons << endl;
    cout << "Imbalance: " << tree->getImbalance() << endl;
}
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    tree->insert(JourneyCode,price);
    return true;
}

BST* SorterTree:: getTree(){
    return this->tree;
};
