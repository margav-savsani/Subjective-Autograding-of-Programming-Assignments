#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
using namespace std;



bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(finish<=start)return true;
    if(finish>start){
        Journey*pivot; 
        if(choice==1) pivot=choose_one(array,start,finish);
        if(choice==2) pivot=choose_two(array,start,finish);
        if(choice==3) pivot=choose_three(array,start,finish);
        Journey temp=*pivot;
        bool inarr=false;
        for(int i=start;i<=finish;i++){
            if(pivot->getJourneyCode()==(array+i)->getJourneyCode() && pivot->getPrice()==(array+i)->getPrice())inarr=true;
        }
        if(!inarr){
            cout<<"Pivot Function is not valid"<<endl;
            return false;
        }
        int i=start,j=finish;
        while(true){
            while(array[i]<temp){
            i++;
            }
            while(temp<array[j]){
                j--;
            }
            if(j>i){
                Journey temp2;
                temp2=array[j];
                array[j]=array[i];
                array[i]=temp2;
            }
            else{
                if(j==finish)j--;
                break;
            }
        }
        return Quicksort(start,j) && Quicksort(j+1,finish);
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(finish<start)return true;
    if(finish==start){
        tree->insert(array[start].getJourneyCode(),array[start].getPrice());
        return true;
    }
    if(finish>start){
        Journey*pivot; 
        if(choice==1) pivot=choose_one(array,start,finish);
        if(choice==2) pivot=choose_two(array,start,finish);
        if(choice==3) pivot=choose_three(array,start,finish);
        Journey temp=*pivot;
        bool inarr=false;
        for(int i=start;i<=finish;i++){
            if(pivot->getJourneyCode()==(array+i)->getJourneyCode() && pivot->getPrice()==(array+i)->getPrice())inarr=true;
        }
        if(!inarr){
            cout<<"Pivot Function is not valid"<<endl;
            return false;
        }
        tree->insert(temp.getJourneyCode(),temp.getPrice());
        int i=start,j=finish;
        while(true){
            while(array[i]<temp){
            i++;
            }
            while(temp<array[j]){
                j--;
            }
            if(j>i){
                Journey temp2;
                temp2=array[j];
                array[j]=array[i];
                array[i]=temp2;
            }
            
            else{
                if(j==finish)j--;
                break;
            }
        }
        return QuicksortWithBSTInsert(start,j) && QuicksortWithBSTInsert(j+1,finish);
    }
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

BST* SorterTree::getTree(){
    return tree;
}

SorterTree::SorterTree(int choice,int l){
    this->choice = choice;
    this->l=l;
    array= new Journey[l];
    tree= new BST;
    for(int i=0;i<l;i++){
        cin>>(array[i]);
    }
}
