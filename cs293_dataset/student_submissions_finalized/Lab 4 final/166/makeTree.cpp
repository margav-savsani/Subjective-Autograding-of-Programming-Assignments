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
    
    SorterTree o(pivot_chooser,num_entries);
    
    for(int i=0;i<num_entries;i++){
        int it=0;
        int ut=0;
        cin>>it;
        cin>>ut;
        o.adds(it,ut,i);
    }
    o.Quicksort(0,num_entries-1);
    o.printArray();
    o.QuicksortWithBSTInsert(0,num_entries-1);
    //Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
