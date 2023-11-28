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
    int nums= num_entries; //creating a copy
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    SorterTree t(pivot_chooser,nums);
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    while(num_entries--){
        unsigned int code,price;
        cin>>code>>price;
        t.insertJourney(code,price);
    }
    // Also write code here to obtain different inputs as in the various parts of the question
    t.printArray();
    // Add functionality to time your code (chrono may be helpful here)
    auto start = chrono::system_clock::now();
    t.Quicksort(0,nums-1);
    auto end = chrono::system_clock::now();
    auto elapsed = end - start;
    cout << elapsed.count() << '\n';
}
