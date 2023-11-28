#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>

using namespace std;


//for running in command line g++ makeTree.cpp
//  ./a.out 4 2 >inp


int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]);
    Journey* store = new Journey[num_entries];
    for (int i = 0; i < num_entries; i++)
    {
        unsigned int j, p;
        cin >> j >> p;
        store[i] = Journey(j, p);
    }// Function to be used for choosing pivot
    assert(1<=pivot_chooser && pivot_chooser<=4);
    auto start_time = std::chrono::high_resolution_clock::now();
    SorterTree S(pivot_chooser, num_entries,store);
    std::chrono::time_point<std::chrono::system_clock>start,end;
    start=std::chrono::system_clock::now();
    S.Quicksort(0,num_entries-1);
    end=std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds= end-start;
    S.printArray();
    cout <<"TIME TAKEN TO SORT : " << elapsed_seconds.count()*1000000 << " microunits" <<endl;
    std::chrono::time_point<std::chrono::system_clock>start1,end1;
    start1=std::chrono::system_clock::now();
    S.QuicksortWithBSTInsert(0,num_entries-1) ;
    end1=std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds1= end1-start1;
    cout <<"TIME TAKEN TO QuickSortWithBSTInsert is : " << elapsed_seconds1.count()*1000000 << " microunits" <<endl;
    S.getTree()->printBST(" ");
    cout <<"IMBALANCE OF THE TREE IS: " <<S.getTree()->getImbalance() <<endl;
    cout <<"THE NUMBER OF COMPARISONS: "<<S.getcomp()<<endl;
    // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
