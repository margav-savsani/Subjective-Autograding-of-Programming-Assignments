#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

using namespace std;

int main()
{

    int num_entries; // Number of journeys to enter
    int pivot_chooser; // Function to be used for choosing pivot

    cin>>num_entries;
    cin>>pivot_chooser;

    
    SorterTree *a=new SorterTree(pivot_chooser, num_entries);
    for(int i=0; i<num_entries; i++){
        int c, b;
        cin>>c>>b;
        Journey x(c, b);
        a->array[i]=x;
    }
    cout<<"lol"<<endl;
    a->Quicksort(0, num_entries-1);
    a->printArray();
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
