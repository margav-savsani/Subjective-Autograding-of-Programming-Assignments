#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

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

    SorterTree A(pivot_chooser,num_entries);

    unsigned int m,n;

    for(int i=0;i<num_entries;i++){
        cin>> m >>n;
        A.add(m,n,i);
    }

    auto start = std::chrono::high_resolution_clock::now();
    A.QuicksortWithBSTInsert(0,(num_entries)-1);
    auto stop =high_resolution_clock::now();
    auto duration = duration_cast<microseconds> (stop-start);
    cout <<"Time spent for this quicksort: " <<duration.count()<<endl;

    cout <<"No of comparisions: " <<A.getcomparisions()<<endl;
    A.printArray();

    BST *t=A.getTree();
    t->printBST("");
    cout <<"Imbalance: "<<t->getImbalance()<<endl;
    cout <<t->highestlength()<<" "<<t->leastlength()<<endl;

    exit(0);
}
