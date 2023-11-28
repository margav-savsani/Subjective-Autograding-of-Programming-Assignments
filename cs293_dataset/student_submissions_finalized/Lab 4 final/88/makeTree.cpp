#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

using namespace std;

int main(int argc, char** argv)
{
    srand(11);
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments; enter number of journeys and choice of pivot function"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=5); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    SorterTree mytree(pivot_chooser, num_entries); // input taken inside constructor
    mytree.QuicksortWithBSTInsert(0, num_entries-1);
    //mytree.printArray();
    //mytree.printTree();
    printf("Comparisions: %d; Imbalance: %d\n",mytree.getcomparisions(), mytree.getimbalance()); // prints results
}
