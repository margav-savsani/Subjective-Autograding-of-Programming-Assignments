#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int s,int length){
    choice=s;
    l=length;
    array=new Journey[l];
    tree=new BST;
    i=0;
    comparisons=0;
}

bool SorterTree::Insertjour(int JourneyCode,int price){
    
    if(i>=l){return false;}
    Journey j(JourneyCode,price);
    array[i]=j;
    i++;
    return true;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey *p;
    if(start>=finish){
        return false;
    }
    if(choice==1){
        p=choose_one(array, start,finish);
    }
    else if(choice==2){
        p=choose_two(array, start,finish);
    }
     else if(choice==3){
        p=choose_three(array, start,finish);
    }
    int x=0;
    while(array[x].getJourneyCode()!=p->getJourneyCode()){
        x++;
    }
    int q=partition(array,start,finish,x);
    Quicksort(start,q);
    Quicksort(q+1,finish); 
    
}

int SorterTree::partition(Journey B[], int p,int r,int piv){
        Journey x=array[piv];
        int i=p;
        int j=r;
        while(true){
            while(array[j]>x){
                j=j-1;
                comparisons++;
            }
            while(x>array[i]){
                i=i+1;
                comparisons++;
            }
            if(i<j){
                Journey temp;
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
            else if(j==r) {return j-1;}
            else return j;
        }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
     Journey *p;
    if(start>=finish){
        return false;
    }
    if(choice==1){
        p=choose_one(array, start,finish);
    }
    else if(choice==2){
        p=choose_two(array, start,finish);
    }
     else if(choice==3){
        p=choose_three(array, start,finish);
    }
    int x=0;
    while(array[x].getJourneyCode()!=p->getJourneyCode()){
        x++;
    }
    insertPivot(p->getJourneyCode(),p->getPrice());
    int q=partition(array,start,finish,x);
    QuicksortWithBSTInsert(start,q);
    QuicksortWithBSTInsert(q+1,finish); 
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
     tree->insert(JourneyCode,price);

}