#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include<chrono>

using namespace std;

// ********************************************************** //
// ************** COMPILING INSTRUCTION ********************* //
// ********************************************************** //
// ********* g++ makeTree.cpp choose.o journey.cpp ********** //
// ********************************************************** //

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

    SorterTree s(pivot_chooser, num_entries);
    s.input();
    cout << "(0) QuickSort (1) QuichSortWithBSTInsert" << endl;
    int n;
    cin >> n;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    if (n)
    {
        s.QuicksortWithBSTInsert(0, num_entries - 1);
        s.getTree()->updatePath(s.getTree()->getRoot());
        s.getTree()->printBST("");
        cout << "Imbalance " << s.getTree()->getImbalance() << endl;
    }
    else if (!n)
    {
        s.Quicksort(0, num_entries - 1);
        s.printArray();
        cout << "Compares " << s.getCompares() << endl;
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << elapsed_seconds.count()*1000 << " miliseconds" << endl;
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
}
