#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
//#include "choose.h"

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

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    SorterTree T(pivot_chooser, num_entries);
    cout << "Enter the journey code and price of each journey as <JourneyCode> <price>\n";
    for (int i = 0; i < num_entries; i++)
    {
        int j, p;
        cin >> j >> p;
        if (j < 0 || p < 0) {cout << "Invalid pair, both must be non-negative\n"; i--; continue;}
        T.addJourney(i, j, p);
    }
    bool one = T.callQuickSort(0, num_entries - 1);
    if (!one) {cout << "Error in sorting. Exiting\n"; return 0;}
    bool two = T.QuicksortWithBSTInsert(0, num_entries - 1);
    if (!two) {cout << "Return in BST formation. Exiting\n"; return 0;}
    cout << "Imbalance is " << (T.getTree())->getImbalance() << endl;
}