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

    assert(1<=pivot_chooser && pivot_chooser<4); // Valid choice of pivot chooser function
    SorterTree s(pivot_chooser,num_entries);
    int x=num_entries,i=0;
    
    while(num_entries>0){
        unsigned int code,price;
        cin >> code;
        cin >> price;
        Journey j(code,price);
        s.add(i,j);
        i++;
        num_entries--;
    }
    s.QuicksortWithBSTInsert(0,x-1);
    cout << "Comparisons : " << s.getcomp() << endl;
    cout << "Imbalance of tree : " << s.getimb() << endl;
    s.Quicksort(0,x-1);
    s.printArray();
    s.printbst();
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
