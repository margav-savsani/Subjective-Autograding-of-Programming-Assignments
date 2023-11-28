#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.h"
#include <chrono>
#include <unistd.h>
using namespace std;


int main(int argc, char** argv)
{
    auto start = chrono::steady_clock::now();
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    Journey arr[num_entries];
    for(int i=0;i<num_entries;i++)
    {
        int JourneyCode,price;
        cin>>JourneyCode>>price;
        Journey j(JourneyCode,price);
        arr[i] = j;
    }
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    SorterTree b(pivot_chooser , num_entries , arr);
    //b.Quicksort(0,num_entries);
    b.QuicksortWithBSTInsert(0 , num_entries);
    b.printArray();
    b.getTree()->printBST(" " , false);
    cout<<b.print_Imbalance()<<endl;

    auto end = chrono::steady_clock::now();
    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;
    return 0;

}
