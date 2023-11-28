#include "sort.h"
#include <iostream>

SorterTree::SorterTree(int choice, int l, string file){
    this->choice=choice;
    this->l=l;
    array = new Journey[l];
    tree = new BST();
    comparisons=0;
    ifstream ist;
    ist.open(file);
    for (int i=0; i<l; i++){
        int code, price;
        ist >> code >> price;
        add(i,code,price);
    }
}

SorterTree::~SorterTree(){
    delete[] array;
    delete tree;
}

int SorterTree::getComp(){
    return comparisons;
}

// Code up the functions defined in sort.cpp
bool SorterTree::swap(Journey *a, Journey *b){
    Journey t=*b;
    *b = *a;
    *a = t;
    cout << "swapping " << a->getJourneyCode() << " " << b->getJourneyCode() << endl;
    return true;
}

int SorterTree::partition(int start, int finish, int flag){

    Journey *pivot; 

    switch (choice){
        case 1:
            pivot = choose_one(array, start, finish);
            break;
        case 2:
            pivot = choose_two(array, start, finish);
            break;
        case 3:
            pivot = choose_three(array, start, finish);
            break;
    }

    if (pivot - array >= l || pivot - array <0){
        cout << "Index goes out of range, plz use proper choose function !!!!" << endl;
        exit(0);
    } 

    if (flag != 0){
        insertPivot(pivot->getJourneyCode(), pivot->getPrice());
        //tree->printBST("");
        //cout << tree->getshortest() << " " << tree->getlongest() << endl;
        //cout << tree->getImbalance() << endl;
    }

    if (!(pivot->getJourneyCode() == array[finish].getJourneyCode())){
        swap(pivot, &array[finish]);
    }
    
    
    int i = (start - 1);
 
    for (int j = start; j <= finish - 1; j++) {
        comparisons++;
        if (array[j] < array[finish]) {
            i++;
            if (!(array[i].getJourneyCode() == array[j].getJourneyCode())){
                swap(&array[i], &array[j]);
            }
        }
    }
    if (!(array[i+1].getJourneyCode() == array[finish].getJourneyCode())){
        swap(&array[i + 1], &array[finish]);
    }
    return (i + 1);
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start <= finish) {
        /* Partitioning index */
        int p = partition(start, finish, 0);
        Quicksort(start, p - 1);
        Quicksort(p + 1, finish);
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if (start <= finish) {
        /* Partitioning index */
        int p = partition(start, finish, 1);
        QuicksortWithBSTInsert(start, p - 1);
        QuicksortWithBSTInsert(p + 1, finish);
    }
    return true;
}

bool SorterTree::add(int i, int val){
    Journey j(val,100-val);
    array[i]=j;
    return true;
}

bool SorterTree::add(int i, int code, int price){
    Journey j(code, price);
    array[i]=j;
    return true;
}

BST *SorterTree::getTree(){
    return tree;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode,price);
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
