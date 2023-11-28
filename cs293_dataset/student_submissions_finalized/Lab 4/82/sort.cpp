#ifndef SORT_CPP
#define SORT_CPP


#include "sort.h"
#include <iostream>
// #include "choose.h"

// Code up the functions defined in sort.cpp


void SorterTree::inputArray(){
    array = new Journey[l];
    unsigned int j, c;
    for(int i=0; i<l; i++){
        cin>>c;
        cin>>j;
        array[i].setParams(c, j);
    }

}

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
}

void swap(Journey* A, int a, int b){
    Journey temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

Journey* choos(Journey* A, int start, int finish){
    int index = (start+finish)/2;
    int temp = 0;
    while(temp != index){
            
    }
}

int SorterTree::Partition(Journey* A, int start, int finish){
    Journey* jour = choos(A, start, finish);

    int index=0;
    for(index; (A[index].getJourneyCode() == jour->getJourneyCode() && A[index].getPrice() == jour->getPrice()); index++);

    swap(A, start, index);

    int i=start, j=finish;
    while(i < j){
        while(A[i] < *jour){
            i++;
        }
        while(!(A[j] < *jour)){
            j--;
        }
        swap(A, i, j);
    }
    return i;
}


bool SorterTree::Quicksort(int start, int finish)
{
    if(start < finish){
        int p = Partition(array, start, finish);
        Quicksort(start, p);
        Quicksort(p, finish);
        return true;
    }

    else{
        return false;
    }
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

int main(){
    int c, l;

    SorterTree s(c, l);
    s.inputArray();
    s.printArray();
    s.Quicksort(0, s.getSize());
    s.printArray();
}

#endif