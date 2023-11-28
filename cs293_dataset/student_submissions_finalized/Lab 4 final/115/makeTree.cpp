#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <fstream>
#include "sort.cpp"
using namespace std;

int main(int argc, char** argv)//compile this file using "g++ maketree.cpp"
{//I didn't implement choose_four function so add that and then only compile 
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }
    int num_entries = atoi(argv[1]);                // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]);              // Function to be used for choosing pivot
    assert(1<=pivot_chooser && pivot_chooser<=4);   // Valid choice of pivot chooser function
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    SorterTree s(pivot_chooser,num_entries);
    int a,b;
    for(int i=0;i<num_entries;i++)
    {
        cin >> a;
        cin >> b;
        s.insertelement(a,b);
    }
    s.QuicksortWithBSTInsert(0,num_entries-1);
    cout <<"No of comparisons-"<<s.comparisons<<endl;//no of comparisons made during sorting
    cout <<"Imbalance-"<<s.tree->getImbalance()<<endl;
    s.printArray();//printing sorted array
    s.tree->printBST("");//printing final bst tree
    return 0;
}
