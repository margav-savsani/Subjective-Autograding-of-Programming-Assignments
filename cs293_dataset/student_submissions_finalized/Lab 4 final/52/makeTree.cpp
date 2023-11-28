#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"      
#include <chrono>

using namespace std;
using namespace std::chrono;

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
    
    SorterTree T(pivot_chooser, num_entries);

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    for (int i = 0; i < num_entries; i++)
    {
        unsigned int journeyCode;
        cin >> journeyCode;
        unsigned int price;
        cin >> price;
        T.insert(journeyCode, price);
    }

    // clock start
    auto start = high_resolution_clock::now();

    // Quicksort
    bool success = T.QuicksortWithBSTInsert(0, num_entries-1);

    // clock end
    auto stop = high_resolution_clock::now();

    if(!success){
        cout << "ERROR: Quicksort not comlpleted successfully" << endl;
        return 0;
    }

    T.printArray(); cout << endl;
    
    T.printResults();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by quicksort: " << duration.count() << " microseconds" << endl;
    
    // Add functionality to time your code (chrono may be helpful here)

}
