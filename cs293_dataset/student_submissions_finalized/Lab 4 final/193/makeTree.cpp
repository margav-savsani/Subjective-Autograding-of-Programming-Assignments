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

    // Taking input as Journey, Price pair.

    Journey *a = new Journey[num_entries];
    for (int i = 0; i < num_entries; i++)
    {
        unsigned int j, p;
        cin >> j >> p;
        a[i] = Journey(j, p);
    }
    SorterTree S = SorterTree(pivot_chooser, num_entries, a); // Creating a sorter tree instance
    std::chrono::time_point<std::chrono::system_clock> start, end; // Time calculation of sort
    start = std::chrono::system_clock::now();
    S.QuicksortWithBSTInsert(0, num_entries - 1); // Sort with insert.
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "THE ARRAY SORTED " << endl;
    S.printArray();
    cout << endl;
    cout << "TREE MADE FROM PIVOTS" << endl;
    S.getTree()->printBST("");
    cout << endl;
    cout << "THE NUMBER OF COMPARISONS " << S.comparisons_count() << endl;
    cout << "TIME TAKEN TO SORT " << elapsed_seconds.count() * 1000 << " miliunits" << endl;
    cout << "IMBALANCE OF THE TREE IS " << S.getTree()->getImbalance() << endl;
}