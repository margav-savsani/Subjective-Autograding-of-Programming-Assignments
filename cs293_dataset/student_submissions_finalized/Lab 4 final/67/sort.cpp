#include "sort.h"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(Journey* array,int choice, int l){
	this->array=new Journey[l];
	for(int i=0;i<l;i++){
		this->array[i]=array[i];
	}
	tree=new BST();
	this->l=l;
	this->choice=choice;
}

Journey* SorterTree::choosePivot(int start,int finish){
	// get the pivot
	Journey* pivot;
	switch(choice){
		case(1):
			pivot=choose_one(array,start,finish);
			break;
		case(2):
			pivot=choose_two(array,start,finish);
			break;
		case(3):
			pivot=choose_three(array,start,finish);
			break;
	}
	return pivot;
}

int SorterTree::divideArray(int start,int finish,Journey* pivot){
	int i=start,j=finish;
	while(i!=j){ // Divide the elements
		if(&array[i]==pivot){
			i++;
			continue;
		}
		if(array[i]<*pivot){
			i++;
			continue;
		}
		if(*pivot<array[j] || pivot->getJourneyCode()==array[j].getJourneyCode()){
			j--;
			continue;
		}
		if(&array[j]==pivot){
			j--;
			continue;
		}
		Journey temp=array[i];
		array[i]=array[j];
		array[j]=temp;
		i++;
	}
	
	if(pivot-array==i){ // return i as the brkpoint
		return i;
	}
	int brk;
	// Move pivot to center and sort the part on it's left and it's right
	if(*pivot<array[i]){
		if(pivot-array<i)	i--;
		Journey temp=array[i];
		array[i]=*pivot;
		*pivot=temp;
		brk=i;
	}
	else if(array[i]<*pivot){
		if(pivot-array>i)	i++;
		Journey temp=array[i];
		array[i]=*pivot;
		*pivot=temp;
		brk=i;
	}
	return brk;
}

bool SorterTree::Quicksort(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

	// Special Cases
	if(start==finish){
		return true;
	}
	if(start>finish){
		return true;
	}
	if(start<0 || finish>=l)	return true;
	Journey* pivot=choosePivot(start,finish);
	//if the choose function returns invalid function
	if(!pivot || pivot-array<start || pivot-array>finish){
		return false;
	}
	int brk=divideArray(start,finish,pivot);
	return (Quicksort(start,brk-1) && Quicksort(brk+1,finish));
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
	if(start>finish || start<0 || finish>=l){
		return true;
	}
	Journey* pivot=choosePivot(start,finish);
	if(!pivot || pivot-array<start || pivot-array>finish){
		return false;
	}
	int brkpt=divideArray(start,finish,pivot);
	if(!insertPivot(pivot->getJourneyCode(),pivot->getPrice()))	return false;
	return (QuicksortWithBSTInsert(start,brkpt-1) && QuicksortWithBSTInsert(brkpt+1,finish));
}

bool SorterTree::printArray(){
    for (int i = 0; i < l; i++)
    {
		cout<<array[i]; //Operator overloaded
    }
	return true;
}

bool SorterTree::insertPivot(int JourneyCode,int price){
	return tree->insert(JourneyCode,price);
}

BST* SorterTree::getTree(){
	return tree;
}

SorterTree::~SorterTree(){
	delete []array;
}
