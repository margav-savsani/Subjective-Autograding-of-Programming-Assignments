#include "sort.h"
#include <iostream>
int y;
Journey *x;
// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){this->choice=choice;this->l=l;comparisons=0;tree=new BST();}// Define valid constructor
int SorterTree::getcomparisons(){return comparisons;}
bool SorterTree::insertPivot(int JourneyCode, int price){
   // cout<<"insertpivot"<<endl;
   //cout<<JourneyCode<<" "<<price<<endl;
    tree->insert(JourneyCode,price);
    //cout<<"done"<<endl;
    return true;
}
int SorterTree::imb(){
   // cout<<"insertpivot"<<endl;
    
    //cout<<"done"<<endl;
    return tree->getImbalance();
}

int SorterTree::partition(Journey * array,int start,int finish){
    //choose pivot x
    
    if(choice==1){x=choose_one(array, start, finish);}
    if(choice==2){x=choose_two(array, start, finish);/*cout<<"chooooose:::"<<x->getJourneyCode()<<endl;*/}
    if(choice==3){x=choose_three(array, start, finish);}
    int i=start;
    int j=finish;
    while(true){
        while(array[j].getJourneyCode()>x->getJourneyCode()){
            j=j-1;
            comparisons++;
        }
        while(array[i].getJourneyCode()<x->getJourneyCode()){
            i=i+1;
            comparisons++;
        }
        if(i<j){
            Journey p=array[i];
            array[i]=array[j];
            array[j]=p;
            //int y=array[i].getJourneyCode();
           // array[i].getJourneyCode()=array[j].getJourneyCode();
           // array[j].getJourneyCode()=y;
        }
        else if (j==finish) return j-1;
        else return j;
    }
}

bool SorterTree::Quicksort(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
   // cout<<"entered quicksort"<<endl;
    if(start<finish){
       // cout<<"hf jtkb"<<endl;
        int q=partition(array,start,finish);
        Quicksort(start,q);
        Quicksort(q+1,finish);
    }
   // cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
   // cout<<printArray();
   // cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
    return true;
}


bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
   //cout<<"entered qwb"<<endl;
    Journey *x;
    if(choice==1){x=choose_one(array, start, finish);}
    if(choice==2){x=choose_two(array, start, finish);}
    if(choice==3){x=choose_three(array, start, finish);//cout<<"choice3"<<endl;cout<<x->getJourneyCode();
    //cout<<x->getPrice();
    }
   // cout<<"body"<<endl;
  // cout<<x->getJourneyCode()<<endl;
//   cout<<x->getPrice()<<endl;
   
   // cout<<"pOo"<<endl;
    
    if(start<finish){
       // cout<<"t"<<endl;
         insertPivot(x->getJourneyCode(),x->getPrice());
        // cout<<"crossed insert pivot"<<endl;
        int q=partition(array,start,finish);
        //cout<<"part"<<endl;
        QuicksortWithBSTInsert(start,q);
        QuicksortWithBSTInsert(q+1,finish);
    }
   //cout<<"nkkkkkkk"<<endl;
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"        "<<"Journey Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
void SorterTree::insertt(int co,Journey j){
    array[co]=j;
   // cout<<"after insertt"<<endl;
   // cout<<printArray();cout<<"............................."<<endl;
    return;
}
