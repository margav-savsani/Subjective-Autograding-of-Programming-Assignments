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
    
    SorterTree s(pivot_chooser,num_entries);   // Creating sorter array
    
    for(int i=0;i<num_entries;i++){int x,y; cin >> x>>y; Journey j(x,y); s.add(j,i); }   // taking inputs for journey array
    
    s.QuicksortWithBSTInsert(0,num_entries-1);  
    s.printArray();
    
    s.getTree()->pretraverse(); cout << endl;
    cout << s.getTree()->getImbalance()<<endl;
    s.getTree()->printBST("hi",false);
}
