#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include "sort.cpp"

using namespace std;

int main(int argc, char **argv)
{
    auto start = chrono::steady_clock::now(); //Stores start time.

    if (argc != 3)
    {
        cout << "Incorrect number of arguments" << endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]);   // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1 <= pivot_chooser && pivot_chooser <= 4); // Valid choice of pivot chooser function

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    
    SorterTree *s = new SorterTree(pivot_chooser, num_entries);
    
    int jrnyCode, price;
    
    for (int i = 0; i < num_entries; i++)
    {
        cout << "Enter (Code, Price) values: ";
        cin >> jrnyCode >> price;

        Journey *entry = new Journey(jrnyCode, price); //Insertion
        (s->getArray())[i] = *entry;
    }

    cout<<endl;
    
    s->QuicksortWithBSTInsert(0, num_entries-1);
    cout << "No. of Comparisons made: " << s->getComparisons() << endl;

    cout <<"Imbalance: "<< s->getTree()->getImbalance() << endl;

    auto end = chrono::steady_clock::now(); //Stores End time

    cout << "Elapsed time in seconds: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count() //Prints time taken to run the code.
         << " micro-seconds"<<endl;

    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
}
