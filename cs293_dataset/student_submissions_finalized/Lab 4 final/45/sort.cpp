#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice,int l){
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    comparisons=0;
    tree = new BST();
}
Journey* SorterTree::choose_pivot(int choice, int start, int finish, Journey* array){
    Journey* pivot;
    if(choice==1){pivot=choose_one(array,start,finish);}
    if(choice==2){pivot=choose_two(array,start,finish);}
    if(choice==3){pivot=choose_three(array,start,finish);}
    return pivot;
}



int SorterTree::partition(int choice,int start,int finish,Journey* array){
    Journey* pivot;
    pivot=choose_pivot(choice, start, finish, array);
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    int i=start-1;
    if(start==finish){
        return start;
    }

    else if(start<finish){
        for(int j=start;j<=finish;j++){
            if(array[j] < *pivot){
                comparisons++;
                i++;
                //swap(array[i],array[j]);
                Journey tmp=array[i];
                array[i]=array[j];
                array[j]=tmp;
            }  
        }
        //swap(array[i+1],pivot);
        Journey tmp2=array[i+1];
        array[i+1]=*pivot;
        *pivot=tmp2;
        return i+1;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    if(start>finish){return false;}
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    int prtn=partition(choice,start,finish,array);
         
    Quicksort(start,prtn-1);
   
    Quicksort(prtn+1,finish);
    
    //else{
        
    //}
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    
    if(start>finish){return false;}
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    int prtn=partition(choice,start,finish,array);
    
    int code= array[prtn].getJourneyCode();
    int price= array[prtn].getPrice();
    
    
    if(insertPivot(code,price)){
        
        //(root->left);
        QuicksortWithBSTInsert(start,prtn-1);
        
        //(root->right)
        QuicksortWithBSTInsert(prtn+1,finish);
    }
    //else{
        
    //}
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<" Journey Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

Journey* SorterTree::getArray()
{
    return array;
}

bool SorterTree::insertPivot(int JourneyCode, int price){   
    return tree->insert(JourneyCode,price); 
}

BST* SorterTree::getTree(){
    return tree;
}