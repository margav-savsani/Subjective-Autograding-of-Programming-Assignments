#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int Choice,int L){
    array = new Journey[L];
    choice = Choice;
    l=L;
    comparisons = 0;
    tree = new BST();
}
SorterTree::~SorterTree(){
    ;
}
 
void SorterTree::insert(int j,int p,int idx){
    array[idx] = Journey(j,p);
}

void SorterTree::Quicksort(int start, int finish)
{   if(start>=finish){
       return;
    }
    Journey* pivot;
    if(choice==1){pivot = choose_one(array,start,finish);}
    else if(choice==2){pivot = choose_two(array,start,finish);}
    else if(choice==3){pivot = choose_three(array,start,finish);}
    else;
    int pivotindex;
    int i=start;
    int j=finish;
    while (true){
        while (array[i]<*pivot){
            i++;
            comparisons++;
        }
        while (array[j]>*pivot){
            j--;
            comparisons++;
        }
        if(i<j){
            Journey temp(5,20);
            temp*array[i];
            array[i]*array[j];
            array[j]*temp;
        }
        else{
            pivotindex=i;
            break;
        };
    }
    Quicksort(start,pivotindex-1);
    Quicksort(pivotindex+1,finish);
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

void SorterTree::QuicksortWithBSTInsert(int start, int finish)
{   if(start>=finish){
       return;
    }
    Journey* pivot;
    if(choice==1){pivot = choose_one(array,start,finish);}
    else if(choice==2){pivot = choose_two(array,start,finish);}
    else if(choice==3){pivot = choose_three(array,start,finish);}
    else;
    tree->insert(pivot->getJourneyCode(),pivot->getPrice());
    int pivotindex;
    int i=start;
    int j=finish;
    while (true){
        while (array[i]<*pivot){
            i++;
            comparisons++;
        }
        while (array[j]>*pivot){
            j--;
            comparisons++;
        }
        if(i<j){
            Journey temp(5,20);
            temp*array[i];
            array[i]*array[j];
            array[j]*temp;
            if(array[i]+*pivot || array[j]+*pivot){
                i=start;
                j=finish;
        }}
        else {
            pivotindex=i;
            break;
        };
    }
    QuicksortWithBSTInsert(start,pivotindex-1);
    QuicksortWithBSTInsert(pivotindex+1,finish);

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}
void SorterTree::getTree(){
    tree->printBST("");
    return;
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return;
}
