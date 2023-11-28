#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

void SorterTree::partition(Jorney *A,int p,int q){
   i=choice;
   int x=A[q];
   int i=p-1;
   int j=r-1;
   while(true){
             while (A[j]<=x){j=j-1;}
             while (A[i]>=x){i=i+1;}
             if (i<j) { int b=A[i];
                         A[i]=A[j];
                         A[j]=b;
                       }
             else return j;
 }}
void SorterTree::sort(Journey *A,int p,int q){
  if(p<r) { q=partition(A,p,q);
            sort(A,p,q)
            sort(A,p+1,q);}
  return;
bool SorterTree::Quicksort(int start, int finish)
{    
    sort(array,1,l);
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
