#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
using namespace std;

SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    comparisons=0;
    counter=0;
    array=new Journey[l];
    tree=new BST();
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start<finish){
        int pi;
        Journey* pivot;
        if(choice==1){pivot = choose_one(array,start,finish);}
        else if (choice==2){pivot=choose_two(array,start,finish);}
        else if (choice==3){pivot=choose_three(array,start,finish);}
        if(pivot-array<0||pivot-array>=l){
            pivot=array+finish;
            cout<<"Pivot out of range"<<endl;
        }
        int i=start-1;
        int pvtindx;
        Journey pvt=*pivot;
        for(int j=start;j<=finish;j++){
            comparisons+=1;
            if(array[j]<pvt){
                i++;
                Journey temp=array[j];
                array[j]=array[i];
                array[i]=temp;
            }
        }
        for(int j=start;j<=finish;j++){
            if(array[j]==pvt){pvtindx=j;break;}
        }
        // cout<<"Here\n";
        Journey temp=array[i+1];
        array[i+1]=array[pvtindx];
        array[pvtindx]=temp;
        pi=i+1;
        // // print array:
        // cout<<"Array: ";
        // for(int k=start;k<=finish;k++){
        //     cout<<array[k].getJourneyCode()<<" ";
        // }
        // cout<<"EOA. Value of pvt is: "<<pvt.getJourneyCode()<<endl;
        Quicksort(start,pi-1);
        Quicksort(pi+1,finish);
    }

    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
        // cout<<"Here"<<endl;
    if(start>finish) {return true;}
    Journey* pivot;
    if(choice==1){pivot = choose_one(array,start,finish);}
    else if (choice==2){pivot=choose_two(array,start,finish);}
    else if (choice==3){pivot=choose_three(array,start,finish);}
    if(pivot-array<0||pivot-array>=l){
            pivot=array+finish;
            cout<<"Pivot out of range"<<endl;
    }
    // Journey* input;
    // input= new Journey(pivot->getJourneyCode(),pivot->getPrice());
    // cout<<"start: "<<start<<" finish: "<<finish<<endl;
    // cout<<"Idhar"<<endl;
    tree->insert(pivot->getJourneyCode(),pivot->getPrice());
    if (start<finish){
        int pi;
        // Journey* pivot;
        // if(choice==1){pivot = choose_one(array,start,finish);}
        // else if (choice==2){pivot=choose_two(array,start,finish);}
        // else if (choice==3){pivot=choose_three(array,start,finish);}
        // // Journey* input;
        // // input= new Journey(pivot->getJourneyCode(),pivot->getPrice());
        // tree->insert(pivot->getJourneyCode(),pivot->getPrice());
        int i=start-1;
        int pvtindx;
        Journey pvt=*pivot;
        for(int j=start;j<=finish;j++){
            comparisons+=1;
            if(array[j]<pvt){
                i++;
                Journey temp=array[j];
                array[j]=array[i];
                array[i]=temp;
            }
        }
        for(int j=start;j<=finish;j++){
            if(array[j]==pvt){pvtindx=j;break;}
        }
        // cout<<"Here\n";
        Journey temp=array[i+1];
        array[i+1]=array[pvtindx];
        array[pvtindx]=temp;
        pi=i+1;
        // // print array:
        // cout<<"Array: ";
        // for(int k=start;k<=finish;k++){
        //     cout<<array[k].getJourneyCode()<<" ";
        // }
        // cout<<"EOA. Value of pvt is: "<<pvt.getJourneyCode()<<endl;
        QuicksortWithBSTInsert(start,pi-1);
        QuicksortWithBSTInsert(pi+1,finish);
    }

    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    // cout<<"Cost of comparisions is: "<<comparisons<<endl;
}

void SorterTree::insertElement(Journey j){
    // cout<<"Counter: "<<counter<<endl;
    // cout<<"After Counter"<<endl;
    array[counter]=j;
    // cout<<"Here2"<<endl;
    counter+=1;
}

BST* SorterTree::getTree(){
    return tree;
}

int SorterTree::getComparisions(){
    return comparisons;
}