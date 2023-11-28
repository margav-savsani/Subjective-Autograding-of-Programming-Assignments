#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
	this->l = l;	//l is the number of entries or the size of array to be created 
	this->choice = choice;//choice of the pivot chooser
	array=new Journey[l];//creating the array of Journey objects 
	entries_added=0;//entries added currently
	tree = new BST;//create a BST 
}

bool SorterTree::Quicksort(int start, int finish)
{
	
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start >= finish)//base case for recursion 
		return true;
	Journey* pivot;
	//finding the pivot using chooser functions
	do{
		if(!(choice >=1 && choice<=3)){
			return false;
		}	
		if(choice == 1){
			pivot = choose_one(array, start, finish);
		}
		else if(choice == 2){
			pivot = choose_two(array, start, finish);
		}
		else if(choice == 3){
			pivot = choose_three(array, start, finish);
		}
	}while(pivot==nullptr);
	Journey value=*pivot;
	int s = start;
	int f = finish;
	while(true){//main loop in quicksort responible for quickSort
		while(array[s]<value && s<=f){
			s++;
		}
		
		while(value<array[f] && f>=s){
			f--;
		}
		
		if(f>s){
			//swapping values in array[s] and array[f]
			Journey temp;
			temp = array[s];
			array[s] = array[f];
			array[f] = temp;
		}else{
			break;
		}
	}

	//using recursion basically self calling 
	if(f==finish)
		this->Quicksort(start, f-1);
	else{
		this->Quicksort(start, f);
		this->Quicksort(f+1, finish);
	}
	return true;
}

bool SorterTree::insert(unsigned int JourneyCode,unsigned int price){
	//insert function used for inserting in the array in Sorter Tree
	if(entries_added<l){
		array[entries_added].setJourneyCode(JourneyCode);
		array[entries_added].setJourneyPrice(price);
		entries_added++;
		return true;
	}else{
		return false;
	}
	
}

//QuickSort with binary Sort is exactly similar to QuickSort but here we just insert Pivots in the BST 
//as soon as we find the pivot
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(start > finish)
		return true;
	if(start==finish){
		insertPivot(array[start].getJourneyCode(), array[start].getPrice());//inserting pivot in BST
		return true;
	}
	Journey* pivot;
	do{
		if(!(choice >=1 && choice<=3)){
			return false;
		}	
		if(choice == 1){
			pivot = choose_one(array, start, finish);
		}
		else if(choice == 2){
			pivot = choose_two(array, start, finish);
		}
		else if(choice == 3){
			pivot = choose_three(array, start, finish);
		}
	}while(pivot==nullptr);
	Journey value=*pivot;
	insertPivot(value.getJourneyCode(), value.getPrice());//inserting Pivot in BST
	int s = start;
	int f = finish;
	while(true){
		while(array[s]<value && s<=f){
			s++;
		}
		
		while(value<array[f] && f>=s){
			f--;
		}
		
		if(f>s){
			Journey temp;
			temp = array[s];
			array[s] = array[f];
			array[f] = temp;
		}else{
			break;
		}
	}

	if(f==finish)
		this->QuicksortWithBSTInsert(start, f-1);
	else{
		this->QuicksortWithBSTInsert(start, f);
		this->QuicksortWithBSTInsert(f+1, finish);
	}
	return true;
}

int SorterTree::total_comparisons(){ //returns the total number of comparisons made in the journey class 
	return Journey::getStaticVar();
}

bool SorterTree::printArray()//prints the array and also holds th command to print the tree 
{
	tree->printBST("");
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
	return true;
}

int SorterTree::getImbalance(){//returns the imbalance in the bST
	return tree->getImbalance();
}


bool SorterTree::insertPivot(int JourneyCode, int price){//inserting the pivot in the BST by calling insert in the BST
	tree->insert(JourneyCode, price);
	return true;
}

SorterTree::~SorterTree(){ //destructor
	delete[] array;//deletes the array
	//the BST pointer is not deleted because it may be possible that its children is not constructed from new 
	//or perhaps it also is a node/root of another BST instance
}