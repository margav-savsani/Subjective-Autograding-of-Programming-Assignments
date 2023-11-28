#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp


bool SorterTree::Quicksort(int start, int finish)
{
	int j = Partition(start, finish);
	Quicksort(start, j);
	Quicksort(j+1, finish);
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

int SorterTree::Partition(int start, int finish){	
	Journey* Pivot;
	switch(l){
		case(1):
		Pivot = choose_one(array, start, finish);
		case(2):
		Pivot = choose_two(array, start, finish);
		case(3):
		Pivot = choose_three(array, start, finish);
		case(4):
		Pivot = choose_four(array, start, finish);
	}

		int i = start;
		int j = finish;
	while(1){
		while(array[i] < *Pivot ){
			i++;
		}
		while(*Pivot < array[j] ){
			j--;
		}
		if(i<j){
			Journey temp = array[i];
			array[i]=array[j];
			array[j]=temp;
		}
		else{
			return j;
		}	
		}
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
	QSWBI(start, finish, tree->get_root());
	return true;
}

void SorterTree::QSWBI(int start, int finish, TreeNode* root){
	
	Journey* Pivot;
	switch(l){
		case(1):
		Pivot = choose_one(array, start, finish);
		case(2):
		Pivot = choose_two(array, start, finish);
		case(3):
		Pivot = choose_three(array, start, finish);
		case(4):
		Pivot = choose_four(array, start, finish);
	}

		int i = start;
		int j = finish;
	while(1){
		while(*Pivot > array[i]){
			i++;
		}
		while(array[j] > *Pivot){
			j--;
		}
		if(i<j){
			Journey temp = array[i];
			array[i]=array[j];
			array[j]=temp;
		}
		else{
			break;
		}	
	}
	root = new TreeNode();
	root = Pivot;
	QSWBI(start, j, root->left);
	QSWBI(j+1, finish, root->right);
}


bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
