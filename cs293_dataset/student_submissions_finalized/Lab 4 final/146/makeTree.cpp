#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

using namespace std;

// COMPILATION INSTRUCTIONS :
// Compile using g++ makeTree.cpp Journey.cpp choose.cpp -o a.out


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
    SorterTree T{pivot_chooser,num_entries};
    T.setArray();
    T.QuicksortWithBSTInsert(0,num_entries-1);
    T.printArray();
    T.printTree();
    cout<<"Imbalance is : ";
    T.printImbalance();
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    cout<<"Number of comparisons are :";
    T.printComparisons();
    return 0;
}
