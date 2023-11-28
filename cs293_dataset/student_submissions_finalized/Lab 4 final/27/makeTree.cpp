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
    
    SorterTree tree(pivot_chooser,num_entries);
    auto start=chrono::high_resolution_clock::now();
    bool sorted=tree.QuicksortWithBSTInsert(0,num_entries-1);
    if(!sorted)cout<<"Couldnt be sorted"<<endl;
    auto end=chrono::high_resolution_clock::now();
    cout<<"Time = "<<chrono::duration_cast<chrono::microseconds>(end-start).count()<<" in microseconds"<<endl;
    tree.getTree()->printBST("-",true);
    tree.printArray();
    cout<<"Number of comparisons = "<<Journey::getComparisons()<<endl;
    cout<<"Imbalance is "<<tree.getTree()->getImbalance()<<endl;


}
