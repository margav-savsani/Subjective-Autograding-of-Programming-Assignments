#include "sort.h"
#include "choose.h"
#include <iostream>
// Code up the functions defined in sort.cpp

bool SorterTree::printComparisons(){
    cout<<comparisons<<std::endl;
    return true;
}

bool SorterTree::printImbalance(){
    cout<<tree->getImbalance()<<std::endl;
    return true;
}

void SorterTree::setArray(){
    for (int i = 0; i < l; i++)
    {
        array[i].setJourneyCode();
        array[i].setPrice();
    }
}

SorterTree::SorterTree(int choicenew, int lnew){
    choice = choicenew;
    l = lnew;
    tree = new BST;
    array = new Journey[l];
    comparisons = 0;
}

bool SorterTree::Quicksort(int start, int finish)
{
    if(start==finish) {
        tree->insert(array[start].getJourneyCode(),array[start].getPrice());
        return true;
    }
    
    Journey *chosen; // $ Here we store the chosen value
    Journey *returned;
    if(choice==1){
        returned = choose_one(array, start,finish);
        chosen = new Journey;
        *chosen = *returned;
    }
    else if(choice==2){
        returned = choose_two(array, start,finish);
        chosen = new Journey;
        *chosen = *returned;
    }
    else if(choice==3){
        returned = choose_three(array, start, finish);
        chosen = new Journey;
        *chosen = *returned;
    }
    else if(choice==4){
        returned = choose_four(array, start,finish);
        chosen = new Journey;
        *chosen = *returned;
    }
    int i,j; //$ The variables used for quicksort
    Journey temp; 

    //$ We take a case where chosen is the maximum element
    Journey arrmax;
    arrmax=array[start];
    int t=start;
    while(t<=finish){
        if(arrmax<array[t]) arrmax = array[t];
        t++;
    }
    if(arrmax == *chosen ){
        while(true){
            i=start;
            j=finish;
            while(array[i]<*chosen ) {
                comparisons++;
                i++;
            }
            while(*chosen<array[j] || *chosen==array[j]) {
                comparisons++;
                j--;
            }
            //$ if i < j then we swap otherwise we break
            if(i<j){
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
            else break;
        }
    }
    else {
        while(true){
            i=start;
            j=finish;
            while(array[i]<*chosen || *chosen == array[i]) {
                i++;
                comparisons++;
            }
            while(*chosen<array[j]) {j--;comparisons++;}
            //$ if i < j then we swap otherwise we break
            if(i<j){
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
            else break;
        }
    }
    QuicksortWithBSTInsert(start,j);
    QuicksortWithBSTInsert(i,finish);

    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(start==finish) {
        tree->insert(array[start].getJourneyCode(),array[start].getPrice());
        return true;
    }
    
    Journey *chosen; // $ Here we store the chosen value
    Journey *returned;
    if(choice==1){
        returned = choose_one(array, start,finish);
        chosen = new Journey;
        *chosen = *returned;
    }
    else if(choice==2){
        returned = choose_two(array, start,finish);
        chosen = new Journey;
        *chosen = *returned;
    }
    else if(choice==3){
        returned = choose_three(array, start, finish);
        chosen = new Journey;
        *chosen = *returned;
    }
    else if(choice==4){
        returned = choose_four(array, start,finish);
        chosen = new Journey;
        *chosen = *returned;
    }
    int i,j; //$ The variables used for quicksort
    Journey temp; 

    //$ We take a case where chosen is the maximum element
    Journey arrmax,arrmin;
    arrmax=array[start];
    arrmin=array[start];
    int t=start;
    while(t<=finish){
        if(arrmax<array[t]) arrmax = array[t];
        t++;
    }
    t=start;
    while(t<=finish){
        if(array[t]<arrmin) arrmin = array[t];
        t++;
    }

    if(*chosen<arrmin || arrmax<*chosen){
        cout<<"Chosen not in bounds"<<endl;
        cout<<"Chosen: "<<chosen->getJourneyCode()<<" Max: "<<arrmax.getJourneyCode()<<" Min: "<<arrmin.getJourneyCode();

    }
    
    if(arrmax == *chosen ){
        while(true){
            i=start;
            j=finish;
            while(array[i]<*chosen ) {
                i++;
                comparisons++;
            }
            while(*chosen<array[j] || *chosen==array[j]) {
                j--;
                comparisons++;
            }
            //$ if i < j then we swap otherwise we break
            if(i<j){
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
            else break;
        }
    }
    else {
        while(true){
            i=start;
            j=finish;
            while(array[i]<*chosen || *chosen == array[i]) {
                i++;
                comparisons++;
            }
            while(*chosen<array[j]) {j--;comparisons++;}
            //$ if i < j then we swap otherwise we break
            if(i<j){
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
            else break;
        }
    }
    int u,v; 
    u = chosen->getJourneyCode();
    v = chosen->getPrice();
    tree->insert(u,v);
    QuicksortWithBSTInsert(start,j);
    QuicksortWithBSTInsert(i,finish);

    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<" Journey Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

bool SorterTree::printTree()
{
    tree->printBST("");
    return true;
}