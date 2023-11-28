#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include "sort.cpp"
using namespace std;


// this file contain the main
// to compile this file run
// g++ makefile
// there should be a choose.cpp in folder
// otherwise this will give error

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
    SorterTree Tree(pivot_chooser,num_entries); // this will call default constructor which
    cout << "Array : " << endl;                 // take inputs from user
    Tree.printArray();                       // printing array without sorting
    auto start=chrono::high_resolution_clock::now();
    Tree.QuicksortWithBSTInsert(0,num_entries-1); // sorting using QuicksortWithBSTInsert
    auto end=chrono::high_resolution_clock::now();
    cout << "Time taken to sort : " << chrono::duration_cast<chrono::microseconds>(end - start).count()<< " micro seconds " << endl;
    cout << "sorted array : " << endl;    
    Tree.printArray();           // print sorted array
    cout << "cost is " << Tree.getComparisons() << endl;
    cout << "imbalance is "<< Tree.getTree()->getImbalance() << endl;
    Tree.getTree()->printBST(""); // print BST
    return 0;
}
