#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
// #include "sort.h"

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
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    
    SorterTree *st = new SorterTree(pivot_chooser,num_entries);

    Journey *x;
    for(int i=0; i<num_entries; i++){
        unsigned int c,p; cin >> c >> p;
        x = new Journey(c,p);
        
        // now to add to array of journeys
        Journey *main = st->getArray();
        main[i] = *x;
    }
    delete x;

    // JOURNEYS ADDED !
    // Now to sort them
    st->Quicksort(0,num_entries-1);
    st->printArray();

}
