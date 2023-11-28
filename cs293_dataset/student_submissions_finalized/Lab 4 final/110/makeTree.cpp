#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>
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
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    SorterTree s(pivot_chooser,num_entries);
    for(int i=0;i<num_entries;i++){
        int journcode,journprice;
        cin>>journcode;
        cin>>journprice;
        s.addarray(journcode,journprice);
    }
    auto start = std::chrono::high_resolution_clock::now();
    s.Quicksort(0,num_entries-1);
    s.QuicksortWithBSTInsert(0,num_entries-1);
    s.printArray();
    cout<<"comparisions: "<<s.cost<<endl;
    cout<<"imbalance: "<<s.getTree()->getImbalance()<<endl; 
    s.printtree();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken in ms is "<<duration.count()<<endl;   //use this chrono to obtain time
}
