#include "sort.h"
#include <iostream>
#include <cassert>

SorterTree::SorterTree(int choice, int l){
    this -> choice = choice;
    this -> l = l;
    array = new Journey[l*sizeof(Journey)];
    tree = new BST;
    comparisons = 0;
}

SorterTree::SorterTree(int choice, int l, Journey* arr){
    this -> choice = choice;
    this -> l = l;
    array = arr;
    tree = new BST;
    comparisons = 0;
}

void swap(Journey* a, Journey* b){Journey tmp = *a; *a = *b; *b = tmp;}

int SorterTree::index_from_pointer(Journey* ptr){return (ptr - array);}

Journey* SorterTree::master_choose(int start, int finish){
    if (choice == 1) return choose_one(array, start, finish);
    if (choice == 2) return choose_two(array, start, finish);
    if (choice == 3) return choose_three(array, start, finish); 
    return nullptr;
}

SorterTree::~SorterTree() {free(array); free(tree);};

void SorterTree::randomizer(int start, int finish){
    int rand_index = index_from_pointer(master_choose(start,finish));
    assert((rand_index >= 0) && (rand_index < l));

    swap(array+rand_index,array+finish); 
}

int SorterTree::part(int start, int finish){
    randomizer(start,finish);

    Journey pivot = array[finish]; 
    int i = (start - 1); 
  
    for (int j = start; j <= finish; j++) {comparisons++; if (array[j].getJourneyCode() < pivot.getJourneyCode()) {swap(&array[++i], &array[j]);}}

    swap(array + i + 1, array + finish);
    return (i + 1);
}

int SorterTree::modified_part(int start, int finish){
    randomizer(start,finish);

    tree -> insert(array[finish].getJourneyCode(),array[finish].getPrice()); 

    Journey pivot = array[finish]; 
    int i = (start - 1); 
  
    for (int j = start; j <= finish - 1; j++) {comparisons++; if (array[j].getJourneyCode() < pivot.getJourneyCode()) {swap(&array[++i], &array[j]);}}

    swap(array + i + 1, array + finish);
    return (i + 1);
}

bool SorterTree::Quicksort(int start, int finish)
{
    if (start == finish) return true;
    else {
        if (start < finish) {
            int mid = part(start, finish);

            Quicksort(start, mid - 1); 
            Quicksort(mid + 1, finish);
        }
        else return false;
    }
    
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (start == finish) return true;
    else {
        if (start < finish) {
            int mid = modified_part(start, finish);

            QuicksortWithBSTInsert(start, mid - 1);
            QuicksortWithBSTInsert(mid + 1, finish);
        }
        else return false;
    }
}

void SorterTree::printTree(){
    tree -> printBST("");
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++) if(!(std::cout<<"Journey code: "<<array[i].getJourneyCode()<<" Journey Price:"<<array[i].getPrice()<<std::endl)) return false;
    return true;
}

BST* SorterTree::getTree() {return tree;}
