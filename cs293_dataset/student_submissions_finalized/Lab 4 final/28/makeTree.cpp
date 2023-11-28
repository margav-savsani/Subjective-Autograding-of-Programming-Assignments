#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include "sort.cpp"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Incorrect number of arguments" << endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]);   // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1 <= pivot_chooser && pivot_chooser <= 4); // Valid choice of pivot chooser function
    SorterTree a(pivot_chooser, num_entries);
    cout<<"Enter the journeys.."<<endl;
    a.input();
    int value;
    cout<<"Enter 0 for Quicksort and 1 for QuicksortwithBSTInsert"<<endl;
    cin>>value;

    if(value==0) a.Quicksort(0,num_entries-1);
    
    if(value==1) a.QuicksortWithBSTInsert(0, num_entries - 1);
    // cout<<"Hi'<<<endl;"<<endl;
    a.printArray();
    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "elapsed time: " << elapsed_seconds.count()*1000 << " Milliseconds\n";

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
}
