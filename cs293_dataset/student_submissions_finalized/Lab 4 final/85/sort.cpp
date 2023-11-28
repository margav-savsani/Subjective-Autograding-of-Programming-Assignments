#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    comparisons=0;
   tree= new BST;
   check=0;
     int** che;
}
SorterTree::~SorterTree(){}
void SorterTree::add(int JourneyCode,int price,int ind){
     Journey n(JourneyCode,price);
     array[ind]=n;
     return;


}
BST* SorterTree::getTree(){
    return tree;
}

int SorterTree::partition(int start,int finish){
    Journey* t;
    if(choice==1){
        t=choose_one(array,start, finish);
        
    }
    if(choice==2)
{
    t=choose_two(array,start, finish);

}
    if(choice==3){
        t=choose_three(array,start, finish);
    }
    int i=0;
    Journey jou= *t;
    *t=array[finish];
    array[finish]=jou;
    Journey x=array[finish];
    int v=start;
    int j=finish;
    while(true){
        while(x<array[j]){
            j=j-1;
            comparisons++;
        }
        while(array[v]<x){
            v=v+1;
            comparisons++;
        }
        comparisons++;
        if (v<j){
            
            Journey n=array[j];
            array[j]=array[v];
            array[v]=n;
            }
        else {return j;}
    } 
}
bool SorterTree::Quicksort(int start, int finish)
{
     if (start<finish){
        int q= partition(start,finish);
         Quicksort(start,q);
        Quicksort(q+1,finish);
        
       
        return true;    
     } 
     else{return false;}
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
      if (start<finish){
        int q= partition(start,finish);
        
        
        QuicksortWithBSTInsert(start,q);
         QuicksortWithBSTInsert(q+1,finish);
        
          Journey n=array[q];
        
          che[check][1]= n.getJourneyCode();
          che[check][2]=n.getPrice(); 
          cout<<che[check][1]<<endl;
          check++;
          
         return true;
     } 
     
     else{return false;}
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}
void SorterTree::compare(){
    cout << comparisons<<endl;
}
bool SorterTree::insertPivot(int JourneyCode,int price){
     
     return tree->insert(JourneyCode,price);
     
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
