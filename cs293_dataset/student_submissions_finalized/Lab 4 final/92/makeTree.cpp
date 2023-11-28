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

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    Journey *a;
    a=new Journey[num_entries];
    for(int i=0;i<num_entries;i++){
        unsigned int j,p;
        cin>>j>>p;
        a[i]=Journey(j,p);
    }
    SorterTree Stree(pivot_chooser,num_entries,a);
    Stree.QuicksortWithBSTInsert(0,num_entries-1);
    Stree.printArray();
    Stree.getTree()->printBST(" ");
    cout<<Stree.getTree()->getImbalance();
    
        // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
