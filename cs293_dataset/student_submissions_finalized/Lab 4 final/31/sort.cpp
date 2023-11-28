#include "sort.h"
#include <iostream>

SorterTree::SorterTree(int choice, int l){
    array=new Journey[l];
    tree=new BST;
    this->choice=choice;
    this->l=l;
    i=0;
    comparisons=0;
}

SorterTree::~SorterTree(){
    return;
}

int SorterTree::getTail(){
    return i;
}

bool SorterTree::insertJourney(int JourneyCode, int price){
    assert(i<l);
    Journey j(JourneyCode,price);
    array[i]=j;
    i++;
}
// Code up the functions defined in sort.cpp
int SorterTree::partition(int first, int last, Journey j){
    int l = last;
    int f = first;
    while(true){
        while(!(array[l]<j || array[l].getJourneyCode()==j.getJourneyCode())){
            comparisons++;
            l--;
        }
        while(!(array[f]>j || array[f].getJourneyCode()==j.getJourneyCode())){
            comparisons++;
            f++;
        }

        if(f<l){
            Journey a = array[f];
            array[f] = array[l];
            array[l] = a;
            f++;
            l--;
        }
        else return l;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start>=finish){
        return false;
    }
    if(start<finish){
        Journey j;
        Journey* q;
        if(choice==1){
            q = choose_one(array, start, finish);
            j =  *q;
        }
        if(choice==2){
            q = choose_two(array, start, finish);
            j =  *q;
        }
        if(choice==3){
            q = choose_three(array, start, finish);
            j =  *q;
        }
        int p=partition(start,finish,j);
        if(p==finish){
            Quicksort(start, p-1);
            Quicksort(p,finish);
        }
        else {
            Quicksort(start, p);
            Quicksort(p+1,finish);
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
    if(start>=finish){
        return false;
    }

    if(start<finish){
        Journey j;
        Journey* q;
        if(choice==1){
            q = choose_one(array, start, finish);
            j =  *q;
        }
        if(choice==2){
            q = choose_two(array, start, finish);
            j =  *q;
        }
        if(choice==3){
            q = choose_three(array, start, finish);
            j =  *q;
        }
        insertPivot(j.getJourneyCode(), j.getPrice());
        int p=partition(start,finish,j);
        if(p==finish){
            QuicksortWithBSTInsert(start, p-1);
            QuicksortWithBSTInsert(p,finish);
        }
        else {
            QuicksortWithBSTInsert(start, p);
            QuicksortWithBSTInsert(p+1,finish);
        }
    }
    return true;

}

bool SorterTree::insertPivot(int JourneyCode, int price){
    tree->insert(JourneyCode, price);
}
bool SorterTree::printArray()
{   cout << "comparisons: " <<comparisons<< endl;
    comparisons=0;
    for (int i = 0; i < this->i; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

BST* SorterTree::getTree(){
    return tree;
}
