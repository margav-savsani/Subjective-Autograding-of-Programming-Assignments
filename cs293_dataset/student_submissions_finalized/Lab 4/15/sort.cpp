#include "sort.h"
#include <iostream>
#include "choose.h"
using namespace std;
// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice,int l){
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    comparisons=0;
    int k=l;
    for(int i=0;i<l;i++){
        int JC,P;
        cin>>JC>>P;
        array[i]=Journey(JC,P);
    }
}
int SorterTree::Partition(int start,int finish,int pivot_index){
    Journey temp=array[pivot_index];
    array[pivot_index]=array[finish];
    array[finish]=temp;
    int i=start;
    int j=finish;
    while(true){
        while(!(array[j]<temp)){
            cout<<j<<endl;
            j--;
        }
        while(array[i]<temp){
            cout<<i<<endl;
            i++;
        }
        if(i<j){
            Journey temp2=array[i];
            array[i]=array[j];
            array[j]=temp2;
        }
        else{
            return j;
        }
    }
}
bool SorterTree::Quicksort(int start, int finish)
{   
    assert(start<=finish);
    if(start+1==finish||start==finish){
        return true;
    }
    Journey* PIVOT;
    if(choice==1){
        PIVOT=choose_one(array,start,finish);
    }
    else if(choice==2){
        PIVOT=choose_two(array,start,finish);
    }
    else if(choice==3){
        PIVOT=choose_three(array,start,finish);
    }
    else if(choice==4){
        PIVOT=choose_four(array,start,finish);
    }
    int pivot_index=PIVOT-array;
    int j=Partition(start,finish,pivot_index);
    Quicksort(start,j);
    Quicksort(j+1,finish);
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
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

