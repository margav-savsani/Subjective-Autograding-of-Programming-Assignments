#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Incorrect number of arguments" << endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]);   // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1 <= pivot_chooser && pivot_chooser <= 4); // Valid choice of pivot chooser function

    /************************************************************************

     * Instructions to run code:
     * 1) g++ -g -c choose.cpp
     * 2) g++ -g -c journey.cpp
     * 3) g++ -g -c makeTree.cpp
     * 4) g++ -g -o makeTree choose.o journey.o makeTree.o
     

    ************************************************************************/

    SorterTree *x; // Constructor of SorterTree has it's own mechanism to take inputs.
    x = new SorterTree(pivot_chooser, num_entries);

    auto start = chrono::system_clock::now(); // Used Chrono to check time for Quicksort and to make BST.
    x->Quicksort(0, num_entries - 1);         // Called the QuickSort function which automatically creates BST also :)
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start; // Source for chrono: https://www.techiedelight.com/get-current-time-and-date-in-cpp/
                                                            // OUTPUTS.
    x->printOutputs();
    cout << ">>> Elapsed Time: " << elapsed_seconds.count() << " sec" << endl;
    cout << ">>> BST:" << endl;
    x->PrintBST();
}
