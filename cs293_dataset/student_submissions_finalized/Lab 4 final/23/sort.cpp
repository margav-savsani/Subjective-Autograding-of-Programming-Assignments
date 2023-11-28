#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
                       array = new Journey[l];
                       this->choice=choice;
                       this->l=l;
                       comparisons=0;
                       };
int SorterTree::partition(int start, int finish)
{  Journey *pivot;
   if (choice==1)
      pivot=choose_one(array,start,finish);
   else if (choice==2)
            pivot=choose_two(array,start,finish);
   else 
       pivot=choose_three(array,start,finish);
    Journey *x=pivot;
    int i = start;
    int j = finish;
    while (true){
          while(!(array[j].getJourneyCode() <= x->getJourneyCode())) {
               comparisons++;
               j=j-1;
               }
          while(!(array[i].getJourneyCode() >=  x->getJourneyCode())) {
               comparisons++;
               i=i+1;
               }
          if (i<j){
             Journey a;
             a=array[i];
             array[i]=array[j];
             array[j]=a;}
          else return j;
          }
    
}
bool SorterTree::Quicksort(int start, int finish){
     if (start<finish){
        int q=partition(start,finish);
        Quicksort(start,q);
        Quicksort(q+1,finish);
        return true;}
     else return false;
    }
int SorterTree::partitionBST(int start, int finish)
{  Journey *pivot;
   if (choice==1)
      pivot=choose_one(array,start,finish);
   else if (choice==2)
            pivot=choose_two(array,start,finish);
   else 
       pivot=choose_three(array,start,finish);
    Journey *x=pivot;
    tree->insert(x->getJourneyCode(),x->getPrice());
    int i = start;
    int j = finish;
    while (true){
          while(!(array[j].getJourneyCode() <=  x->getJourneyCode())) {
               comparisons++;
               j=j-1;
               }
          while(!(array[i].getJourneyCode() >= x->getJourneyCode())){
               comparisons++;
               i=i+1;
               }
          if (i<j){
             Journey a;
             a=array[i];
             array[i]=array[j];
             array[j]=a;}
          else return j;
          }}

bool SorterTree:: QuicksortWithBSTInsert(int start, int finish)
{
    if (start<finish){
        int q=partitionBST(start,finish);
        QuicksortWithBSTInsert(start,q);
        QuicksortWithBSTInsert(q+1,finish);
        return true;}
     else return false;
}

BST* SorterTree::getTree()
{
     return tree;
}
int SorterTree::comp(){
    return comparisons;
    }
Journey* SorterTree::arr(){
    return array;
    }
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
