#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <chrono>
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
    SorterTree records(pivot_chooser,num_entries);

    //testing purposes
    auto startTime= chrono::steady_clock::now();
    cout<<"The array:"<<endl<<endl;
    records.printArray();
    cout<<endl;
    cout<<"Sorted Array:"<<endl<<endl;
    records.QuicksortWithBSTInsert(0,num_entries-1);
    records.printArray();
    auto endTime= chrono::steady_clock::now();
    cout<<endl<<"The BST of pivots: "<<endl;
    records.getTree()->printBST("");
    cout<<endl<<"The imbalance in the tree is: ";
    records.getTree()->getImbalance();
    cout<<endl<<"The number of comparisons made is:"<<records.getComparisons()<<endl;
    cout << "Elapsed time in milliseconds: " <<chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()
        << " ns" << endl;
}
