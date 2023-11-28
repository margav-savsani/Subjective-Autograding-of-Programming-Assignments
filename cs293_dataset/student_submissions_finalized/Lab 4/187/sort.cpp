#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
}
int part(Journey *A, int s, int f){
    Journey *x;
    if(choice == 1){
        x = choose_one(A,s,f);
    }
    else if(choice == 2){
        x = choose_two(A,s,f);
    }
    else if(choice == 3){
        x = choose_three(A,s,f);
    }
    else if(choice == 4){
        x = choose__four(A,s,f);
    }
    Journey a;
    a = *x;
    int i,j;
    i = s-1;
    j = f+1;
    while(true){
        while(j >= s){
            if(A[j] < a) break;
            j = j-1;
        }
        while(i < f){
            if(a <  A[i]){break;}
            i++;
        }
        if(i < j){
            swap(A[i],A[j]);
        }         
        else{
            return j;
        }
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    int q = part(array,start,finish);
    if(start > finish){
        return false;        
    }
    else if(start == finish){
        return true;
    }
    else{
        Quicksort(start,q);
        Quicksort(q+1,finish);
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish,Journey *A)
{
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
