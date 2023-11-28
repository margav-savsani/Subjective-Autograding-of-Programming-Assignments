#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <fstream>
#include "sort.cpp"
#include <chrono>

using namespace std;

//---HANDLES INPUT OUTPUT---

int main(int argc, char** argv)
{
	//Select the pivot
	int pivot_chooser ;							
	cout << "Choose pivot_chooser (1:4)" << endl;
	cin >> pivot_chooser;
	
	// Valid choice of pivot chooser function	
	assert(1<=pivot_chooser && pivot_chooser<=4);

	//Take filename to be read as input
	cout << "Enter input file" << endl;
	char *c = new char[32] ;
	cin >> c;

	//Count number of lines in file
	ifstream g;
	g.open(c);
	int num_entries = 0;
	while (!g.eof()){
		num_entries++;
		int a;
		g >> a;
		g >> a;
	}
	g.close();

	//Reading file
	ifstream f;
	f.open(c);
	SorterTree S(pivot_chooser, num_entries);	
	while ( !f.eof() ){
		unsigned int code;
		unsigned int price;
		f >> code;
		f >> price;
		Journey temp(code, price);
		S.Insert(temp);
	}

	//Print the array read from file
	cout << "Array as read from the file" << endl;
	S.printArray();

	//Quicksort and insert into binary tree
	cout << endl << endl << "Calling quicksort and insert to binary tree " << endl;
	auto start = chrono::steady_clock::now();
	S.QuicksortWithBSTInsert(0, num_entries-1);
	auto end = chrono::steady_clock::now();
	cout << chrono::duration_cast<chrono::microseconds>(end - start).count() << "microseconds : time required for quicksort and insert" << endl;

	//Print the updated array
	cout << endl << endl << "Here is the Array" << endl;
	S.printArray();
	
	//Print the BST
	cout << endl << endl << "Here is the BST" << endl;
	S.getTree()->printBST("");
	
	//Print the comparisons
	cout << endl << "Imbalance is " << S.getTree()->pathDifference() << endl;
	cout << endl <<"Comparison made were " << S.get_comparisons();
	f.close();
}
