#include "sort.h"
#include "choose.h"
#include <cassert>

SorterTree::SorterTree(int choice, int size){
    tree = new BST;
    if(choice == 1) choosePivot = choose_one;
    else if(choice == 2) choosePivot = choose_two;
    else if(choice == 3) choosePivot = choose_three;
    //add 4th function choice
    //else if(choice == 4) choosePivot = choose_four;
    array = new Journey[size];
    this->size = size;
}


bool SorterTree::Quicksort(int start, int finish){
    if(start >= finish) return true;
    int init_start = start, init_finish = finish;
    Journey *pivot = choosePivot(array, start, finish);
    if(pivot == NULL) return false;
    Journey pivot_val = *pivot;
    while(true){
        while(array[start] < pivot_val){
            start++; comparisons++;
            if(start > init_finish) return false;
        }
        while(array[finish] > pivot_val){
            finish--; comparisons++;
            if(finish < init_start) return false;
        }
        if(start < finish){
            Journey temp = array[finish];
            array[finish] = array[start];
            array[start] = temp;
        }
        else break;
    }
    //if(start - 1 == init_finish || finish + 1 == init_start) return false;
    if(!QuicksortWithInsert(init_start, start-1)) return false;
    if(!QuicksortWithInsert(start+1, init_finish)) return false;
    return true; 
}

bool SorterTree::QuicksortWithInsert(int start, int finish){
    if(start >= finish) return true;
    int init_start = start, init_finish = finish;
    Journey *pivot = choosePivot(array, start, finish);
    if(pivot == NULL) return false;
    tree->insert(*pivot); //to insert the current pivot in the tree
    Journey pivot_val = *pivot;
    while(true){
        while(array[start] < pivot_val){
            start++; comparisons++;
            if(start > init_finish) return false;
        }
        while(array[finish] > pivot_val){
            finish--; comparisons++;
            if(finish < init_start) return false;
        }
        if(start < finish){
            Journey temp = array[finish];
            array[finish] = array[start];
            array[start] = temp;
        }
        else break;
    }
    //if(start - 1 == init_finish || finish + 1 == init_start) return false;
    if(!QuicksortWithInsert(init_start, start-1)) return false;
    if(!QuicksortWithInsert(start+1, init_finish)) return false;
    return true;   
}

void SorterTree::printArray(){
    cout << "Code" << " " << "Price" << endl;
    for(int i = 0; i < size; i++){
       cout << array[i];
    }
    cout << endl;
}

void SorterTree::printTree(){
    tree->printBST("", false);
}

BST* SorterTree::getTree(){return tree;}

Journey *SorterTree::getArray(){return array;}
