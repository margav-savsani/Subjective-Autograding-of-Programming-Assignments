#include "sort.h"
#include <iostream>
#include "choose.h"
// Code up the functions defined in sort.cpp
int SorterTree::partition(int start,int finish,Journey*jour){
    
    int i=start-1;
    int j=finish+1;
    swap(*jour,array[start]);
    while (true)
    {
        do{j=j-1;comparisons++;}
        while (array[j].JourneyCode>jour->JourneyCode);
        do{i=i+1;comparisons++;}
        while ((array[i].JourneyCode)<(jour->JourneyCode));
        if(i<j)
        {
            swap(array[i],array[j]);
        }
        else return j;
    }
}

SorterTree::SorterTree(int a,int b){
    array=new Journey[a];
    tree=new BST;
    choice=b;
    l=0;
    comparisons=0;
}
void SorterTree::add(unsigned int JourneyCode,unsigned int price){
    array[l].JourneyCode=JourneyCode;
    array[l].price=price;
    l++;
    return;
}
bool SorterTree::Quicksort(int start, int finish)
{
    Journey* jour ;
    if(choice==1) jour = choose_one(array,start,finish);
    if(choice==2) jour= choose_two(array,start,finish);
    if(choice==3) jour= choose_three(array,start,finish);
    if (start < finish){
    int q = partition(start,finish,jour);
    Quicksort(start,q);            
    Quicksort(q+1,finish);
    return true;
    }
    return false;
}
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{  
     Journey* jour =new Journey();
    if(choice==1) jour = choose_one(array,start,finish);
    if(choice==2) jour= choose_two(array,start,finish);
    if(choice==3) jour= choose_three(array,start,finish);
    tree->insert(jour->JourneyCode,jour->price);
    if (start < finish){
    int q = partition(start,finish,jour);
    QuicksortWithBSTInsert(start,q);                                 
    QuicksortWithBSTInsert(q+1,finish);
    return true;
    }
    return false;
}

bool SorterTree::printArray()
{   cout<<"comparisions: "<<comparisons/2<<endl; //as I am performing both the quicksort and quicksort with bst i am dividing the no of comparisions with two to find 
                                                 //the no of comparisions taken for one sorting.               
    for (int i = 0; i <l; i++)
    {
        std::cout<<"Journey code: "<<array[i].JourneyCode <<"\tJourney Price:"<<array[i].price<<std::endl;
    }
    return true;
  
}
BST* SorterTree::getTree()
{
    return tree;
}