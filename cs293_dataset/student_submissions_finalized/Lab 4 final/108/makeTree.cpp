#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.h"

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
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

    Journey a[num_entries];
    srand(time(0));
    for (int i=0; i<num_entries; i++) {
        a[i] = {rand()%1000, rand()%1000};
    }

    SorterTree st { pivot_chooser, num_entries, a };
    // st.printArray();
    // cout << '\n';

    // auto start = chrono::high_resolution_clock::now();
    // st.Quicksort(0, num_entries-1);
    // auto t = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start);
    // st.QuicksortWithBSTInsert(0, num_entries-1);
    // st.printArray();
    // st.printTree();
    // cout << "Comparisons = " << st.comp() << '\n';
    // cout << "Imbalance = " << st.imbalance() << '\n';
    // cout << "Time(in microseconds) = " << t.count() << '\n';
}