#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l,Journey* array){
    this->choice = choice; 
    this->l = l;
    this->array = array;    
    comparisons=0;
    tree = new BST;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    return(tree->insert(JourneyCode,price));    
}

int SorterTree::partition(int p,int q, bool insert){
    int i=p-1;
    int j=q+1;
    Journey* J;
    if(choice == 1) J = choose_one(array, p, q);
    else if(choice == 2) J = choose_two(array, p, q);
    else J = choose_three(array, p, q);    

    if(insert) {        
        insertPivot(J->getJourneyCode(),J->getPrice()); 
    }
    while(J != NULL){                
        while(true){
            j=j-1;
            if(array[j] < *J || *J == array[j]) {
                comparisons++;
                break;
            }
        }           

        while(true){
            i=i+1;
            if(*J < array[i] || *J == array[i]) {
                comparisons++;    
                break;
            }
        }

        if(i < j){  
            if(i != j){
                Journey temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }                      
        }
        else if(j == q) return j-1;
        else return j;
    }  
    return -1;  
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start<finish){
        int q = partition(start,finish,false);
        if(q == -1) return false;
        if(!Quicksort(start,q) || !Quicksort(q+1,finish)) return false;
    }    
    return true; 
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately  
    if(start<finish){
        int q = partition(start,finish,true);
        if(q == -1) return false;
        if(!QuicksortWithBSTInsert(start,q) || !QuicksortWithBSTInsert(q+1,finish))  return false;
    }
    return true;
}

BST* SorterTree::getTree(){ return tree;}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    cout<<endl;
    cout<<"comparisions: "<<comparisons<<endl;
    cout<<endl;
    return true;
}
