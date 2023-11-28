#include<cassert>
#include "sort.h"
#include <iostream>
using namespace std;
// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int num, int a)
{   //intializers choice,arraysize,intializing tree and taking inputs to array
	choice = num;  
	l = a;
	array = new Journey[l];
	for (int i = 0; i < l; i++)
	{
		int jr_Code, prices;
		cin >> jr_Code >> prices;
		Journey Dummy = Journey(jr_Code, prices);
		array[i] = Dummy;
		tree = new BST();
	}
}
bool SorterTree::Quicksort(int start, int finish)
{
	Journey * pivot;   //choosing pivot  based on choice
	if (choice == 1)
	{
		pivot = choose_one(array, start, finish);
	}
	if (choice == 2)
	{
		pivot = choose_two(array, start, finish);
	}
	if (choice == 3)
	{
		pivot = choose_three(array, start, finish);
	}
	if (choice == 4)
	{
		pivot = choose_four(array, start, finish);
	}
	if (start == finish)  //base case if start = finish returns true
	{
		return true;
	}

	/*if(finish-start==1){

	    if(array[start].getJourneyCode() >array[finish].getJourneyCode())
	    {swap(array[start],array[finish]);}
	}*/
	if (start < finish)
	{
		int i = start;
		int j = finish;
		int pivot_index;
		for (int i = start; i <= finish; i++) // finding pivot index
		{

			if (pivot->getJourneyCode() == array[i].getJourneyCode())
			{
				pivot_index = i;
				break;
			}
		}
        assert( pivot_index <= finish && pivot_index >= start); //if pivot is not present in array it terminates the function
		swap(array[pivot_index], array[finish]);
		// partition
		while (i < j) // partition function
		{
			while (array[i].getJourneyCode() < array[finish].getJourneyCode())
			{
				comparisons++;
				i++;
			}
			while (array[j].getJourneyCode() >= array[finish].getJourneyCode())
			{
				comparisons++;
				j--;
			}

			if (i < j)
			{
				swap(array[i], array[j]);
			}
		}

		swap(array[i], array[finish]);
		if (i - 1 >= start) // checking if i-1>start and fixing the soreted element and partitioning the before and after partitions
		{
			Quicksort(start, i - 1);
		}
		if (i + 1 <= finish) 
		{
			Quicksort(i + 1, finish);
		}

		return true;
	}
	// index of array??
	// Call appropriate pivot function based on choice
	// Split into 2 parts based on pivot choice
	// Recursively keep sorting
}
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{

	Journey * pivot; //choosing pivot  based on choice
	if (choice == 1)
	{
		pivot = choose_one(array, start, finish);
	}
	if (choice == 2)
	{
		pivot = choose_two(array, start, finish);
	}
	if (choice == 3)
	{
		pivot = choose_three(array, start, finish);
	}
	if (choice == 4)
	{
		pivot = choose_four(array, start, finish);
	}
	if (start == finish) //base case 
	{
		insertPivot(array[finish].getJourneyCode(), array[finish].getPrice()); // inserting into the tree
		return true;
	}

	/*if(finish-start==1){

	    if(array[start].getJourneyCode() >array[finish].getJourneyCode())
	    {swap(array[start],array[finish]);}
	}*/
	if (start < finish) // finding pivot index
	{
		int i = start;
		int j = finish;
		int pivot_index;
		for (int i = start; i <= finish; i++)
		{

			if (pivot->getJourneyCode() == array[i].getJourneyCode())
			{
				pivot_index = i;
				break;
			}
		}
        assert( pivot_index <= finish && pivot_index >= start); //if pivot is not present in array it terminates the function
		insertPivot(array[pivot_index].getJourneyCode(), array[pivot_index].getPrice()); // inserting pivot
		swap(array[pivot_index], array[finish]); // swaping the pivot to the last and substituting it back at the end
		// partition function
		while (i < j)
		{
			while (array[i].getJourneyCode() < array[finish].getJourneyCode())
			{
				comparisons++;
				i++;
			}
			while (array[j].getJourneyCode() >= array[finish].getJourneyCode())
			{
				comparisons++;
				j--;
			}

			if (i < j)
			{
				swap(array[i], array[j]);
			}
		}

		swap(array[i], array[finish]);
		if (i - 1 >= start)// checking if i-1>start and fixing the soreted element and partitioning the before and after partitions
		{
			QuicksortWithBSTInsert(start, i - 1);
		}
		if (i + 1 <= finish)
		{
			QuicksortWithBSTInsert(i + 1, finish);
		}

		return true;
	}
}
bool SorterTree::insertPivot(int JourneyCode, int price)
{
	tree->insert(JourneyCode, price);
	return true;
}
bool SorterTree::printArray()
{
	for (int i = 0; i < l; i++)
	{
		std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
	}

	cout << "comparisons : " << comparisons << endl;
}
BST *SorterTree::getTree()
{
	return tree;
}
SorterTree::~SorterTree() {};
//insertPivot(array[pivot_index].getJourneyCode(),array[pivot_index].getPrice());