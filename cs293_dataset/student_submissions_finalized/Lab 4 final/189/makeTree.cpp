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
    SorterTree ST(pivot_chooser,num_entries);
    for(int i=0;i<num_entries;i++) {
        int JC;
        int P;
        cout<<"Journey input";
        ST.getarray()[i].JourneyCode=JC;
        ST.getarray()[i].price=P;

    }
    ST.Quicksort(0,num_entries-1);
    for(int j=0;j<num_entries;j++){
        cout<<ST.getarray()[j].JourneyCode<<" "<<ST.getarray()[j].price<<endl;
    }
    ST.QuicksortWithBSTInsert(0,num_entries-1);
    for(int k=0;k<num_entries;k++) {
        cout<<ST.getarray()[k].JourneyCode<<" "<<ST.getarray()[k].price<<endl;
    }
    ST.getTree()->printBST("");


    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
