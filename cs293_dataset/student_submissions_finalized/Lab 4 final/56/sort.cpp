#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){    //constructor
    this->choice = choice;
    assert(choice >= 1 && choice <= 4);    //1 <= choice <= 4;
    this->l = l;
    array = new Journey[l];    //initialize the array
    tree = new BST;
    comparisons = 0;   //what about int* codes??
    curr_elts = 0;
}

BST* SorterTree::getTree(){
    return tree;
}

bool SorterTree::Quicksort(int start, int finish){    //quicksort and then return comparisons
    //assert(start >= 0 && finish <= l-1);
    if(!QuicksortInter(start, finish)) return false;       //failed to quicksort, array already sorted
    
    //comparisons = 0;
    return true;
}

int SorterTree::getComparisons(){
    return comparisons;
}

bool SorterTree::QuicksortInter(int start, int end)   //helper quicksort
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // assert(start >= 0 && finish < l);
    
    if(start > end){   //invalid case
        return false;
    }
    Journey* pivot;     
    if(choice == 1){pivot = choose_one(array, start, end);}     //choose pivot from choice functions
    else if(choice == 2){pivot = choose_two(array, start, end);}
    else if(choice == 3){pivot = choose_three(array, start, end);}
    else if(choice == 4){pivot = choose_four(array, start, end);}
    if(pivot == nullptr){
        return false;
    }    
    if(start == end){       //base case, dont quicksort
        tree->insert(pivot->getJourneyCode(), pivot->getPrice());        
        return true;
    }
    tree->insert(pivot->getJourneyCode(), pivot->getPrice());
    
    
    int margin = Partition(start, end, pivot);   //partition the array based on pivot
    
    if(margin == -1){            
        return false;
    }
    bool res1 = false;
    bool res2 = false;
    if(margin == end){    //margin is at the end, neglect the last element in the next quicksort
        res1 = QuicksortInter(start, margin-1);
        //return false;
    }
    else{    //recursively quicksort both arrays
        res1 = QuicksortInter(start, margin);       
    }
    res2 = QuicksortInter(margin+1, end);
    if(!res1 && !res2){
        
        return false;
    }
    return true;
}

int SorterTree::Partition(int start, int end, Journey* pivot){    
    
    int i = start;
    int j = end;
    int previ = -1;
    int prevj = -1;
    while(true){
        
        while(array[i] < *pivot && i < end){    //increment until an element more than pivot is found
            comparisons++;
            i++;
        }
        comparisons++;
        while(array[j] > *pivot && j > start){    //decrement until an element less than pivot is found
            j--;
            comparisons++;
        }
        comparisons++;
        if(previ == i && prevj == j){return -1;}      //unable to sort, return  
        previ = i; prevj = j;

        if(j<=i){            
            return j;
        }
        
        else{
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }   
}
    
}

void SorterTree::insertJourney(int JourneyCode, int price){      //insert journey in the array
    array[curr_elts] = Journey(JourneyCode, price);
    curr_elts++;
    assert(curr_elts <= l);
}

bool SorterTree::insertPivot(int JourneyCode, int price){   //unused
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)   //unused
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    return false;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return false;
}
