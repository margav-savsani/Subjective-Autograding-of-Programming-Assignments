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
    SorterTree s(pivot_chooser,num_entries);
    ifstream f;
    f.open("sample-input.txt");
    string x,y;
    int p,q;
    int i=0;
    while(!f.eof()){
        f>>x;
        p=stoi(x);
        f>>y;
        q=stoi(y);
        s.insert(p,q,i);
        i++;
        cout<<p<<" "<<q<<" "<<i<<endl;
    }
    s.Quicksort(0,num_entries-1);
    s.QuicksortWithBSTInsert(0,num_entries-1);
    s.printArray();
    s.getTree();
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
