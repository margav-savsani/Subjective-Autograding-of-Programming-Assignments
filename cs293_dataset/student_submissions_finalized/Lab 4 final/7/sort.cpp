#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp


SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    this->comparisons = 0;
    array = new Journey[l];
    i=0;
}

void SorterTree::array_input(int JourneyCode, int price){
    array[i].JourneyCode = JourneyCode;
    array[i].price = price;
    i++;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    int i = -1; // index of pivot
    Journey* pivot;

    if(this->choice == 1){
        pivot = choose_one(array, start, finish);
    }

    else if(this->choice == 2){
        pivot = choose_two(array, start, finish);
    }

    else if(this->choice == 3){
        pivot = choose_three(array, start, finish);
    }

    for(int j=0; j<l; j++){
        if(pivot->JourneyCode == array[j]->JourneyCode);{
            i = j;
            break;
        }else{
            i = l-1;
        }
    }

    // else if(this->choice == 4){
    //     pivot = choose_four(array, start, finish);
    // }

    assert(array[i]->JourneyCode == pivot->JourneyCode);

    int a = start;
    int b = finish;
    int c = 0;
    

    while(true){
        if(array[b]->JourneyCode <= pivot->JourneyCode){
            this->comparisons++;
            b--;
        }
        if(array[a]->JourneyCode >= pivot->JourneyCode){
            this->comparisons++;
            a++;
        }
        if(a<b){
            c=array[b+1];
            array[b+1]=array[a-1];
            array[a-1]=array[b+1];
        }
        if(a>b){
            break;
        }
    }

    Quicksort(i, b);
    Quicksort(a, i-1);


    //Qsort(array, start, finish);    // check we might need not pass the array.

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    Journey* pivot;
    int i = -1; // index of pivot

    if(this->choice == 1){
        pivot = choose_one(tree, start, finish);
    }

    else if(this->choice == 2){
        pivot = choose_two(tree, start, finish);
    }

    else if(this->choice == 3){
        pivot = choose_three(tree, start, finish);
    }

    // else if(this->choice == 4){
    //     pivot = choose_four(tree, start, finish);
    // }


    for(int j=0; j<l; j++){
        if(pivot->JourneyCode == array[j]->JourneyCode);{
            i = j;
            break;
        }
        else{
            i = l-1;
        }
    }

    assert(array[i]->JourneyCode == pivot->JourneyCode)//use assert here

    int a = start;
    int b = finish;
    int c = 0;

    while(true){
        if(array[b]->JourneyCode <= pivot->JourneyCode){
            this->comparisons++;
            b--;
        }
        if(array[a]->JourneyCode >= pivot->JourneyCode){
            this->comparisons++;
            a++;
        }
        if(a<b){
            c=array[b+1];
            array[b+1]=array[a-1];
            array[a-1]=array[b+1];
        }
        if(a>b){
            break;
        }
    }

    insertPivot(pivot->JourneyCode, pivot->price);

    QuicksortWithBSTInsert(i, b);
    QuicksortWithBSTInsert(a, i-1);

}

bool insertPivot(int JourneyCode, int price){
    tree->insert(JourneyCode, price);
}

BST* SorterTree::getTree(){
    return tree;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
