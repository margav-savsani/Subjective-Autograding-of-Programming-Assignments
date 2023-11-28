#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
using namespace std;
SorterTree::SorterTree(int choice,int l,Journey arr[])
{
    this->choice=choice;
    this->l=l;
    array = arr;
    comparisons=0;
    tree= new BST();
}
bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    cout<<"start :"<<start<<" end:"<<finish<<endl;
    Journey* pi;
    if(start>=finish-1) return true;
    if(choice==1)
    pi= choose_one(array,start,finish-1);
    if(choice==2)
    pi= choose_two(array,start,finish-1);
    if(choice==3)
    pi= choose_three(array,start,finish-1);
    int c,k,s;
    cout<<"key:"<<pi->getJourneyCode()<<endl;
    c=k=s=0;
    for(int i=0;i<l;i++)
    {
        if( &array[i] == pi)
        {
            s=i;
            break;
            
        }
    }

    Journey temp=array[finish-1];
    array[finish-1]=array[s];
    array[s]=temp;
    temp = array[finish-1];
    
    while(true){
        for(c = start ; c < finish ; c++ ){
            if(array[c] > temp)break;
        }
        for(k = finish-1;k >= start;k--){
            if(temp > array[k])break;
        }
        //cout<<"k , c"<<k <<" "<<c<<endl;
        //cout<< array[k].getJourneyCode()<<" "<<array[c].getJourneyCode()<<endl;
        if(c == finish  || k == start-1 || k <= c)break;
        Journey temp1 = array[c];
        array[c] = array[k];
        array[k] = temp1;
    }
    if(c != finish){
    temp = array[c];
    array[c] = array[finish-1];
    array[finish-1] = temp;
    Quicksort(start,c);
    Quicksort(c+1,finish);
    }
    else{
        Quicksort(start, finish-1);
    }
    
    return true;


}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
       // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey* pi;
    if(start>=finish-1) return true;
    if(choice==1)
    pi= choose_one(array,start,finish-1);
    if(choice==2)
    pi= choose_two(array,start,finish-1);
    if(choice==3)
    pi= choose_three(array,start,finish-1);
    int c,k,s;
    c=k=s=0;
    for(int i=0;i<l;i++)
    {
        if( &array[i] == pi)
        {
            s=i;
            break;
            
        }
    }
    cout<<tree->insert(pi->getJourneyCode() , pi->getPrice())<<endl;
    Journey temp=array[finish-1];
    array[finish-1]=array[s];
    array[s]=temp;
    temp = array[finish-1];
    
    while(true){
        for(c = start ; c < finish ; c++ ){
            if(array[c] > temp)break;
        }
        for(k = finish-1;k >= start;k--){
            if(temp > array[k])break;
        }
        //cout<<"k , c"<<k <<" "<<c<<endl;
        //cout<< array[k].getJourneyCode()<<" "<<array[c].getJourneyCode()<<endl;
        if(c == finish  || k == start-1 || k <= c)break;
        Journey temp1 = array[c];
        array[c] = array[k];
        array[k] = temp1;
    }
    if(c != finish){
    temp = array[c];
    array[c] = array[finish-1];
    array[finish-1] = temp;
    QuicksortWithBSTInsert(start,c);
    QuicksortWithBSTInsert(c+1,finish);
    }
    else{
        QuicksortWithBSTInsert(start, finish-1);
    }
    
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
SorterTree::~SorterTree(){}
int SorterTree::print_Imbalance(){ return tree->getImbalance();}

bool SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode,price);    
}
