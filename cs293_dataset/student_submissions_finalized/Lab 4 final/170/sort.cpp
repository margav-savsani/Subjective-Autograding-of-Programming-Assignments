#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int a=0;
int k=0;

SorterTree::SorterTree(int choice, int l){
	this->l=l;
	this->choice=choice;
	array=new Journey[l];
	tree = new BST();
	comparisons=0;
}

void SorterTree::add(Journey J){
	array[k]=J;
	k++;
}

int SorterTree::Partition(int p, int r){
	Journey* x;
	if(choice==1) x=choose_one(array, p, r);
	else if(choice==2) x=choose_two(array, p, r);
		else x=choose_three(array, p, r);
	if(a==1){
		tree->insert(x->getJourneyCode(), x->getPrice());
	}
	int i=p;
	int j=r;
	while(1){
		while(array[j].getJourneyCode() > x->getJourneyCode()){ j=j-1;comparisons++; }
		while(array[i].getJourneyCode() < x->getJourneyCode()){ i=i+1;comparisons++; }
		if(i<j){
			Journey k=array[i];
			array[i]=array[j];
			array[j]=k;
		}
		else if(j==r) return j-1;
		else return j;
	}
}

bool SorterTree::Quicksort(int start, int finish)
{
	// Call appropriate pivot function based on choice
	// Split into 2 parts based on pivot choice
	// Recursively keep sorting
	if(start<finish){
		int q=Partition(start,finish);
		Quicksort(start,q);
		Quicksort(q+1,finish);
	}
	return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    
	if(start==finish){
		Journey* x;
		if(choice==1) x=choose_one(array, start, finish);
		else if(choice==2) x=choose_two(array, start, finish);
			else x=choose_three(array, start, finish);
		if(a==1){
			tree->insert(x->getJourneyCode(), x->getPrice());
		}	
	}
    if(start<finish){
        a=1;
	int q=Partition(start,finish);
	QuicksortWithBSTInsert(start,q);
	QuicksortWithBSTInsert(q+1,finish);
     }
     a=0;
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

int SorterTree:: difference(){
	return tree->getImbalance();
}

int SorterTree:: comparison(){
	return comparisons;
}

BST* SorterTree::getTree(){
	tree->printBST("");
	return tree;
}
