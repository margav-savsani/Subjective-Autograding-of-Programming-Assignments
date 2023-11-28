#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int SorterTree:: Partition(Journey* A,int start,int finish){
if (choise==1){
 Journey* p=choose_one(Journey* array, int start, int finish);}

if (choise==2){
 Journey* p=choose_two(Journey* array, int start, int finish);}

if (choise==3){
 Journey* p=choose_three(Journey* array, int start, int finish);}

if (choise==4){
 Journey* p=choose_four(Journey* array, int start, int finish);}
    
    Journey x=*p;
    
    i=start-1;
    j=finish+1;
    while(true){
     while(A[j]<=x){
     j=j-1;
     }
     while(A[i]>=x){
     i = i+1;
     }
     if (i<j){
           Journey temp=A[j];
           A[j]=A[i];
           A[i]=A[j];
     }
     else return j;
}

bool SorterTree::Quicksort(int start, int finish)
{   if (start<finish){
             
         
   
     
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
