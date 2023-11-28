#include "updated_sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int SorterTree::partition (int low, int high) 
{
	Journey* pivot;
	if (choice==1) pivot = choose_one(array, low, high);
	else if (choice==2) pivot = choose_two(array, low, high);
	else if (choice==3) pivot = choose_three(array, low, high);
	int i = (low-1);
	
	//cout << "inserting node...\n";
	tree->insert(pivot->getJourneyCode(), pivot->getPrice());      // inserts the pivot element to the BST
	//cout << "insert successful\n";
	Journey pv(pivot->getJourneyCode(), pivot->getPrice());
	for (int j=low; j<=high; j++)
	{
		if(array[j]<pv)
		{
			i++;
			Journey tmp=array[i];
			array[i]=array[j];
			array[j]=tmp;
		}
		comparisons++;                                               // comparisons is defined INSISDE of class!!
		
	}
	
	int k=low;
	while (k<=high) 
	{
		if (array[k].getJourneyCode() == pv.getJourneyCode())
			break;
		k++;
	}
	
	Journey tmp=array[k];
	array[k]=array[i+1];
	array[i+1]=tmp;
	return (i+1);
}

SorterTree::SorterTree(int choice_, int l_)
{
	choice=choice_;
	l=l_;
	comparisons=0;
	tree=new BST();
	array = new Journey[l];
	
	for (int i=0; i<l; i++)
	{
		unsigned int code, cost;
		cin >> code >> cost;
		//cout << code << " " << cost << endl;
		//Journey x(code, cost);                                       // creaate a journey with the given code, cost 
		array[i]=Journey(code, cost);                               // and added to the array
	}
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start == finish){
    	tree->insert(array[start].getJourneyCode(),array[start].getPrice());  //it adds the elements that are left over
    	return true;
    }
    else if (start > finish){
    	return false; 
    }
    else{
    int q = partition(start, finish);
			Quicksort(start, q-1);
			Quicksort(q+1, finish);
    	return true;
    }
}
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

/*bool SorterTree::insertArray(Journey* j)
{
	array=j;
	return true;
}*/

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

BST* SorterTree::getTree()
{
	return tree;
}

bool SorterTree::insertPivot(int JourneyCode, int price) {}
