#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree :: SorterTree (int choice, int l){
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    comparisons=0;
    tree=new BST(); 
    
}
bool SorterTree::Quicksort(int start, int finish)
{  int k;
   if(start<finish){ 
     k=partition(start,finish);    // Call appropriate pivot function based on choice 
     Quicksort(start,k);
     Quicksort(k+1,finish);         // Split into 2 parts based on pivot choice
            }                     // Recursively keep sorting
    return true;

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
   int k;
   if (start>finish) return true;
    
        // Call appropriate pivot function based on choice
     Journey* j;
    
    if(choice==1){
        j=choose_one(array,start,finish);
    }
     else if(choice==2){
        j=choose_two(array,start,finish);
    }
    else if(choice==3){
        j=choose_three(array,start,finish);
    }
    
    insertPivot(j->getJourneyCode(), j->getPrice());
    if(start==finish) return true;
     k=partition(start,finish); 
     QuicksortWithBSTInsert(start,k);
     QuicksortWithBSTInsert(k+1,finish);         // Split into 2 parts based on pivot choice
               
     return true;                           // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}


int SorterTree::partition(int p,int r){
    Journey* x;
    if(choice==1){
        x=choose_one(array,p,r);
    }
     if(choice==2){
        x=choose_two(array,p,r);
    }
     if(choice==3){
        x=choose_three(array,p,r);
    }
    int a=x->getJourneyCode();
    int b=x->getPrice();
    int i=p;
    int j=r;
    Journey T(a,b);
    while(1){
        while(T<array[j]){
            j--;
            comparisons++;
        }
        while(array[i]<T){
            i++;
            comparisons++;
        }
      
        if(i<j){
           
            Journey k =array[i];
            array[i]=array[j];
            array[j]=k;
        }
        else if(j==r) return j-1;
        else return j;
    }

}
void SorterTree::arrinsert(int j,Journey k){
    array[j]=k;
     cout<<"inserted"<<endl;
    return;
}
 bool SorterTree::insertPivot(int JourneyCode, int price){
     
   tree->insert(JourneyCode,price);
   return true;
 } // insert node corresponding to chosen pivot in BST

int SorterTree:: getcomp(){
    return comparisons;
}
int SorterTree:: getimb(){
    return tree->getImbalance();
}

void SorterTree::drawbst(){
    
     tree->printBST(" ");
     return;
}