#include "sort.h"
#include <iostream>

void SorterTree::addJourney(int index, int JourneyCode, int Price){
    array[index].change_JourneyCode(JourneyCode);
    array[index].change_price(Price);
}
SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    tree=new BST();
}

void SorterTree::swap(Journey* a,Journey* b){
    unsigned int c=a->getJourneyCode();
    unsigned int d=a->getPrice();
    a->change_JourneyCode(b->getJourneyCode());
    a->change_price(b->getPrice());
    b->change_JourneyCode(c);
    b->change_price(d);
}

// Code up the functions defined in sort.cpp
int SorterTree::partition(Journey* arr,int start,int finish,int pivot_choice){
    swap(&arr[pivot_choice],&arr[finish]);
    Journey pivot = arr[finish];  
    int i=start-1;  
    for(int j=start; j<=finish; j++){
         if(arr[j].getJourneyCode() < pivot.getJourneyCode()){
            i++;   
            comparisons++;
            swap(&arr[i],&arr[j]);
         }
    }
    swap(&arr[i+1],&arr[finish]);
    return i+1;
}

void SorterTree::Quicksort(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start>finish) return;
    int i=0;
    Journey* x=new Journey();
    int found=0;
    if(choice==1){x=choose_one(array,start,finish);}
    else if(choice==2){x=choose_two(array,start,finish);}
    else if(choice==3){x=choose_three(array,start,finish);}
    int code=x->getJourneyCode();
    if (start<=finish){
        int index;
        for(int i=start;i<=finish;i++){
            if(array[i].getJourneyCode()==code){
                 index=i;
                 found=1;
                 tree->insert(array[i].getJourneyCode(),array[i].getPrice());
            }
        }
        if(found==1){
            int p=partition(array, start, finish, index);
            Quicksort(start, p-1);  // Before p
            Quicksort(p+1,finish); // After p
        }
    }
    if(found==0 && start<=finish) cout<<"pivot selected is outside the array";
    return;

}

void SorterTree::calling_QuickSort(){
    Quicksort(0,l-1);
    cout<<"number of Comparisons :"<<comparisons<<endl;
}

BST* SorterTree::getTree(){
     return tree;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    bool a=tree->insert(JourneyCode,price);
    return a;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
    tree->printBST("",false);
    return true;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray(){
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return 1;
}
