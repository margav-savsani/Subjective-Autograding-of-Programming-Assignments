#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include "sort.cpp"

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

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    SorterTree *sortTree1 = new SorterTree(pivot_chooser, num_entries);
    SorterTree *sortTree2 = new SorterTree(pivot_chooser, num_entries);
    for (int i = 0; i < num_entries; i++)
    {
        int JourneyCode, price;
        cin >> JourneyCode >> price;
        sortTree1->insertJourney(JourneyCode, price, i);
        sortTree2->insertJourney(JourneyCode, price, i);
    }

    auto start1 = chrono::high_resolution_clock::now();
    sortTree1->Quicksort(0, num_entries - 1);
    sortTree1->printArray();
    cout << "Cost of Comparisons: " << sortTree1->getComparisons() << endl;

    auto diff1 = chrono::high_resolution_clock::now() - start1;
    auto t1 = chrono::duration_cast<std::chrono::nanoseconds>(diff1);
    cout << "Time for Quicksort: " << t1.count() << endl;

    cout << "\n\n";

    auto start2 = chrono::high_resolution_clock::now();
    sortTree2->QuicksortWithBSTInsert(0, num_entries - 1);
    sortTree2->getTree()->printBST("");
    cout << sortTree2->getTree()->getImbalance() << endl;
    auto diff2 = chrono::high_resolution_clock::now() - start2;
    auto t2 = chrono::duration_cast<std::chrono::nanoseconds>(diff2);
    cout << "Time for QuicksortwithBSTInsert: " << t2.count() << endl;
}
