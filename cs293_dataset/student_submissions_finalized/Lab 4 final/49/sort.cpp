#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l)// constructor
{
    this->choice=choice;
    this->l=l;
    array = new Journey[l];
    comparisons = 0;
    tree = new BST(new TreeNode);
}
bool SorterTree::insertJourney(int JourneyCode, int price)// to take inputs in main and insert into array
{
    for(int i=0;i<l;i++){
        if(array[i].getJourneyCode()==-1){
            array[i].resetvoidJourney(JourneyCode,price);// function declared in journey.h to reset if journeycode is -1  
            cout<<"Insertion successfull"<<endl;         
            return true; 
        }    
    }
    return false; 
}
int SorterTree::partition(Journey*array,int start,int finish,Journey pivot)// partition used in quicksort
{
    int i = start;
    int j = finish;
    while(true){
        while(array[j]>pivot){
            j=j-1;          
            comparisons++;
        }    
        while(array[i]<pivot){
            i=i+1;
            comparisons++;
        }    
        if(i<j){
            swap(array[i],array[j]);
        }
        else return j;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey* pivot;
    if(choice==1) pivot = choose_one(array,start,finish);
    else if(choice==2) pivot = choose_two(array,start,finish);
    else if(choice==3) pivot = choose_three(array,start,finish);    

    if(start<finish){
        int q = partition(array,start,finish,*pivot);  
        if(q==finish)return true;      
        Quicksort(start,q);
        Quicksort(q+1,finish);
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
     Journey* pivot;
    if(choice==1) pivot = choose_one(array,start,finish);
    else if(choice==2) pivot = choose_two(array,start,finish);
    else if(choice==3) pivot = choose_three(array,start,finish);  
    insertPivot(pivot->getJourneyCode(),pivot->getPrice());
    if(start<finish){
        int q = partition(array,start,finish,*pivot);  
        if(q==finish)return true;      
        QuicksortWithBSTInsert(start,q);
        QuicksortWithBSTInsert(q+1,finish);
    }
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

void SorterTree::BSTprint()// defined it as tree is private in SorterTree 
{
    tree->printBST("");

}

int SorterTree::comp()
{
    return comparisons;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    if(tree->insert(JourneyCode,price))return true;
    else return false;
}

BST* SorterTree::getTree(){
    return tree;
}

int SorterTree:: BSTimbalance(){
    return tree->getImbalance();
};
