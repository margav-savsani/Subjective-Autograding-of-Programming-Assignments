#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

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

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    
    SorterTree *ST = new SorterTree(pivot_chooser, num_entries);
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    for(int i = 0; i < num_entries; i++){
        unsigned int code,price;
        cin >> code >> price;
        ST->initializeArray(i,code,price);
    }
    // Also write code here to obtain different inputs as in the various parts of the question
    auto start = high_resolution_clock::now();

    ST->QuicksortWithBSTInsert(0,num_entries-1);
    ST->printArray();
    cout<<endl;
    // Add functionality to time your code (chrono may be helpful here)

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Time taken to sort, print the array and insert pivots, printing the tree :"<<duration.count() << " ms" << endl;

    
}
