#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.h"
#include <chrono>
using namespace std;

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout << "Incorrect number of arguments" << endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

    // srand(time(0));

    // creating sorter tree object
    SorterTree mysorter(pivot_chooser, num_entries);
    mysorter.array_init(); // initialising the array

    // time start
    auto start = std::chrono::system_clock::now();

    // only quick sort 
    // if(!mysorter.Quicksort(0, num_entries-1)){
    //     cout << "QuickSort Failed" << endl;
    //     return 0;
    // };

    // quick sort with bst insert
    if(!mysorter.QuicksortWithBSTInsert(0, num_entries-1)){
        cout << "QuickSort Failed" << endl;
        return 0;
    };

    // time end
    auto end = std::chrono::system_clock::now();

    mysorter.printArray();
    cout << "Comparisons: " << mysorter.get_comparisons() << endl;
    cout << "Imbalance: " << mysorter.getTree()->getImbalance() << endl;
    cout << "Time units elapsed: " << (end-start).count() <<" ns" << endl;
    mysorter.getTree()->printBST("");
}
