#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice , int size){
	array = new Journey [size];
	l = size;
	this->choice = choice;
	n = 0;
	tree = new BST();
	comparisons = 0;
}

//Returns the number of comparisons made
int SorterTree::get_comparisons(){
	return comparisons;
}

//Inserts the elements into array
bool SorterTree::Insert(Journey journey){
	if (n==l){
		return false;
	}
	else{
		array[n]=journey;
		n++;
		return true;
	}
}

//Quicksorts the array using recurssion
bool SorterTree::Quicksort(int start, int finish)
{
	if (start == finish){
		return true;
	}
	int j = Partition(start, finish);
	if (j=-1){
		cout << "Abonding because of invalid choose function" << endl;
		return false;
	}
	Quicksort(start, j);
	Quicksort(j+1, finish);
	return true;
}

//Returns j and partitions the array according to chosen pivot
int SorterTree::Partition(int start, int finish){	
	Journey* Pivot;	
	//chooses the Pivot according to 4 given functions
	switch(choice){
		case 1:
			Pivot = choose_one(array, start, finish);
			break;
		case 2:
			Pivot = choose_two(array, start, finish);
			break;
		case 3:
			Pivot = choose_three(array, start, finish);
			break;
		case 4:
			Pivot = choose_four(array, start, finish) ;
			break;
	}

	bool isInArray = false;
	for ( int k = start; k < finish + 1; k++ ){
		if ( array[k].getJourneyCode() == Pivot->getJourneyCode() && array[k].getPrice() == Pivot->getPrice())
		{
			isInArray = true;
		}
	}
	if (!isInArray){
		return -1;
	}

		int i = start;
		int j = finish;
	
	while(1){
		
		//Updating i
		while(array[i].getJourneyCode() < Pivot->getJourneyCode() ){
			comparisons++;
			i++;
		}
		
		//Updating j
		while( Pivot->getJourneyCode() <= array[j].getJourneyCode() ){
			comparisons++;
			j--;
			if (j==start && array[start].getJourneyCode() >= Pivot->getJourneyCode()){
				comparisons++;
				Journey temp;
				temp = *Pivot;
				*Pivot = array[start];
				array[start] = temp;
				return j;
			}
		}

		//If i becomes less than j, switch the elements at i and j
		if(i<j){
			Journey temp = array[i];
			array[i]=array[j];
			array[j]=temp;
			if (Pivot->getJourneyCode() == array[i].getJourneyCode() && Pivot->getPrice() == array[i].getPrice()){ 
				Pivot = &array[j];
			}
			if (Pivot->getJourneyCode() == array[j].getJourneyCode() && Pivot->getPrice() == array[j].getPrice()){ 
				Pivot = &array[i];
			}
		}
		
		//Return j after the quick sort has been performed
		else{
			return j;
		}	
	}
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{	
	//PIVOT is not called when only one function is in array to be analyzed
	if (start == finish){
		if ( !tree->find(array[start].getJourneyCode(), array[start].getPrice())){
			tree->insert(array[start].getJourneyCode(), array[start].getPrice());
		}
		return true;
	}

	//Partitioning the array
	Journey* Pivot;
	switch(choice){
		case 1:
			Pivot = choose_one(array, start, finish);
			break;
		case 2:
			Pivot = choose_two(array, start, finish);
			break;
		case 3:
			Pivot = choose_three(array, start, finish);
			break;
		case 4:
			Pivot = choose_four(array, start, finish) ;
			break;
	}

	//IsInArray
	bool isInArray = false;
	for ( int k = start; k < finish + 1; k++ ){
		if ( array[k].getJourneyCode() == Pivot->getJourneyCode() && array[k].getPrice() == Pivot->getPrice())
		{
			isInArray = true;
		}
	}
	if (!isInArray){
		cout << "Abonding the process (Invalid choose function)" << endl;
		return false;
	}
		Journey chosen_pivot = *Pivot;
		int i = start;
		int j = finish;
	while(1){
		while(array[i].getJourneyCode() < Pivot->getJourneyCode() ){
			comparisons++;
			i++;
		}
		while( Pivot->getJourneyCode() <= array[j].getJourneyCode() ){
			comparisons++;
			j--;
			if (j==start && array[start].getJourneyCode() >= Pivot->getJourneyCode()){
				comparisons++;
				Journey temp;
				temp = *Pivot;
				*Pivot = array[start];
				array[start] = temp;
				break;
			}
		}
		if(i<j){
			Journey temp = array[i];
			array[i]=array[j];
			array[j]=temp;
			if (Pivot->getJourneyCode() == array[i].getJourneyCode() && Pivot->getPrice() == array[i].getPrice()){ 
				Pivot = &array[j];
			}
			if (Pivot->getJourneyCode() == array[j].getJourneyCode() && Pivot->getPrice() == array[j].getPrice()){ 
				Pivot = &array[i];
			}
		}
		else{
			break;
		}	
	}

	//IF PIVOT HAS NOT BEEN INSERTED ALREADY, ONLY THEN I'M INSERTING IT
	if(! tree->find(  chosen_pivot.getJourneyCode() , chosen_pivot.getPrice()) ){
		tree->insert( chosen_pivot.getJourneyCode() , chosen_pivot.getPrice() );
	}

	//Call recurssively
	QuicksortWithBSTInsert(start, j);
	QuicksortWithBSTInsert(j+1, finish);
	return true;
}


//Prints the array
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
	return true;
}

//returns the BST
BST* SorterTree::getTree(){
	return tree;
}

//defualt destructor
SorterTree::~SorterTree(){
}