#include "sort.h"
#include <iostream>
#include "journey.h"

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
	this->choice=choice;
	this->l=l;
}
SorterTree::SorterTree(Journey* array,int choice,int l){
	this->array=array;
	this->choice=choice;
	this->l=l;
}
bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
	if(start>=finish){
		return true;
	}
	int pivot;
	if(choice==1)	pivot=choose_one(array,start,finish)->JourneyCode;
	else if(choice==2)	pivot=choose_two(array,start,finish)->JourneyCode;
	else if(choice==3)	pivot=choose_three(array,start,finish)->JourneyCode;
	else if(choice==4)	pivot=choose_four(array,start,finish)->JourneyCode;
	int i=start,j=finish;
	//cout<<"piv= "<<pivot<<endl;
	while(i!=j){
		//cout<<i<<" "<<j<<endl;
		if(array[i].JourneyCode<pivot){
			i++;
			continue;
		}
		if(array[j].JourneyCode>=pivot){
			j--;
			continue;
		}
		//cout<<"wtf"<<endl;
		Journey temp=array[i];
		array[i]=array[j];
		array[j]=temp;
		i++;
	}
	//cout<<"ME"<<endl;
	//cout<<i<<" "<<j<<endl;
	return (Quicksort(start,j-1)&& Quicksort(j,finish));
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
	return false;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
		//std::cout<<array[i];
        std::cout<<"Journey code: "<<array[i].JourneyCode<<"\tJourney Price:"<<array[i].price<<std::endl;
    }
	return true;
}

SorterTree::~SorterTree(){}
