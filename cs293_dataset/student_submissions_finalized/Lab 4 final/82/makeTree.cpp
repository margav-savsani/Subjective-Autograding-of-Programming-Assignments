#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

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
    assert(num_entries>0);

    SorterTree s(pivot_chooser, num_entries);
    cout << "INPUT YOUR ARRAY" << endl;
    s.inputArray();
    s.QuicksortWithBSTInsert(0, num_entries - 1);
    s.printArray();
    s.getTree()->printBST("");
    cout << "ShortestPathLength: " << s.getTree()->getRoot()->shortestPathLength << endl;
    cout << "LongestPathLength: " << s.getTree()->getRoot()->longestPathLength << endl;
    cout << "Imbalance: " << s.getTree()->getImbalance() << endl;
    cout << "Comparisions: " << s.getComp() << endl;
    

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
