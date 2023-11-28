
#include <iostream>
#include "updated_sort.h"
// Code up the functions defined in sort.cpp


SorterTree::SorterTree(int choice,int l){
    this->choice = choice;
    this->l = l;
    array=new Journey[1];
    tree=new BST;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    

    Journey pivot;
    if(choice==1){
        pivot=*choose_one(array,start,finish);
    }
    else if(choice==2){
        pivot=*choose_two(array,start,finish);
    }
    else if(choice==3){
        pivot=*choose_three(array,start,finish);
    }
    if(abs(start-finish)==0 || abs(start-finish)==1){
        return;
    }
    int i=start;
    int j=finish-1;
    while(i<finish){
            if(i>j){
                break;
            }
            if(array[i]>=pivot && array[j]<pivot || array[i]>pivot && array[j]<=pivot ){
                int temp;
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
                i++;j--;
            }
            else if(array[i]<=pivot){
                i++;
            }
            else if(array[j]>=pivot){
                j--;
            }
    }
    return true;
}

bool SorterTree::insertPivot(int JourneyCode,int price){
    return tree->insert(JourneyCode,price);
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    Journey pivot;
    if(choice==1){
        pivot=*choose_one(array,start,finish);
    }
    else if(choice==2){
        pivot=*choose_two(array,start,finish);
    }
    else if(choice==3){
        pivot=*choose_three(array,start,finish);
    }
    if(abs(start-finish)==0 || abs(start-finish)==1){
        return;
    }
    int i=start;
    int j=finish-1;
    while(i<finish){
            if(i>j){
                break;
            }
            if(array[i]>=pivot && array[j]<pivot || array[i]>pivot && array[j]<=pivot ){
                int temp;
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
                i++;j--;
            }
            else if(array[i]<=pivot){
                i++;
            }
            else if(array[j]>=pivot){
                j--;
            }
    }
    QuicksortWithBSTInsert(start,j);
    QuicksortWithBSTInsert(i,finish);
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

BST* SorterTree::getTree(){
    return tree;
}

SorterTree::~SorterTree(){
    cout<<"Total Imbalance = "<<getTree()->getImbalance() << "\n";
}