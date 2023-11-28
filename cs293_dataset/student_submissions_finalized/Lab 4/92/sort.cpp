#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int ch,int n){//constructor for sortertree
    choice=ch;
    l=n;
}
void SorterTree::partition(int BSTornot,int start,int finish){
Journey x;
    if(choice==1){x=*choose_one(array,start,finish);}
    else if(choice==2){x=*choose_two(array,start,finish);}
    else if(choice==3){x=*choose_three(array,start,finish);}
    else if(choice==4){x=*choose_four(array,start,finish);}
    if(BSTornot){}
    else{bool wa=insertPivot(x.getJourneyCode,x.getPrice);}
    int i=start;
    int j=finish;int mi;
    while(true){
        while(x<array[j]){j=j-1;}
        while(array[i]<x){i=i+1;}
        if(i<j){
            Journey mid(array[i].getJourneyCode(),array[i].getPrice());
            array[i]=array[j];
            array[j]=mid;
        }
        else {mi=j;}
    }
    partition(BSTornot,start,mi);partition(BSTornot,mi+1,finish);
}
bool SorterTree::Quicksort(int start, int finish)
{  if(start>finish){return 0;}
    else {partition(0,start,finish);
        return 1;}
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{   if(start>finish){return 0;}
    else{
        partition(1,start,finish);
        return 1;
        }
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

bool SorterTree::insertPivot(int JourneyCode,int price){
    TreeNode *y;y=NULL;
        TreeNode *x;x=root;
        TreeNode *n;n=new TreeNode(JourneyCode,price);
        while(x!=NULL){
         y=x;
         if(price<x->price){x=x->left;}
         else{x=x->right;}
        }
         n->parent=y;
         if(y==NULL){root=n;return 1;}
         else if(price<y->price){
            y->left=n;return 1;}
            else{y->right=n;return 1;}
}