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
    int nums=num_entries;
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    SorterTree t(pivot_chooser,nums);
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    while(num_entries--){
        unsigned int code,price;
        cin>>code>>price;
        t.insertJourney(code,price);
    }
    t.QuicksortWithBSTInsert(0,nums-1);
    t.printArray();
    cout<<endl;
    t.printBST();
    cout<<endl;
    cout<<"Imbalance : "<<t.getTree()->getImbalance()<<endl;
    cout<<"comparisons  : "<<t.compares()<<endl;
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    return 0;
}
