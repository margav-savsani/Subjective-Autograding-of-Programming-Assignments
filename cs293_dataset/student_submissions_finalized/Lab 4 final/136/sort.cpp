#include "sort.h"
#include <iostream>

//defining constructor
SorterTree::SorterTree(int c, int len){
    choice=c;
    this->l=len;
    comparisons=0;
    tree=new BST();
    array=new Journey[l];
    construct_array();
}

//define arrayconstructor
void SorterTree::construct_array(){
    for(int i=0;i<l;i++){
        cout<<">>>";
        int price;
        int code;
        cin>>code;
        cin>>price;
        array[i]=Journey(code,price);
    }
}

//Code up the functions defined in sort.cpp
// int SorterTree :: partition(int start,int finish,Journey pivot){
//     int i=start;
//     int j=finish;
//     while(i<j){
//         while ((array[i]<pivot)||(array[i]==pivot)){
//             comparisons++;
//             i++;
//         }
//         while((pivot<array[j])){
//             comparisons++;
//             j--;
//         }
//         if(i<j){
//             Journey temp;
//             temp=array[i];
//             array[i]=array[j];
//             array[j]=temp;
//         }
//     }

//     return j;
// }

int SorterTree :: partition (int start, int finish, Journey pivot) 
{  
    int i = (start - 1); // Index of smaller element and indicates the right position of pivot found so far
    for (int j=start; j<=finish-1; j++) 
    { 
        comparisons++;
        // If current element is smaller than the pivot 
        if (array[j] < pivot) 
        {
            i++; // increment index of smaller element 
            Journey t=array[i];
            t=array[i];
            array[i]=array[j];
            array[j]=t;
        }
    } 
    Journey temp=array[i+1];
    array[i+1]=array[finish];
    array[finish]=temp;
    return (i + 1); 
}

int SorterTree :: getImbalance(){
    if(tree!=nullptr){
        return tree->getImbalance();
    }
}

int SorterTree :: random_partition(int start, int finish,bool tree){
    Journey pivot;
    switch (choice)
    {
        case 1:
            pivot=*choose_one(array,start,finish);
            break;
        case 2:
            pivot=*choose_two(array,start,finish);
            break;
        case 3:
            pivot=*choose_three(array,start,finish);
            break;
    }
    for(int i=0;i<l;i++){
        if(array[i]==pivot){
            Journey temp=array[i];
            array[i]=array[finish];
            array[finish]=temp;
        }
    }
    if(tree){
        insertPivot(pivot.getJourneyCode(),pivot.getPrice());
    }
    return partition(start,finish,pivot);
}

bool SorterTree::Quicksort(int start, int finish)
{   
    if(start<finish){    
    // Call appropriate pivot function based on choice
        //Split into 2 parts based on pivot choice
        // Recursively keep sorting
        int partition_index=random_partition(start,finish,false);
        Quicksort(start,partition_index-1);
        Quicksort(partition_index+1,finish);
        return true;
    }
    return false;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{   
    // Call appropriate ivot function based on choice
    if(start<finish){    
    // Call appropriate pivot function based on choice
        //Split into 2 parts based on pivot choice
        // Recursively keep sorting
        int partition_index=random_partition(start,finish,true);
        QuicksortWithBSTInsert(start,partition_index-1);
        QuicksortWithBSTInsert(partition_index+1,finish);
        return true;
    }
    return false;
}

bool SorterTree::insertPivot(int JourneyCode,int price){
    if(tree==nullptr){
        tree=new BST[1];
    }
    tree->insert(JourneyCode,price);
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    cout<<"comparisions: "<<comparisons<<endl;
    return true;
}

void SorterTree::printTree(){
    tree->printBST("tree");
}