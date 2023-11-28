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
    
    SorterTree T{5,1};

    T.array = new Journey[num_entries];
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    for(int i=0; i<num_entries; i++)
    {
        cin>>T.array[i].JourneyCode;
    }
    T.Quicksort(0,num_entries-1);
    cout<<"Till here ?";
    for(int i=0; i<num_entries; i++)
    {
        cout<<T.array[i].JourneyCode<<endl;
    }

    

    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
