#include "sort.h"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice,int l){
    assert(0<=choice&&choice<=4);
    this->choice=choice;
    if(l>0) {
        tree=new BST;
        comparisons=0;
        this->l=l;
        array=new Journey[l];

    }
    else{
        this->l=-1;
    }
    
}

int SorterTree::Partition(Journey* A, int a, int b) {
    Journey* x;
    switch(choice){
        case(1):
          x=choose_one(array,a,b);
          break;
        case(2):
          x=choose_two(array,a,b);
          break;
        case(3):
          x=choose_three(array,a,b);
          break;
        
    }
    int i=a;
    int j=b;
    while(true) {
        while(!(A[j]<*x)) {
            j--;
            comparisons++;
        }
        while(!(*x<A[i])) {
            i++;
            comparisons++;
        }
        if(i<j) {
           Journey temp;
           temp=A[i];
           A[i]=A[j];
           A[j]=temp;
        }
        else return j;
    }
}
bool SorterTree::Quicksort1(int start,int finish){
    if(start>finish) {
        return false;
    }
    else if(start==finish) {
        return true;
    }
    else{
        int divider;
        divider=Partition(array,start,finish);
        return (Quicksort1(start,divider)&&Quicksort1(divider+1,finish));
    }
    
}
bool SorterTree::Quicksort(int start, int finish)
{   bool b;
    b=Quicksort1(start,finish);
    cout<<comparisons<<endl;
    return Quicksort1(start,finish);
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}
bool SorterTree::QuicksortWithBSTInsert1(int start,int finish){
    if(start>finish) {
        return false;
    }
    else if(start==finish) {
        return true;
    }
    else{
        int divider;
        divider=Partition(array,start,finish);
        tree->insert(array[divider].getJourneyCode(),array[divider].getPrice());
        return (QuicksortWithBSTInsert1(start,divider)&&QuicksortWithBSTInsert1(divider+1,finish));
        

    }
}
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    bool p;
    p=QuicksortWithBSTInsert1(start,finish);
    cout<<comparisons<<endl;
    return p;
}
BST* SorterTree::getTree() {
    return tree;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
