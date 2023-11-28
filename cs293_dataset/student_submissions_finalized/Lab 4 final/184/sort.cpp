#include "sort.h"
#include <iostream>

//constructers
SorterTree::SorterTree(int a, int b){
    choice=a;
    l=b;
    array=new Journey[l];
    ind=0;
    comparisons=1;
}
// Code up the functions defined in sort.cpp
void SorterTree::insert(int jrny_code, int cost){
    assert(ind<l);//so that insertion does not takes place after l. 
    array[ind]=Journey(jrny_code,cost);
    ind++;
}
int SorterTree::partition(int start, int finish){
    Journey *x1;
    if(choice==1) x1=choose_one(array,start,finish);
    else if(choice==2)  x1=choose_two(array,start,finish);
    else if(choice==3)  x1=choose_three(array,start,finish);
    //if(x==nullptr) return -1;
    //cout<<x->getJourneyCode();
    
    Journey exchange=array[finish];
    array[finish]=*x1;
    *x1=exchange;
    // cout<<x->getJourneyCode()<<endl;
    // x=&array[finish];
    // cout<<x->getJourneyCode()<<endl;

    Journey x=array[finish];

    int i=start;
    int j=finish;
    while(true){
        while((x<array[j])) {
            j--;
            comparisons++;
        }
        while((array[i]<x)){
            i++;
            comparisons++;
        }
        //cout<<i<<" "<<j<<endl;
        if(i<j){
            Journey a=array[j];
            array[j]=array[i];
            array[i]=a;
        }
        else return j;
    }

}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    int q=partition(start,finish);
    //cout<<start<<finish<<endl;
    //cout<<q<<endl;
    
    if(start>=finish) return true;
    
    if(q<finish && q>start){
        Quicksort(start,q);
        Quicksort(q+1,finish);
        return true;
    }
    // if(start<finish ){
    //     Quicksort(start,q);
    //     Quicksort(q+1,finish);
    //     return true;
    // }
    else if(q==finish){
        Quicksort(start,q-1);
        return true;
    }
    else if(q==start){
        Quicksort(q+1,finish);
        return true;
    }
    else return false;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    return false;
}

void SorterTree::printArray()
{   
    cout<<"Total Number of Comparisions:"<<comparisons<<endl;
    for (int i = 0; i <ind; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

SorterTree::~SorterTree(){

}


