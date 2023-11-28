#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>
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
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    int JourneyCode,price;
    SorterTree s = SorterTree(pivot_chooser,num_entries);
    
    s.QuicksortWithBSTInsert(0,num_entries-1);
    
    //s.printArray();
    //s.getTree()->printBST(" ");
    cout << "the imbalance is = ";
    cout << s.getTree()->getImbalance() << endl;

    //s.getTree()->getRoot();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time taken = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    cout << "Total comparisons made = " << s.getComparisons() << endl;

}
