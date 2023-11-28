#include "sort.h"
#include "choose.cpp"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice,int l){
    comparisons=0;  
    this->choice=choice;
    this->l=l;
    unsigned int jcode,price;
    array=new Journey[l];
    for(int i=0;i<l;i++){
        cin>>jcode>>price;
        array[i]=Journey(jcode,price);
    }
    tree=new BST(nullptr);
}

bool SorterTree::Quicksort(int start, int finish)
{
    Journey* pivot;
    //getting pivot according to choice.
    switch(choice){
        case 1: pivot=choose_one(array,start,finish);break;
        case 2: pivot=choose_two(array,start,finish);break;
        case 3: pivot=choose_three(array,start,finish);break;
        case 4: pivot=choose_four(array,start,finish);break;
    }
    if(!(start==finish)){ 
        //partitioning the array
        int mid=getMidIndex(pivot,start,finish);
        if(mid>=start){
            QuicksortWithBSTInsert(start,mid);
        }
        if(mid+1<=finish){
           QuicksortWithBSTInsert(mid+1,finish);
        }
    }
    return true;
}

int SorterTree::getMidIndex(Journey* pivot,int start,int finish){
    //finding index of the pivot and putting it at the end
    for(int i=start;i<=finish;i++){
        if(!(array[i]<*pivot) && !(*pivot<array[i])){
            comparisons+=2;
            unsigned int jcode=array[finish].getJourneyCode();
            unsigned int price=array[finish].getPrice();
            array[finish]=array[i];
            array[i]=Journey(jcode,price);
            break;
        }    
    }
    //sorting the array according to whether an element is less than or greater than
    //or equal to the pivot.
    int i=start-1;
    int j=finish+1;
    while (true){
        do{
            comparisons++;
            j=j-1;
            if(j<start){
                break;
            }
        }
        while(*pivot<array[j]);

        do{
            comparisons++;
            i++;
            if(i>finish){
                break;
            }
        }
        while(array[i]<*pivot);

        if(i<j){
            unsigned int jcode=array[j].getJourneyCode();
            unsigned int price=array[j].getPrice();
            array[j]=array[i];
            array[i]=Journey(jcode,price);
        }
        else if(i==j){
            return j-1;
        }
        else{
            return j;
        }
    }
}

bool SorterTree::insertPivot(int j, int p){
    //inserts to the tree by calling the previously defined insert function
    tree->insert(j,p);
    return true;
}
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    Journey* pivot;
    switch(choice){
        case 1: pivot=&array[start];break;//choose_one(array,start,finish);break;
        case 2: pivot=&array[finish];break;//choose_two(array,start,finish);break;
        case 3: pivot=&array[int((start+finish)/2)];break;//choose_three(array,start,finish);break;
        case 4: pivot=new Journey(1,1);break;//choose_four(array,start,finish);break;
    }

    //if(!(tree->find(pivot->getJourneyCode(),pivot->getPrice()))){
    insertPivot(pivot->getJourneyCode(),pivot->getPrice());
    
    if(!(start==finish)){ 
        int mid=getMidIndex(pivot,start,finish);
        if(mid>=start){
            QuicksortWithBSTInsert(start,mid);
        }
        if(mid+1<=finish){
           QuicksortWithBSTInsert(mid+1,finish);
        }
    }

    return true;
}

BST* SorterTree::getTree(){
    return tree;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<endl;
    }
}

void SorterTree::getShortLong(){
    tree->prestore();
}

int SorterTree::getComparisons(){
    return comparisons;
}