#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree :: SorterTree(int Choice,int L){ //constructor to initialise choice, number of entries,array,comparisions,tree
    choice = Choice;
    l = L;
    array = new Journey[L];
    comparisons=0;
    tree = new BST();
}
bool SorterTree::Quicksort(int start, int finish) //used to sort the array from the start index to the finish index
{
    if(start>=finish){  //if start>=finish returns false;
        return false;
    }
    Journey *pivot;
    if(choice==1){ //if choice=1 call the choose_one function
        pivot = choose_one(array,start,finish);
    }
    if(choice==2){ //if choice=2 call the choose_two function
        pivot = choose_two(array,start,finish);
    }
    if(choice==3){ //if choice=3 call the choose_three function
        pivot = choose_three(array,start,finish);
    }
    int pivot_ele = pivot->JourneyCode;
    int i = start;
    int j = finish;
     while(true){
        while(!(array[j].JourneyCode<=pivot_ele)){ //update j till the value is less than or equal to the pivot and also update comparisons
            j = j - 1;
            comparisons++;
        }
        while(!(array[i].JourneyCode>=pivot_ele)){ //update i till the value is greater than or equal to the pivot and also update comparisons
            i = i + 1;
            comparisons++;
        }
        if(i<j){ //swap the fixed elements
            Journey x;
            x = array[i];
            array[i] = array[j];
            array[j] = x;
        }
        else{ //breaks if i>=j
            break;
        }
    } //changing the partition index according to the pivot
    if(pivot==&array[start]){
        Quicksort(start,j);
        Quicksort(j+1,finish);
    }
    else if(pivot==&array[finish]){
        Quicksort(start,j-1);
        Quicksort(j,finish);    
    }
    else{
        Quicksort(start,j);
        Quicksort(i,finish);     
    }
    return true;
}
int SorterTree::compare(){ //returns the number of comparisons
    return comparisons;
}
bool SorterTree::QuicksortWithBSTInsert(int start, int finish) //sorts the array and also insert the pivot elements to the tree
{
    if(start>=finish){ //if start>=finish returns false;
        return false;
    }
    Journey *pivot;
    if(choice==1){ //if choice=1 call the choose_one function and inserts the pivot element if it is not repeated
        pivot = choose_one(array,start,finish);
        insertPivot(pivot->getJourneyCode(),pivot->getPrice());
    }
    if(choice==2){ //if choice=2 call the choose_two function and inserts the pivot element if it is not repeated
        pivot = choose_two(array,start,finish);
        insertPivot(pivot->getJourneyCode(),pivot->getPrice());
    }
    if(choice==3){ //if choice=3 call the choose_three function and inserts the pivot element if it is not repeated
        pivot = choose_three(array,start,finish);
        insertPivot(pivot->getJourneyCode(),pivot->getPrice());
    }
    int pivot_ele = pivot->JourneyCode;
    int i = start;
    int j = finish;
    while(true){
        while(!(array[j].JourneyCode<=pivot_ele)){ //update j till the value is less than or equal to the pivot and also update comparisons
            j = j - 1;
            comparisons++;
        }
        while(!(array[i].JourneyCode>=pivot_ele)){ //update i till the value is greater than or equal to the pivot and also update comparisons
            i = i + 1;
            comparisons++;
        }
        if(i<j){ //swap the fixed elements
            Journey x;
            x = array[i];
            array[i] = array[j];
            array[j] = x;
        }
        else{ //breaks if i>=j
            break;
        }
    }  //changing the partition index according to the pivot
    if(pivot==&array[start]){
        QuicksortWithBSTInsert(start,j);
        QuicksortWithBSTInsert(j+1,finish);
    }
    else if(pivot==&array[finish]){
        QuicksortWithBSTInsert(start,j-1);
        QuicksortWithBSTInsert(j,finish);    
    }
    else{
        QuicksortWithBSTInsert(start,j);
        QuicksortWithBSTInsert(i,finish);     
    }
    return true;
}
bool SorterTree::insertPivot(int JourneyCode,int price){ //will insert the pivot element into the tree
    if(JourneyCode>0 && price>0){ //return true if it is a valid pair else false
        tree->insert(JourneyCode,price);
        return true;
    }
    return false;
}
void SorterTree::print(){ //prints the BST
    tree->printBST("");
}
BST* SorterTree::getTree(){ //returns pointer to the tree
    return tree;
}
bool SorterTree::printArray() //prints the array
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
int SorterTree::Imbalance(){ //returns the imbalance of the tree
    return tree->getImbalance();
}
