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
    SorterTree sortertree(pivot_chooser, num_entries);
    for(int i = 0; i<num_entries; i++)
    {
        int journeycode, price;
        cin>>journeycode>>price;
        Journey journey = Journey(journeycode,price);
        sortertree.Insert(journey,i);
    }
    sortertree.QuicksortWithBSTInsert(0,num_entries-1);
    auto start = std::chrono::system_clock::now();
    sortertree.Quicksort(0,num_entries-1);
    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    sortertree.printArray();
    sortertree.printTree();
    cout<<"The Imbalance of the tree is: "<<sortertree.getImbalance()<<endl;
    cout<<"The number of comparisons is: "<<sortertree.getComparisons()<<endl;
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    cout<<"Time elapsed is: "<<elapsed.count()<<endl;

}
