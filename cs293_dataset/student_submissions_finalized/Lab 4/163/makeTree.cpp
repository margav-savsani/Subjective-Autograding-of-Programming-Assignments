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
    SorterTree *tree = new SorterTree(pivot_chooser, num_entries);
    for (int i = 0; i < num_entries; i++)
    {
        int JourneyCode, price;
        cin >> JourneyCode >> price;
        tree->insertJourney(JourneyCode, price, i);
    }
    auto start = chrono::high_resolution_clock::now();
    tree->Quicksort(0, num_entries);
    auto diff = chrono::high_resolution_clock::now() - start;
    auto t1 = chrono::duration_cast<std::chrono::nanoseconds>(diff);
    cout << "Loop1: " << t1.count() << endl;
}
