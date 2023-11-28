#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int c,int n){
    choice=c;
    l=n;
    array=new Journey[l];
    tree=new BST;
    comparisons=0;
    count=0;
    once=true;
}

SorterTree::SorterTree(Journey* j,int c,int n){
    choice=c;
    l=n;
    array=j;
    tree=new BST;
    comparisons=0;
    count=0;
    once=true;
}

void swap(Journey* x,Journey* y){
    Journey temp=*x;
    *x=*y;
    *y=temp;
}

int SorterTree::partition(int start,int finish){
    Journey p=array[finish];
    int i=start-1;
    for(int j=start;j<finish;j++){
        comparisons++;
        if(array[j]<p){
            i++;
            swap(&array[i],&array[j]);
        }
    }
    swap(&array[i+1],&array[finish]);
    return i+1;
}

bool SorterTree::Quicksort(int start, int finish)
{
    
    if(start<=finish){
        Journey *j;
        if(choice==1)j=choose_one(array,start,finish);
        if(choice==2)j=choose_two(array,start,finish);
        if(choice==3)j=choose_three(array,start,finish);
        swap(j,&array[finish]);
        count++;
        int part=partition(start,finish);
        Quicksort(start,part-1);
        Quicksort(part+1,finish);
    }
    if(count==l && once){
        cout<<"Total comparisons performed: "<<comparisons<<endl;
        once=false;
    }
    return true;

}

bool SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode,price);
    
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(start<=finish){
        Journey *j;
        if(choice==1)j=choose_one(array,start,finish);
        if(choice==2)j=choose_two(array,start,finish);
        if(choice==3)j=choose_three(array,start,finish);
        insertPivot(j->getJourneyCode(),j->getPrice());
        count++;
        swap(j,&array[finish]);
        int part=partition(start,finish);
        QuicksortWithBSTInsert(start,part-1);
        QuicksortWithBSTInsert(part+1,finish);
    }
    if(count==l && once){
        cout<<"Total comparisons performed: "<<comparisons<<endl;
        once=false;
    }
    return true;

}

BST* SorterTree::getTree(){
    return tree;
}
void SorterTree::printTree(){
    tree->printBST("");
}
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
