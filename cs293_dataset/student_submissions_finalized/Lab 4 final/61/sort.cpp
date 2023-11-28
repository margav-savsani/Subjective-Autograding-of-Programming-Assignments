#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
int SorterTree::getcomp(){
    	return comparisons;
}

void SorterTree::printTree(){
    	tree->printBST("");
        
}
bool SorterTree::insert(Journey entry){
    if(cardinality >=l){
        return false;
    }
    array[cardinality]=entry;
    cardinality++;
    return true;
}
BST* SorterTree::getTree(){
    return tree;
}
SorterTree::SorterTree(int choice, int l){
        this->choice=choice;
        this->l=l;
        array=new Journey[l];
        cardinality=0; 
        comparisons=0;
        tree=new BST();

}

void SorterTree::Quicksort(int start, int end)
{
  if (start >= end)
        {return;}

   Journey pivot = *getPivot(start,end);
 
    int less = 0,p_org;
    for (int i = start ; i <= end; i++) {
        if (array[i]< pivot)
            less++;
        if(array[i]==pivot){
            p_org=i;
        }
    }
 
    int p = start+less;
    struct Journey temp=array[p];
    array[p]=pivot;
    array[p_org]=temp;
 
    int i = start, j = end;
 
    while (i<p && j>p) {
 
        while (!(array[i]> pivot)) {
            i++;
            comparisons++;
        }
        while(array[j]>pivot) {
            j--;
            comparisons++;
        }
        comparisons=comparisons+2;
        if (i<p && j>p) {
            struct Journey temp=array[i];
            array[i]=array[j];
            array[j]=temp;
            i++;
            j--;
        }
    }
    Quicksort(start,p-1);
    Quicksort(p,end);
}

void SorterTree::QuicksortWithBSTInsert(int start, int end)
{
    if (start >= end)
    {
        if(start==end){
            tree->insert(array[start].getJourneyCode(),array[start].getPrice()); 
        }
        return;
    }

   Journey pivot = *getPivot(start,end);
 
    int less = 0,p_org;
    for (int i = start; i <= end; i++) {
        if ((array[i]<pivot))
            less++;
        if(array[i]==pivot){
            p_org=i;
        }
    }
 
    int p = start+less;
    struct Journey temp=array[p];
    array[p]=pivot;
    array[p_org]=temp;
 
    int i = start, j = end;
    while (i<p && j>p) {
 
        while (!(array[i]> pivot)) {
            i++;
              comparisons++;
        }
          comparisons++;
        while(array[j]>pivot) {
            j--;
              comparisons++;
        }
          comparisons++;
        if (i<p && j>p) {
            struct Journey temp=array[i];
            array[i]=array[j];
            array[j]=temp;
            i++;
            j--;
        }
    }
    tree->insert(array[p].getJourneyCode(),array[p].getPrice());
    QuicksortWithBSTInsert(start,p-1);
    QuicksortWithBSTInsert(p+1,end);
}

bool SorterTree::printArray()
{  
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
