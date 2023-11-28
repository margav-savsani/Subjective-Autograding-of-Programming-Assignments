#include "sort.h"
#include <iostream>
#include<cassert>
using namespace std;

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l, Journey* jarray){
    this->choice = choice;
    this->l = l;
    tree = new BST();
    comparisons=0;
    array = jarray;
}

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    tree = new BST();
    comparisons=0;
    array = new Journey[l];
}

void SorterTree::array_init(){
    unsigned int jcode, jprice;
    for(int i=0; i<l; i++){
        cin>>jcode>>jprice;
        // jcode = rand();
        // jprice = rand();
        array[i] = Journey(jcode, jprice);
    }
}

SorterTree::~SorterTree(){
    delete[] array;
    delete tree;
}

Journey* SorterTree::choose_pivot(Journey* x, int start, int finish){
    // pivot chooser function
    switch(choice){
        case 1:
            return choose_one(x, start, finish);
        case 2:
            return choose_two(x, start, finish);
        case 3:
            return choose_three(x, start, finish);
        case 4:
            return choose_four(x, start, finish);    
    }
    return nullptr;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    if(start >= finish) return true;

    Journey* pivot_ptr = choose_pivot(array, start, finish);
    if(pivot_ptr == nullptr) return false;
    // assert(pivot_ptr != nullptr);

    Journey pivot = *pivot_ptr;
    // cout<<"Pivot: "<<pivot.getJourneyCode()<<", "<<pivot.getPrice()<<" | "<<start<<",  "<<finish<<endl;

    int left = start;
    int right = finish;

    while(true){
        comparisons+=2;
        while(array[left] < pivot){
            comparisons++;
            left++;
        }
        while(pivot < array[right]){
            comparisons++;
            right--;
        }
        if(left < right){
            swap(array[left], array[right]);
        }
        else{break;}
    }
    if(left==right){
        return (Quicksort(start, right-1) && Quicksort(left+1, finish));
    }
    else{
        if(start!=left && finish != right){
            return(Quicksort(start, right) && Quicksort(left, finish));
        }
        else{
            return false;
        }
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    // base case
    if(start > finish) return true;

    Journey* pivot_ptr = choose_pivot(array, start, finish);
    if(pivot_ptr == nullptr) return false;

    Journey pivot = *pivot_ptr;
    if (!insertPivot(pivot.getJourneyCode(), pivot.getPrice())){
        cout<<"Insertion Error\n";
        // return false;
    }
    // cout<<"Pivot: "<<pivot.getJourneyCode()<<", "<<pivot.getPrice()<<" | "<<start<<",  "<<finish<<endl;

    int left = start;
    int right = finish;

    while(true){
        comparisons+=2;
        while(array[left] < pivot){
            comparisons++;
            left++;
        }
        while(pivot < array[right]){
            comparisons++;
            right--;
        }
        if(left < right){
            swap(array[left], array[right]);
        }
        else{break;}
    }
    if(left==right){
        // it means pivot is in the array
        return (QuicksortWithBSTInsert(start, right-1) && QuicksortWithBSTInsert(left+1, finish));
    }
    else{
        // pivot not in array
        if(start!=left && finish != right){
            return(QuicksortWithBSTInsert(start, right) && QuicksortWithBSTInsert(left, finish));
        }
        else{
            // partition unsuccesful
            return false;
        }
    }
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<" \tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode, price);
}

BST* SorterTree::getTree(){
    return tree;
}

int SorterTree::get_comparisons(){
    return comparisons;
}

bool SorterTree::Quicksort_k(int start, int finish, int k){
    return false;
}