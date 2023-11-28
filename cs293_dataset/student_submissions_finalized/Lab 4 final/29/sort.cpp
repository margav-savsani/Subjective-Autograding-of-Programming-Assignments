#include "sort.h"
#include <iostream>
// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l) // default constructor
{
    this->choice = choice;
    this->l = l;
    tree = new BST;
    comparisons = 0;
    array = new Journey [l];
    for(int i = 0 ; i < l ; i ++){
        unsigned J, p;
        std::cin >> J >> p;   // take input from user
        array[i] = Journey(J,p);
    }
}

int SorterTree::getComparisons(){return comparisons;} // return how many time < or > used
bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    //base case
    if(start >= finish) return true;
    //otherwise  
    Journey *pivot;  
    if(choice == 1) pivot = choose_one(array,start,finish);
    if(choice == 2) pivot = choose_two(array,start,finish);
    if(choice == 3) pivot = choose_three(array,start,finish);
    if(!((&array[start] <= pivot)&&(pivot <= &array[finish]))) return false;
    Journey p = *pivot;
    int i = start , j = finish;
    while(true){
        while(array[i] < p){
            comparisons++;
            i++;
        } 
        while(array[j] > p){
            comparisons++;
            j--;
        } 
        comparisons+=2;
        if(j<=i) break;
        Journey temp = array[i];
        array[i] = array[j];
        array[j] = temp;    
    }
    return Quicksort(start,j-1) && Quicksort(j+1,finish);
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    
    if(start >= finish) return true;
    //otherwise
    Journey *pivot;
    if(choice == 1) pivot = choose_one(array,start,finish);
    if(choice == 2) pivot = choose_two(array,start,finish);
    if(choice == 3) pivot = choose_three(array,start,finish);
    if(!((&array[start] <= pivot)&&(pivot <= &array[finish]))) return false;
    Journey p = *pivot;
    if(!insertPivot(p.getJourneyCode(),p.getPrice())) return false;
    int i = start , j = finish;
    while(true){
        while(array[i] < p ){
            comparisons++;
            i++;
        } 
        while(array[j] > p){
            comparisons++;
            j--;
        } 
        comparisons+=2;
        if(j<=i) break;
        Journey temp = array[i];
        array[i] = array[j];
        array[j] = temp;    
    }

    return QuicksortWithBSTInsert(start,j-1) && QuicksortWithBSTInsert(j+1,finish);
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<" \t Journey Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode,price);
}

BST* SorterTree::getTree(){
    return tree;
}

SorterTree::~SorterTree(){}