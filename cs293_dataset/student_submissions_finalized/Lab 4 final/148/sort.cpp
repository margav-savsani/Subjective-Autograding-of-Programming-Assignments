#include "sort.h"
#include "choose.h"
#include <iostream>
#include "journey.h"
#include <algorithm>
// Code up the functions defined in sort.cpp
using namespace std;
SorterTree::SorterTree(int choice, int l){
    switch(choice){
        case 1:
            pivot_func = choose_one;
            break;
        case 2:
            pivot_func = choose_two;
            break;
        case 3:
            pivot_func = choose_three;
            break;
    }
    this->l = l;
    this->choice = choice;
    array = new Journey[l];
    tree = new BST();

}
int SorterTree::Partition(Journey* start, Journey* end, Journey * pivot){
    // Partition the region betweem start and end, at pivot
    Journey *i = start;
    Journey *j = end;
    Journey *elemtLtPivot = i;
    // If a pointer points to an element in an array, a+1 points to the element next to it

    for(; i <= j; i++){
        if(*i < *pivot){
            // Put it in the place of elemtltPivot
            if(elemtLtPivot != pivot){
                Journey a = *elemtLtPivot;
                *elemtLtPivot = *i;
                *i = a;
            }
            else{
             Journey a = *elemtLtPivot;
                *elemtLtPivot = *i;
                *i = a;
                pivot = i;
            }
            elemtLtPivot += 1;
        }
    }
    if (elemtLtPivot == start){
        Journey a = *elemtLtPivot;
        *elemtLtPivot = *pivot;
        *pivot = a;
        elemtLtPivot += 1;
    }

    return elemtLtPivot - start-1;
}
bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // cout << start << " " << finish<< endl;
    // cout << "Start = " << start << endl;
    // cout << "End = " << finish << endl;
    // printArray();
    if (start > finish) return false;
    if (start == finish) return true;
    Journey *pivot = pivot_func(array, start, finish);
    if (pivot > array+finish) return false;
    if (pivot < array+start) return false;
    // cout << "Pivot = " << pivot->getJourneyCode() << endl;
    int partition = Partition(array+start, array+finish, pivot); // This returns the offset from start
    // cout << partition<< endl;
    if(partition < 0){
        return false;
    }
    Quicksort(start, start+partition);
    Quicksort(start+partition+1, finish);
    return true;
}

bool SorterTree::isSorted(int start, int end){
    for(int i = start+1; i< end; i++){
        if(array[i] < array[i-1]){
            return false;
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
    if (start > finish) return false;
    // if (start == finish) return true;
    Journey *pivot = pivot_func(array, start, finish);

    if( !(tree->insert(pivot->getJourneyCode(), pivot->getPrice()))){
        return false;
    }
    int pivotIndex = pivot - array;
    QuicksortWithBSTInsert(start, pivotIndex-1);
    QuicksortWithBSTInsert(pivotIndex+1, finish);

    return true;
}



bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

void SorterTree::initWithRandomVals(){
    int js[l], ks[l];
    int j, k;
    for(int i = 0;i<l;i++){
        do{
            j = rand();
            k = rand() % 100000;
        }while(std::find(js, js+i, j)!=js+i && std::find(ks, ks+i, k)!=ks+i);
        array[i] = Journey(j,k);
        js[i] = j;
        ks[i] = k;
    }
}

bool SorterTree::insert(int jc, int price, int pos){
    array[pos] = Journey(jc, price);
    return true;
}
