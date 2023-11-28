#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include "sort.cpp"

using namespace std;

int main(int argc, char** argv)
{   
    auto start = chrono::steady_clock::now();
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot
    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function

    SorterTree s(pivot_chooser,num_entries);
    for(int i=0;i<num_entries;i++){
        int code,price;
        cin>>code>>price;
        if(!(s.insertJourney(code,price))){
            cout<<"Insertion failed"<<endl;
            break;
        }    
    }
    cout<<"Quicksort"<<endl;
    s.Quicksort(0,num_entries-1);
    s.printArray();
    cout<<"QuicksortWithBSTInsert"<<endl;
    s.QuicksortWithBSTInsert(0,num_entries-1);
    s.printArray();
    cout<<"BST of pivots"<<endl;
    s.BSTprint();
    cout<<"Imbalance "<<s.BSTimbalance()<<endl;
    cout<<"comparisons "<<s.comp()<<endl;   
    auto end = chrono::steady_clock::now();
    cout<<"Elapsed time in microseconds: "<<chrono::duration_cast<chrono::microseconds>(end - start).count()<<" microseconds"<<endl;
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
