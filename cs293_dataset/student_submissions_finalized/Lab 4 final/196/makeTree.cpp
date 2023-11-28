#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include "tree.cpp"
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
    SorterTree s(pivot_chooser,num_entries);
    Journey a[num_entries];
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    for (int i=0;i<num_entries;i++){
        unsigned int jcode;
        cin >> jcode;
        unsigned int jprice;
        cin >> jprice;
        Journey j(jcode,jprice);
        a[i]=j;
    }
    s.setArray(a);
    // Also write code here to obtain different inputs as in the various parts of the question
    bool some=s.QuicksortWithBSTInsert(0,num_entries-1);
    cout<<"Sorted Array is:"<<endl;
    s.printArray();
    s.getTree()->printBST(" ");
    cout<<"The imbalance is:"<<s.getTree()->getImbalance()<<endl;
    cout<<"The total time taken for comparisons performed is:"<<s.getcomparisons()<<endl;
    // Add functionality to time your code (chrono may be helpful here)
    return 0;
}
