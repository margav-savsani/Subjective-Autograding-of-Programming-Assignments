#include "sort.h"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.cpp
BST *b1 = new BST();   // define a tree where pivots have to be inserted 

SorterTree:: SorterTree(int choice, int l, Journey *array){
    this->choice=choice;
    this->l=l;
    this->array=array;
    comparisons=0;
}


bool SorterTree::Quicksort(int start, int finish)  // implement quick sort
{  
    if (start<finish)
     {int q=partition (array,start,finish);
      Quicksort (start,q);
     Quicksort(q+1,finish);}
     // else{cout<< comparisons<<endl;}
      return true;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

int SorterTree::partition(Journey * A,int p , int r){  // partition function
 Journey *pivot;
 if (choice==1){    // choose from the given functions
   pivot= choose_one(array,p,r);}
   if (choice==2){
   pivot= choose_two(array,p,r);}
   if (choice==3){
   pivot= choose_three(array,p,r);}

  Journey piv=*pivot;
  *pivot=A[r];
   A[r]=piv ;
   
   int limit=r;
   int x=A[r].getJourneyCode();
   Journey y=A[r];
    int i=p-1;
    int j=r+1; 
   
    while(1){
        while(1){
            j--;
            comparisons ++;
            if ( A[j].operator<(y) || A[j].getJourneyCode()==x ){
                break;
            }
        }
        while(1){
            i++;
            comparisons ++;
            if ( y.operator<(A[i]) || A[i].getJourneyCode()==x ||i>limit){
                break;
            }
        }
       
        if( i<=j){
        Journey temp =A[i];
        A[i]=A[j];
        A[j]= temp;}
         else{return j;}
         
   }
}


bool SorterTree:: insertPivot(int JourneyCode, int price){
    b1->insert (JourneyCode,price);
    return true;
}
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{    if (start<finish)
     {int q=partition_ins (array,start,finish);
      QuicksortWithBSTInsert (start,q);
      QuicksortWithBSTInsert(q+1,finish);}
       return true; 
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

void SorterTree:: get_tree(){   // print the BST 
    b1->printBST("",false);
}

int SorterTree::partition_ins(Journey * A,int p , int r){
 Journey *pivot;
 if (choice==1){
   pivot= choose_one(array,p,r);}
   if (choice==2){
   pivot= choose_two(array,p,r);}
   if (choice==3){
   pivot= choose_three(array,p,r);}
   
  Journey piv=*pivot;
  *pivot=A[r];
   A[r]=piv ;
   insertPivot(piv.getJourneyCode(),piv.getPrice());

   int limit=r;
   int x=A[r].getJourneyCode();
   Journey y=A[r];
    int i=p-1;
    int j=r+1; 
   
    while(1){
        while(1){
            j--;
            comparisons ++;
            if ( A[j].operator<(y) || A[j].getJourneyCode()==x ){
                break;
            }
        }
        while(1){
            i++;
            comparisons ++;
            if ( y.operator<(A[i]) || A[i].getJourneyCode()==x ||i>limit){
                break;
            }
        }
        
        if( i<=j){
        Journey temp =A[i];
        A[i]=A[j];
        A[j]= temp;}
         else{return j;}
         
   }
}

int SorterTree::get_comp(){   // get total cost of comaparisons
    int comp=comparisons;
    return comp;
};
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
