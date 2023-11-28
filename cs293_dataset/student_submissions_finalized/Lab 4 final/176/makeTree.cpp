#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>
using namespace std;

int main(int argc, char** argv)
{
    if(argc != 3 )
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    const int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
        
    unsigned int code,price;
    SorterTree arr(pivot_chooser, num_entries);
    int flag = arr.QuicksortWithBSTInsert(0, num_entries-1);
    if (flag == 0) {
        cout << "Sorry pivot inclusion error:\n";
        cout << "Array so far:\n";
        arr.printArray();
        return 0;
    }
    
    arr.printArray();
    BST* tree = arr.getTree();
    tree->printBST("");
    int a = tree->getImbalance();
    cout << "No. of comparisons = " << arr.getComparisons() << endl;
    cout << "Imbalance : " << a << endl;
        // Write your code here to accept input of journeys, input one per line as a (code, price) pair
        // Also write code here to obtain different inputs as in the various parts of the question
        // Add functionality to time your code (chrono may be helpful here)
    return 0;
    }
