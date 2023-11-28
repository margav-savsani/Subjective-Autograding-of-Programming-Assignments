#include "sort.h"
#include "choose.h"
#include <iostream>
#include <cassert>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    comparisons = 0;
    array = new Journey[l];
    int code, price;
    ifstream fl;
    fl.open("sample-input.txt");
    for (int i = 0; i < l; i++){
        fl >> code >> price;
        array[i] = Journey(code, price);
    }
    fl.close();
}

void SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start < finish){

        Journey *pivot = nullptr;
        int pos;
        
        if (choice == 1) pivot = choose_one(array, start, finish);
        else if (choice == 2) pivot = choose_two(array, start, finish);
        else if (choice == 3) pivot = choose_three(array, start, finish);
        else if (choice == 4) pivot = &array[(start + finish) / 2];

        int i = start;
        int j = finish;

        for (int k = start; k <= finish; k++){
            if (pivot->getJourneyCode() == array[k].getJourneyCode() && pivot->getPrice() == array[k].getPrice()){
                pos = k;
                break;
            }
        }
        assert(pos >= start && pos <= finish);

        Journey tmp = array[pos];
        array[pos] = array[finish];
        array[finish] = tmp;
        pos = finish;

        int code = array[pos].getJourneyCode();

        while (true){
            while (array[i].getJourneyCode() <= code){
                i++;
                comparisons ++;
            }

            while (array[j].getJourneyCode() > code){
                j--;
                comparisons ++;
            }

            if (i < j){
                Journey tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
            else{
                break;
            }
        }

        for (int k = start; k <= finish; k++){
            if (array[k].getJourneyCode() > code){
                pos = k;
                break;
            }
        }
        Quicksort(start, pos - 1);
        Quicksort(pos, finish);
    }
    return;
}

void SorterTree::getComparisons(){
    cout << comparisons << endl;
    return;
}

void SorterTree::QuicksortWithBSTInsert(BST *tree, int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    if (start < finish){

        Journey *pivot = nullptr;
        int pos;
        
        if (choice == 1) pivot = choose_one(array, start, finish);
        else if (choice == 2) pivot = choose_two(array, start, finish);
        else if (choice == 3) pivot = choose_three(array, start, finish);
        else if (choice == 4) pivot = &array[(start + finish) / 2];

        int i = start;
        int j = finish;

        for (int k = start; k <= finish; k++){
            if (pivot->getJourneyCode() == array[k].getJourneyCode() && pivot->getPrice() == array[k].getPrice()){
                pos = k;
                break;
            }
        }
        assert(pos >= start && pos <= finish);
        tree->insert(array[pos].getJourneyCode(), array[pos].getPrice());

        Journey tmp = array[pos];
        array[pos] = array[finish];
        array[finish] = tmp;
        pos = finish;

        int code = array[pos].getJourneyCode();

        while (true){
            while (array[i].getJourneyCode() <= code){
                i++;
                comparisons ++;
            }

            while (array[j].getJourneyCode() > code){
                j--;
                comparisons ++;
            }

            if (i < j){
                Journey tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
            else{
                break;
            }
        }

        for (int k = start; k <= finish; k++){
            if (array[k].getJourneyCode() > code){
                pos = k;
                break;
            }
        }
        QuicksortWithBSTInsert(tree, start, pos - 1);
        QuicksortWithBSTInsert(tree, pos, finish);
    }
    return;
}

void SorterTree::getImbalance(BST *tree){
    cout << tree->getImbalance() << endl;
    return;
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

SorterTree::~SorterTree(){}