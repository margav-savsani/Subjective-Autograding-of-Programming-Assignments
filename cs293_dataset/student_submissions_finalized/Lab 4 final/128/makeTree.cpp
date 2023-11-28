#ifndef MAKETREE_CPP
#define MAKETREE_CPP

#include <stdlib.h>
#include <iostream>
#include <cassert>
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
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    //cout<< "constructer" <<endl;
    SorterTree sorter(pivot_chooser, num_entries);
    //cout<<"sorting"<<endl;
    //sorter.Quicksort(0,num_entries-1);
    //cout<<"sorted"<<endl;
    //sorter.printArray();
    sorter.QuicksortWithBSTInsert(0, num_entries-1);
    //sorter.printArray();
    BST* tree = sorter.getTree();
    tree->printBST("");
    //std::cout<<endl;
    std::cout << tree->getImbalance() << endl;
    std::cout<< sorter.getComparisons()<<endl;
}

#endif
