#include "sort.h"
#include "choose.cpp"
#include <iostream>

SorterTree::SorterTree(int choice, int l){
    this->choice=choice;this->l=l;
}

int SorterTree::Partition(int start,int finish){
    int c=choice;Journey* x;
    if (c==1){
        x = choose_one(array,start,finish);
    }
    if (c==2){
        x = choose_two(array,start,finish);
    }
    if (c==3){
        x = choose_three(array,start,finish);
    }
    int i=start-1,j=finish+1;
    while(true){
        while(array[j].getJourneyCode()<=x->getJourneyCode()){
            j=j-1;
        }
        while(array[i].getJourneyCode()>=x->getJourneyCode()){
            i=i+1;
        }
        if(i<j) swap (array[i],array[j]);
        else return j;
    }
}

// Code up the functions defined in sort.cpp

void SorterTree::Quicksort(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    int i=start,j=finish;
    if(i<j){
        int q=Partition(i,j);
        return Quicksort(i,q);
        return Quicksort(q+1,j);
    }
}

BST *b = new BST();
void SorterTree::QuicksortWithBSTInsert(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
  int c= choice;  Journey* x;
  while(l>0){
    if (c==1){
        x = choose_one(array,start,finish);
    }
    if (c==2){
        x = choose_two(array,start,finish);
    }
    if (c==3){
        x = choose_three(array,start,finish);
    }
    b->insert(x->getJourneyCode(),x->getPrice());
    for(int i=0;i<l;i++){
        if(array[i].getJourneyCode()==x->getJourneyCode()){
            for(int j=i;j<l-1;j++){
                array[j]=array[j+1];
            }
            l=l-1;break;
        }
    }
  }
  return;
}

void SorterTree::printArray(){
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return;
}

