#include "sort.h"
#include <iostream>
using namespace std;
// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice,int l){
    array=new Journey(l);

}
int SorterTree::Partition(Journey* A, int a, int b) {
    Journey x;
    x=A[b];
    int i=a;
    int j=b;
    while(true) {
        while(!A[j]<x) {
            j--;
            comparisons++;
        }
        while(A[i]<x) {
            i++;
            comparisons++;
        }
        if(i<j) {
           Journey temp;
           temp=A[i];
           A[i]=A[j];
           A[j]=temp;
        }
        else{
            return j;
        }
    }
}
bool SorterTree::Quicksort1(int start,int finish){
    assert((start<finish)&&(start>=0)&&(finish)<l);
    if(start<finish){
        int divider;
        divider=Partition(array,start,finish);
        return Quicksort(start,divider);
        return Quicksort(divider+1,finish);

    }
    else return false;
}
bool SorterTree::Quicksort(int start, int finish){
    bool b;
    b=Quicksort1(start,finish);
    cout<<comparisons<<endl;
    return Quicksort1(start,finish);
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
    Journey* j;
    switch(choice){
        case(1):
          j=choose_one(array,start,finish);
          break;
        case(2):
          j=choose_two(array,start,finish);
          break;
        case(3):
          j=choose_three(array,start,finish);
          break;
        case(4):
          j=choose_four(array,start,finish);
          break;
    }


}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
