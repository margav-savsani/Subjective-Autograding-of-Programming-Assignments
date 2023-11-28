#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <cassert>
#include "tree.cpp"
#include "journey.cpp"
#include "sort.cpp"

using namespace std;

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
	Journey* array=new Journey[num_entries];
	for(int i=0;i<num_entries;i++){
		cin>>array[i];
	}
	SorterTree x(array,pivot_chooser,num_entries);
	auto start=chrono::high_resolution_clock::now();
	if(!x.Quicksort(0,num_entries-1)){
		cout<<"Couldn't sort elements. choose function returned out of bound values.\n";
		return 0;
	}
	auto end=chrono::high_resolution_clock::now();
	cout<<"Time Taken= "<<chrono::duration_cast<chrono::microseconds>(end-start).count()<< " micro seconds\n";
	cout<<"Sorted array is made by doing "<<Journey::getComparisonCount()<<" comparisons. Sorted array is:\n";
	x.printArray();
    // Also write code here to obtain different inputs as in the various parts of the question
	cout<<"Making Tree\n";
	if(!x.QuicksortWithBSTInsert(0,num_entries-1)){
		cout<<"Couldn't make tree\n";
		return 0;
	}
	BST* tree=x.getTree();
	cout<<"Tree was made with imbalance = "<<tree->getImbalance()<<endl;
	tree->printBST("SortedTree",false);
    // Add functionality to time your code (chrono may be helpful here)

}
