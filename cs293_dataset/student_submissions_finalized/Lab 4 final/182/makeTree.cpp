#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include<vector>

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
    SorterTree(pivot_chooser,num_entries);
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    


}
